/***********************************************************************
* File: icmp.c
* Description:
***********************************************************************/
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "ethdrv.h"
#include "nwstk.h"
#include "nwutil.h"

typedef struct
{
  UINT8   icmpType;
  UINT8   icmpCode;
  UINT16  icmpChksum;
  UINT8   data[1];
}icmpHdr_t;

typedef struct
{
  UINT8   icmpType;
  UINT8   icmpCode;
  UINT16  icmpChksum;
  UINT16  echoId;
  UINT16  echoSeq;
  UINT8   data[1];
}icmpEcho_t;


#define   ICMP_ECHO_RESP  0
#define   ICMP_ECHO_REQ   8
 
/***********************************************************************
* Name:
* Description:
***********************************************************************/
void icmpSendEchoReply(pktBuf_t *pkt, icmpHdr_t *pic)
{
  UINT8 dstIpAdrs[4];

  memcpy(dstIpAdrs, &pkt->buf[26], IP_ADRS_LEN);
  pkt->len -= (ETH_HDR_LEN + IP_HDR_LEN);
  pic->icmpType = ICMP_ECHO_RESP;
  pic->icmpChksum = 0;
  pic->icmpChksum = computeChecksum(pkt->data, pkt->len);
  ipSendPkt(pkt, dstIpAdrs, PROTO_ICMP);
}

/***********************************************************************
* Name: icmpIn
* Description:
   This function is called whenever IP packet with protcol field as ICMP
 is received. This function processes only ICMP echo request and echo 
 response packets only.If it receives icmp echo request packet,it sends
 icmp echo response packet.
***********************************************************************/
void icmpIn(pktBuf_t *pkt)
{
  icmpHdr_t  *pic;
  icmpEcho_t *pEcho;

  pic = (icmpHdr_t *) pkt->data;
  switch(pic->icmpType)
  {
    case ICMP_ECHO_REQ:
       printf("ICMP req len : %d\n",pkt->len); 
      // printBuf(pkt->buf, pkt->len); 
      icmpSendEchoReply(pkt, pic);
      break;

    case ICMP_ECHO_RESP:
      pEcho = (icmpEcho_t *)&pkt->buf[34];
      printf("%d bytes from %d.%d.%d.%d: icmp_seq=%d\n",
             (pkt->len - 34), pkt->buf[26],pkt->buf[27],pkt->buf[28],
              pkt->buf[29],pEcho->echoSeq);
      pktFree(pkt);
      break;

    default:
      pktFree(pkt);
      break;
  }
}
/***********************************************************************
* Name: ping
* Description:
***********************************************************************/
int ping(int argc,char *argv[])
{
  int cnt,maxCnt;
  UINT8 ii;
  UINT8 dstIpAdrs[4];

  maxCnt = 100;

  if(argc == 2)
  {
    ip2bin(argv[1],dstIpAdrs);
  }
  else if (argc == 3)
  {
    ip2bin(argv[1],dstIpAdrs);
    sscanf(argv[2],"%d",&maxCnt);
  }
  else
  {
    printf("Invalid arguments\n");
    printf("Invalid arguments\n");
    return;
  }

  for(cnt=0; cnt < maxCnt; cnt++)
  {
    pktBuf_t *pkt = pktAlloc();
   icmpEcho_t  *pic = (icmpEcho_t *)&pkt->buf[ETH_HDR_LEN + IP_HDR_LEN];

    pic->icmpType   = ICMP_ECHO_REQ;
    pic->icmpCode   =  0;
    pic->icmpChksum =  0;
    pic->echoSeq    =  cnt;
    for(ii=0; ii<56; ii++)
      pic->data[ii] =  ii;
    pkt->len = 64;
    pic->icmpChksum = computeChecksum(&pkt->buf[34], pkt->len);
    ipSendPkt(pkt, dstIpAdrs, PROTO_ICMP);
    taskDelay(100);
  }
}

/***********************************************************************
* Name:
* Description:
***********************************************************************/
int icmpInit()
{
  shellRegCmd("ping",ping, "Send ping packet");
}
