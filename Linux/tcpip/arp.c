/***********************************************************************
* File: arp.c
* Description:
*   This file implements the arp module. Following are the interface functions
*   of this ARP module.
*
*      arpInit()
*      arpIn()
*      arpSendIpPkt()
*      arpStat()
*      arpDispTbl()
***********************************************************************/
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "ethdrv.h"
#include "nwstk.h"

#define  SUCCESS      0
#define  MAXSIZE      1024 
#define  TRUE         1
#define  FALSE        0 
#define  LOCAL        static 

#define  MAX_ARP_ENTRIES            32 

#define  ARP_ENTRY_FREE             0 
#define  ARP_ENTRY_PENDING          1 
#define  ARP_ENTRY_RESOLVED         2 

#define  ARP_REQ                    1
#define  ARP_RESP                   2

typedef struct
{
  UINT32    state;
  UINT8     ipAdrs[IP_ADRS_LEN];
  UINT8     hwAdrs[HW_ADRS_LEN];
  pktQ_t    pktQ;
}arpEntry_t;


LOCAL arpEntry_t arpTbl[MAX_ARP_ENTRIES];

LOCAL UINT32  arpInCnt,arpInReqCnt, arpInReqMatchCnt, arpInRespCnt, arpHitCnt;
LOCAL UINT32  arpSendIpPktCnt, arpReqSentCnt, arpSentIpPktWRCnt;

/***********************************************************************
* Name:
* Description:
*   Returns index of free entry in ARP table through output parameter.
* Parameters:
*   indx : (O) pointer to place index value;
* Return value:
*   OK : On finding free entry in ARP table
*   ERROR : If no free entry found in arp table.
***********************************************************************/
LOCAL int arpGetFreeEntry(int *indx)
{
  int ii;
  for(ii=0; ii<MAX_ARP_ENTRIES; ii++)
  {
    if(arpTbl[ii].state == ARP_ENTRY_FREE)
    {
      *indx = ii;
      return OK;
    }
  }
  printf("###ERROR###: cound not find arp entry\n");
  return ERROR;
}

/***********************************************************************
* Name: arpFindEntry
* Description:
***********************************************************************/
LOCAL int arpFindEntry(UINT8 *ipAdrs, int *index)
{
  int ii;
  for(ii=0; ii<MAX_ARP_ENTRIES; ii++)
  {
    if ((arpTbl[ii].state == ARP_ENTRY_RESOLVED) &&
        (memcmp(arpTbl[ii].ipAdrs,ipAdrs,4) == 0))
    {
      *index = ii;
      return OK;
    }
  }
  return ERROR;
}
/*LOCAL int arpFindEntry(UINT8 *ipAdrs, int *index)
{
  int ii;
  for(ii=0; ii<MAX_ARP_ENTRIES; ii++)
  {
    if (memcmp(arpTbl[ii].ipAdrs,ipAdrs,4) == 0)
    {
      *index = ii;
      return OK;
    }
  }
  return ERROR;
}*/
/***********************************************************************
* Name: arpAddEntry
* Description:
*   This function adds a new resolved entry into the arp table.
***********************************************************************/
LOCAL int arpAddEntry(UINT8 *ipAdrs, UINT8 *hwAdrs)
{
  int indx;

  /*** If ARP entry exists for this IP address already, update the hardware
   *** address with the give hardware address ***/
  if(arpFindEntry(ipAdrs, &indx) == OK)
  {
    memcpy(arpTbl[indx].hwAdrs, hwAdrs, HW_ADRS_LEN);
    return OK;
  }

  /*** Find free entry in ARP table and copy this new entry ***/
  if(arpGetFreeEntry(&indx) == OK)
  {
    memcpy(arpTbl[indx].ipAdrs, ipAdrs, IP_ADRS_LEN);
    memcpy(arpTbl[indx].hwAdrs, hwAdrs, HW_ADRS_LEN);
    arpTbl[indx].state = ARP_ENTRY_RESOLVED;
    return OK;
  }
  return ERROR; 
}

/***********************************************************************
* Name: arpIn
* Description:
* This function is called by the net task, whenever it receives a frame 
* with frame type as ARP. 
***********************************************************************/
void arpIn(pktBuf_t *pkt)
{
  int      ii;
  arpPkt_t *pArp; 
  iface_t  *pIf; 
  int      op;
 
  arpInCnt++;
  pIf  = ifaceTbl[pkt->ifNum];
  pArp = (arpPkt_t *)(pkt->data+sizeof(ethHdr_t));
  op   = htons(pArp->operation);

  if(op == ARP_REQ)
  {
    arpInReqCnt++;
    /*** If it is ARP request for our IP address, send ARP reply ***/
    if(memcmp(pArp->targetPra,pIf->ipAdrs,4) == 0)
    {
      arpInReqMatchCnt++;
      pArp->operation = htons(ARP_RESP);
      memcpy(pArp->targetHwa, pArp->senderHwa, HW_ADRS_LEN);
      memcpy(pArp->targetPra, pArp->senderPra, IP_ADRS_LEN);
      memcpy(pArp->senderPra, pIf->ipAdrs, IP_ADRS_LEN);
      memcpy(pArp->senderHwa, pIf->macAdrs, HW_ADRS_LEN);
      arpAddEntry(pArp->targetPra, pArp->targetHwa);
      memcpy(pkt->data, pkt->data+6, HW_ADRS_LEN);
      memcpy(pkt->data+6, pIf->macAdrs, HW_ADRS_LEN);
      pIf->sendFP(pIf->pDev,pkt);
      return;
    }
  }
  else if(op == ARP_RESP)
  {
    arpInRespCnt++;

    for(ii=0; ii<MAX_ARP_ENTRIES; ii++)
    {
      if ( (arpTbl[ii].state == ARP_ENTRY_PENDING) && 
           (memcmp(arpTbl[ii].ipAdrs,pArp->senderPra,4) == 0))
      {
        memcpy(arpTbl[ii].hwAdrs, pArp->senderHwa, HW_ADRS_LEN);
        arpTbl[ii].state = ARP_ENTRY_RESOLVED;
        pktFree(pkt);
        while(pkt = pktDeQ(&arpTbl[ii].pktQ))
        {
          memcpy(pkt->data,arpTbl[ii].hwAdrs,HW_ADRS_LEN);
          arpSentIpPktWRCnt++;
          pIf->sendFP(pIf->pDev,pkt);
        }
        //semGive(arpSem);
        return;
      }
    }
  }
  pktFree(pkt);
}

/***********************************************************************
* Name: arpSendIpPkt
* Description:
*    This function is called by the IP layer to send an IP packet. This *  arp function should fill the destination's H/W address in packet's   *  frame header.
***********************************************************************/
int arpSendIpPkt(pktBuf_t *pkt, UINT8 *nxtHopIpAdrs, iface_t *pIf)
{
  int index;
  ethHdr_t *pEthHdr;
  arpPkt_t *pArp; 
  pktBuf_t *pkt1; 
  arpSendIpPktCnt++;

  if(arpFindEntry(nxtHopIpAdrs, &index) == OK)
  {
      arpHitCnt++;
      memcpy(pkt->data,arpTbl[index].hwAdrs,HW_ADRS_LEN);
      pIf->sendFP(pIf->pDev,pkt);
  }
  else
  {
    if(arpGetFreeEntry(&index) != OK)
    {
      printf("No free entry in ARP table\n");
      pktFree(pkt);
      return ERROR;
    }

    memcpy(arpTbl[index].ipAdrs, nxtHopIpAdrs, IP_ADRS_LEN);
    arpTbl[index].state = ARP_ENTRY_PENDING; 
    pktEnQ(&arpTbl[index].pktQ, pkt);

    pkt1 = pktAlloc();
    if(pkt1==NULL)
    {
      printf("Pkt alloc failed\n");
      return ERROR;
    }

    pArp = (arpPkt_t*) pkt1->data;
    pEthHdr = (ethHdr_t*) (pkt1->data-sizeof(ethHdr_t));
    pkt1->data=(UINT8 *)pEthHdr;
    memset(pArp, 0, sizeof(arpPkt_t));

    /** Prepare ARP request packet **/
    memset(pEthHdr->dstHwa,0xff,6); 
    memcpy(pEthHdr->srcHwa,pIf->macAdrs, HW_ADRS_LEN); 
    pEthHdr->type = htons(ARP_PKT); 

    pArp->hwType    = htons(1);
    pArp->protoType = htons(IP_PKT); 
    pArp->hwaLen    = HW_ADRS_LEN;
    pArp->protoLen  = IP_ADRS_LEN; 
    pArp->operation = htons(1); 
    memcpy(pArp->senderHwa, pIf->macAdrs, HW_ADRS_LEN); 
    memcpy(pArp->senderPra,pIf->ipAdrs,4);  
    memcpy(pArp->targetPra,nxtHopIpAdrs,4);  

    pkt1->len = sizeof(arpPkt_t) + ETH_HDR_LEN;
    arpReqSentCnt++;

  /*** Send ARP request packet by calling interface's send function ***/
    pIf->sendFP(pIf->pDev,pkt1);
  }
  return SUCCESS;
}

/***********************************************************************
* Name: arpDispTbl
* Description:
*  This function is called from command line interface. This displays  
*  all the resolved arp table entries.
***********************************************************************/
LOCAL int arpDispTbl(int argc, char * argv[])
{
  int ii, jj;
  for(ii=0; ii<MAX_ARP_ENTRIES; ii++)
  {
    if (arpTbl[ii].state == ARP_ENTRY_RESOLVED) 
    {
      for(jj=0; jj<3; jj++)
      {
        printf("%d.",arpTbl[ii].ipAdrs[jj]);
      }
      printf("%d   :  ",arpTbl[ii].ipAdrs[jj]);
      printBuf(arpTbl[ii].hwAdrs, 6);
      printf("\n");
    }
  }
}

/***********************************************************************
* Name: arpStat
* Description:
*   This function is called from command line interface. This function 
*   displays arp statistics.
***********************************************************************/
LOCAL int arpStat(int argc, char * argv[])
{
  printf("ArpIn Pkts   : %d\n"
         "ArpIn Req    : %d\n"
         "ArpIn Rq Mtch: %d\n"
         "ArpIn Resp   : %d\n"
         "Arp Hits     : %d\n"
         "ArpSendIpPkts: %d\n",
         arpInCnt,arpInReqCnt, arpInReqMatchCnt, arpInRespCnt, arpHitCnt,
         arpSendIpPktCnt);
}

/***********************************************************************
* Name: arpInit
* Description:
*   This function registers arp shell commands.
***********************************************************************/
void arpInit()
{
  shellRegCmd("arp",arpDispTbl, "show arp Tbl");
  shellRegCmd("arpStat",arpStat, "arp Counters");
  //arpSem=semBCreate(0,0);
}
