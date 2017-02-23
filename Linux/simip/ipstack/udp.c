/*******************************************************************************
* File name : udp.c
* Description :
*   This file maintains the udp control block list. when user creates the new
*   socket then it internally calls the udpSocket() this function allocates
*   one new control block for that socket and this control block to udp list
*   and returns the that pointer . Next time onwards user operates that 
*   pointer.This file is the interface between user and ip .That is user sends
*   data to this layer and get data from this layer. If user wants to send data
*   he calls the udpSendTo() . This function allocates one mBuf_t variable and
*   fill the udpHeader. it maps the data and header to mbuf pointer and sends
*   the mbuf pointer to ip layer.If user wants to receive data then it calls
*   the udpRecvFrom().This function initially blocked on semaphore . whenever
*   ip calls the udpIn() function. This udpIn() function checks whether this
*   packet is ours or not . if it is ours then it gets the corresponding udp
*   control block pointer and queues that packet to that control block queue 
*   and gives the semaphore .in udpRecvFrom () it takes the semaphore and
*   dequeue s the packet and parse the packet and gives the data to user.When
*   user calls the close() then we deallocates the corresponding udp control
*   block pointer.
*******************************************************************************/

#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "pktbuf.h"
#include "nwstk.h"

udpCb_t   *udpCbList;

udpCb_t *udpSearchCb(UINT16 dport);
void udpHhtons(udpHdr_t *pUh);
void udpHntohs(udpHdr_t *pUh);

/*******************************************************************************
* Name : udpIn
* Description :
*   This function is called by the ipIn() . Responsibility of this function
*   is to parse the packet whether this packet is ours or not . By seeing the
*   port number it serches the udp linked list if that port is there in udp 
*   list then it returns that control block . after getting udp control block
*   pointer this function queues packet to this control block ,and gives
*   the semaphore.Other wise it frees the packet.
* parameters : 
*   Input : pktBuf_t pointer variable
* Returns  :
*    Nothing
*******************************************************************************/
void udpIn(pktBuf_t *pkt)
{
  udpHdr_t  *pUh;
  udpCb_t   *pUcb;

  pUh  = (udpHdr_t *) &pkt->buf[14 + 20];
  udpHntohs(pUh);
  pUcb = udpSearchCb(pUh->dport);
  if(!pUcb)
  {
    //search failed 
    pktFree(pkt);
    return;
  }
  pUcb->pktCnt++;
  pktEnQ(pUcb->pCbpktQ, pkt);
  semGive(pUcb->semID);
}

/*******************************************************************************
* Name: udpSocket
* Description :
*     This function is called by the socket function . This function allocate
*  memory for one udp control block , initialize the control block ,and adds
*  that control block to udp list.it returns the control block pointer.
* Parameters :
*    Input : protocol
* Returns :
*   Success : control block pointer.
*   Failure : NULL.
*******************************************************************************/
udpCb_t *udpSocket(int protocol)
{
   udpCb_t *pUdpCb = (udpCb_t *)malloc(sizeof(udpCb_t));
   
   if(pUdpCb == NULL)
   {
     printf("UDP socket failed\n");
     return NULL;
   }
   pUdpCb->pktCnt = 0;
   pUdpCb->state  = 0;
   pUdpCb->pCbpktQ= (pktQ_t *) malloc(sizeof(pktQ_t));
   pUdpCb->semID  = semBCreate(0,0);
   pUdpCb->pNext  = udpCbList;
   udpCbList      = pUdpCb;
   return pUdpCb;
}
/*******************************************************************************
* Name: udpBind
* Description :
*   This function is called by the bind system call. Responsibility of the
*   function is fill the port number and ip address in udpcontrol block , it
*   adds the state as BIND_BIT set.if all fine then it returns sucess otherwise
*   it returns the error.
* Parameters :
*   Input : control block pointer , 
*           sockaddr_in pointer variable
*           len of the sockaddr_in structure.
* Returns :
*   All are fine it returns SUCCESS other wise it returns ERROR.
*
*******************************************************************************/
int udpBind(udpCb_t *pSockCb, struct sockaddr_in *addr, int addLen)
{

  if(pSockCb == NULL)
  {
    printf("UDP BIND ERROR\n");
    return ERROR;
  }
  if(addr == NULL)
  {
    printf("udp bind error\n");
    return ERROR;
  }
  //Check whether port is already bind or not
  if(udpSearchCb(addr->sin_port))
    return ERROR;
  pSockCb->lport = addr->sin_port;
  memcpy(pSockCb->lip, (UINT8 *)&addr->sin_addr.s_addr, 4);
  pSockCb->state  |= BIND_BIT;
  return SUCCESS;
}
/*******************************************************************************
* Name: udpConnect
* Description :
*   This function is called by the connect system call. Responsibility of
*   this function is fill the port number and ip address of the destination in
*   udp control block, and sets the state as CONNECTED.Finally if all are fine
*   it returns SUCCESS otherwise it returns ERROR.
* Parameters :
*   Input :   udp control block pointer.
*             sockaddr_in structre pointer variable
*             size of the sockaddr_in structure.
* Returns :
*      if all are fine then it returns SUCCESS otherwise it returns the ERROR.
*******************************************************************************/
int udpConnect(udpCb_t *pSockCb, struct sockaddr_in *addr, int addLen)
{
  if(pSockCb == NULL)
  {
    printf("error in pSockCb\n" );
    return ERROR;
  }
  if(addr == NULL)
  {
    printf("error in sockaddr_in\n" );
    return ERROR;
  }
  pSockCb->rport = addr->sin_port;
  memcpy(pSockCb->rip, (UINT8 *)&addr->sin_addr.s_addr, 4);
  pSockCb->state = (pSockCb->state | CONNECT_BIT);
  return SUCCESS;
}

/*******************************************************************************
* Name: udpSendto
* Description :
*   This function is called by the sendto() system call . First it sees the
*   whether the state of the control block is CONNECTED or BINDED. if not then
*   it sees whether user sends valid sockaddr_in structure varaible.if all are
*   fine it allocates memory for one MBuf_t pointer variable using mbufAlloc()
*   function .This function extracts the source and destination port numbers
*   and fills those port numbers in udp structure and also fills the len of
*   the buffer and check sum is zero.Finally we send this mbuf to ip layer
*   using the ipSendPkt() function .
* Parameters :
*    Input :  udp control block pointer.
*             buffer of user
*             length of that buffer
*             flags if any 
*             sockaddr_in structure pointer variable
*             size of the sockaddr_in structure.
* Returns :
*    if all are fine it returns how much data it sended  other wise it
*   returns ERROR.
*
*******************************************************************************/
int udpSendto(udpCb_t *pucb, INT8 *buf, INT32 len, INT32 flags,
              struct sockaddr_in *pcliAdr, int length) 
{
  
  int ii;
  UINT8     dstAdr[4];
  udpHdr_t *pudp;
  pktBuf_t *pkt;
  printf("we r in udp send  to\n" );
  if(((pucb->state & CONNECT_BIT) == 0) && (pcliAdr == NULL))
    return ERROR;

  if((pucb->state & BIND_BIT) == 0)
  {
    pucb->lport  = ntohs(allocLocalPort()); 
    pucb->state |= BIND_BIT;
  }

  pkt = pktAlloc(0, len + HDR_LEN);
  if(pkt == NULL)
    return ERROR;

  memcpy((pkt->buf + HDR_LEN), buf, len);
  pudp = (udpHdr_t *)(pkt->buf + HDR_LEN - sizeof(udpHdr_t));
  pudp->sport  = pucb->lport;

  if( pcliAdr )
  { 
    memcpy(dstAdr,&pcliAdr->sin_addr.s_addr,4); 
    pudp->dport = pcliAdr->sin_port;
  }
  else     
  {
    pudp->dport  = pucb->rport;
    memcpy(dstAdr,pucb->rip,4);
  }
  pudp->cksum = 0;
  pudp->len    = sizeof(udpHdr_t)+len;
  //pudp->len = ntohs(pudp->len);
  pkt->len = len+ sizeof(udpHdr_t); 
  //printf("sending UDP packet %d\n",pkt->len);
  //printf("sport %d\ndport %d\nlen %d\n",htons(pudp->sport),htons(pudp->dport),
  //		                        htons(pudp->len));
  udpHhtons(pudp);

  ipSendPkt(pkt, dstAdr, UDP_PROTO); 

  return len;
}


/*******************************************************************************
* Name : udpRecvRrom
* Description :
*   This function is called by the recvfrom system call. Responsibility of
*   this function is recieve the data segment from ip layer.Initially it waits
*   on semaphore for the packet . ip layer queues the packet into udp control
*   block and gives the semaphore , then this function takes the semaphore and
*   de queues the packet from the control block queue, parse the packet finally
*   it extractes the data from packet and copies into users buffer and also it
*   fills the port number and ip address of the destination machine 
*   sockaddr_in structure and fills the size of the structure size in
*   structlen variable.
* Parameteres :
*   Input : control block pointer 
*           len of the buffer
*           flags 
*   Output : users buffer where this function fills data 
*            sockadd_in structure pointer where we fill port number and 
*                                            ip address of destination .
*            structlen fills the size of the sockaddr_in structure.
* Returns :
*   if all are fine we return length of the data we copied in users
*   buffer other wise it returns ERROR.
*******************************************************************************/
int udpRecvFrom(udpCb_t *pucb, INT8 *buf, int len, UINT32 flags, 
                struct sockaddr_in *pAdIn, int *structlen) 
{
  int length, port;
  udpHdr_t *udpHdrp;
  UINT8    *ipAdrs;
  pktBuf_t *pkt;
  unsigned short mlen;
  
  /******* waiting for receive semaphore *******/
  while(pucb->pktCnt == 0)
    semTake(pucb->semID,WAIT_FOREVER);

  pkt = pktDeQ(pucb->pCbpktQ);
  pucb->pktCnt--;

  if(structlen)
    *structlen = sizeof(*pAdIn);
  if(pkt == NULL)
    return ERROR;

  udpHdrp = (udpHdr_t *)(pkt->buf + HDR_LEN - sizeof(udpHdr_t));
  mlen = udpHdrp->len - sizeof(udpHdr_t);
  //ntoH(&mlen,2);
  //mlen = mlen - sizeof(udpHdr_t);
  length = (mlen < len) ? mlen : len;
  memcpy(buf, pkt->buf+HDR_LEN, length);
  if(pAdIn)
  {
    pAdIn->sin_port = udpHdrp->sport;
    memcpy(&pAdIn->sin_addr.s_addr, pkt->buf+14+12, 4);
  }
  pktFree(pkt);
  return length;
}

/*************************************************************************
* Name : udpclose(udpcb_t *pSockCb.pSockCb);
* Description :
*   This function is called by the close system call .This free the 
*   udp control block.
* Parameters : udp control block pointer.
*************************************************************************/
int udpclose(udpCb_t *pSockCb)
{
  udpCb_t *udpCbListp, *temp;
  temp = udpCbListp = udpCbList;

  if(pSockCb == NULL)
  {
    printf("UDP close error\n");
    return ERROR;
  }
  while(udpCbListp != NULL)
  {
    if(udpCbListp == pSockCb)
    {
      if(udpCbListp == udpCbList)
      {
        udpCbList = udpCbListp->pNext;
        free(udpCbListp);
        return 	SUCCESS;
      }
      else
      {
        temp->pNext = udpCbListp->pNext;
        //udpCbList = temp;
        free(udpCbListp);
        return SUCCESS;
      }
    }
    else
    {
      temp = udpCbListp;
      udpCbListp = udpCbListp->pNext;
    }
  }
  printf("UDP close error\n");
  return ERROR;
}

/*******************************************************************************
* Name : udpSearchUcb
* Decription :
*   This function searches the given port number in udp control block list.
*   If the port number matches in any control block then it returns that
*   pointer other wise it returns NULL.
* Parameters : 
*   Input :   Port number
* Returns : control block pointer
*******************************************************************************/
udpCb_t *udpSearchCb(UINT16 dport)
{
  udpCb_t *pudpCbList;
  pudpCbList = udpCbList;

  while(pudpCbList != NULL)
  {
    if(pudpCbList->lport == dport)
      return pudpCbList;
    pudpCbList = pudpCbList->pNext;
  }

  return NULL;
}
/*************************************************************************
* Name: allocLocalPort
* Description :
*   This function allocates one new port number which is not there in udp
*   control block list.it is unique
* Parameters : none
* Returns :    Port number
*************************************************************************/
int allocLocalPort()
{
  static unsigned short port = 5024;
  while(1)
  {
    port++;
    if(udpSearchCb(port)==NULL)
      return port;
  }
}

/*******************************************************************************
* Name: displayCtlBlk()
* Description :
*   This function displays all the UDP control blocks present in the linked
*   list.
*******************************************************************************/
int displayCtlBlk()
{
  int ii;
  udpCb_t *udpCbListp;
  udpCbListp = udpCbList;

  if(udpCbListp == NULL)
  {
     printf("there is no control blocks\n");
  }
  while(udpCbListp != NULL)
  {
    printf("state = %x\n",udpCbListp->state);
    printf("local ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",udpCbListp->lip[ii]);
    printf("\n");
    printf("destination ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",udpCbListp->rip[ii]);
    printf("\n");
    printf("local port = %d\n",htons(udpCbListp->lport));
    printf("destination port = %x\n",htons(udpCbListp->rport));
    printf("packet count = %d\n",udpCbListp->pktCnt);

    udpCbListp = udpCbListp->pNext;
  }

}

/******************************************************************************
 * Name : udpHtons
 * Description:
 *  This function convert the udp header host to network order.
 * Parameters: 
 *   udpHdr_t pointer 
 *****************************************************************************/
void udpHhtons(udpHdr_t *pUh)
{
  pUh->len = htons(pUh->len);
}
/******************************************************************************
 * Name : udpHntohs
 * Description:
 *  This function covert the udp header network to host order.
 * Parameters:
 *  udpHdr_t pointer.
 *****************************************************************************/
void udpHntohs(udpHdr_t *pUh)
{
  pUh->len = htons(pUh->len);
}
