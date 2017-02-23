/**** the copy of this program in the ctcp.c **********/

#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "nwutil.h"
#include "tcpnwstk.h"

void preparePsuedoHdr(UINT8 *psuedoHdr,tcpHdr_t *tcpHdr, ipHdr_t *ipHdr);

INT32 prepareAndSendFINACKpkt(tcpCb_t *tcb,UINT8 *buf);
UINT32 alarmStart(INT32 tmOutInMilliSecs,void(*fp)(void *arg),void *arg);
void tcpRstEvtProc(tcpCb_t *tcb, pktBuf_t *pkt);
void timeOut(tcpCb_t *);
INT32 prepareAndSendAckpkt(tcpCb_t *, pktBuf_t *);
UINT16 computechecksum(UINT8 *psuedoHdr, pktBuf_t *pkt, INT16 len);
INT32 deleteTcpBlock(tcpCb_t *pnode);
INT32 prepareAndSendFINpkt(tcpCb_t *tcb,UINT8 *buf);
UINT32 tcpSearchLstCb(ipHdr_t *ipHdr,tcpHdr_t *tcpHdr);
UINT32 tcpSearchNonLstCb(ipHdr_t *ipHdr,tcpHdr_t *tcpHdr);
void tcpFinEvtProc(tcpCb_t *, pktBuf_t *);
void tcpAckEvtProc(pktBuf_t *,tcpCb_t *);
extern tcpCb_t *pNonListenQ, *pListenQ;

/*******************************************************************************
* Function Name : tcpIn()
* Description   : 
-> This function is called from the ipIn().

-> This function first calculates the checksum and if it is correct 
   then only it accepts the incoming packet otherwise it drops that 
   packet.

-> If the checksum is correct then this function calls various function
   depending upon the type of the incoming packet.

-> If the checksum is correct and the incoming packet doesn't belong to
   any of the blocks i.e. listen blocks or non-listen blocks, then it
   prepares and send RST packet to the sender.
   
* Parameters    :
     Input      : The inconing packet.
* Returns       :
-> SUCCESS or ERROR.
**********************************************************************/

INT32 tcpIn(pktBuf_t *pkt)
{
  tcpCb_t *tcpCb;
  UINT16 hdrlen;
  UINT16 pktLen;
  UINT32 zeros = 0x0000;
  UINT16 chksum;
  UINT8  psuedoHdr[12];
  pktBuf_t *ackpkt;   //

  ipHdr_t  *ipHdr   = (ipHdr_t *) (pkt -> data - IP_HDR_LEN);
  tcpHdr_t *tcpHdr  = (tcpHdr_t *)pkt -> data;


  hdrlen = ntohs(tcpHdr -> hdrlen);
  memset(&psuedoHdr,0,sizeof(psuedoHdr));
  preparePsuedoHdr(psuedoHdr, tcpHdr, ipHdr);

  pktLen = ipHdr -> pktLen - IP_HDR_LEN;
  pktLen = ntohs(pktLen);

    
  if((chksum = computechecksum(psuedoHdr, pkt, pktLen)))
  {
    printf("Check sum calculation Failed and cksum = %x\n",chksum);    
    pktFree(pkt);
    return ERROR;
  }

  else
  {
    if((tcpCb = (tcpCb_t *)tcpSearchNonLstCb(ipHdr,tcpHdr)) == NULL)
    {
      if((tcpCb = (tcpCb_t *)tcpSearchLstCb(ipHdr,tcpHdr)) == NULL)
         ;
    }
 
    switch(tcpHdr -> ctrlflgs)
    {
      case SYN_PKT:
           tcpSynEvtProc(pkt,tcpCb);
           break;

      case SYN_ACK_PKT:
           tcpCb -> tmout = alarmStop(tcpCb -> timerid);
           tcpSynAckEvtProc(pkt,tcpCb);
           break; 

      case PSH_PKT:
      case PSH_ACK_PKT:
           if(tcpCb -> windflag == 1)
           {
             tcpCb -> windflag =0;
           }
           if(tcpCb->state == FIN_WAIT1)
             tcpCb->state = FIN_WAIT2;
           tcpDataEvtProc(pkt,tcpCb);
           break;

      case FIN_PSH_ACK_PKT:
           if(tcpCb -> state == FIN_WAIT1)
             tcpCb -> state = TIME_WAIT;
           tcpDataEvtProc(pkt, tcpCb);
           break;

      case FIN_PKT:
      case FIN_ACK_PKT:
           tcpFinEvtProc(tcpCb,pkt);
           if(FIN_ACK_PKT)
              tcpAckEvtProc(pkt,tcpCb);
           break;

      case ACK_PKT:  
           tcpCb -> tmout = alarmStop(tcpCb -> timerid);         
           if(tcpCb -> windflag == 1)
           {
             ackpkt = pktAlloc();
             if(ackpkt == NULL)
             { 
               printf("pkt allocation failed in AckEvtProc() \n");
               return ERROR;
             } 
             prepareAck(ackpkt,tcpCb);
             ackpkt->len = 20;
             ipSendPkt(ackpkt,tcpCb -> rip, TCP_PROTO);
             break ;
            }
          
           tcpAckEvtProc(pkt,tcpCb);
           break;

      case RST_PKT:
      case RST_ACK_PKT:
           tcpRstEvtProc(tcpCb, pkt);
           break;

   }

 }
       
}


/**********************************************************************
* Function Name : computechecksum()
* Description   : 
-> This fucntion calculates the checksum. And return it to the calling 
   function.
* Parameters    :
    Input       : Pointer to the psuedoHdr buffer,
                  The address of the packet and
                  The length of the TCP header.
* Returns       :
-> It returns the checksum.
**********************************************************************/
UINT16 computechecksum(UINT8 *psuedoHdr, pktBuf_t *pkt, INT16 len)
{
  UINT16 *pShort,check= 0;
  UINT16 temp = 0;
  UINT16 word = 0,tempword = 0;
  unsigned int result=0;
  int i,j;

  pShort = (UINT16 *) psuedoHdr;
  for(i=0;i<6;i++)
  {
    result+= *pShort++;
  }
  pShort = (UINT16 *) pkt->data;

  //if payload len is odd then make it even by adding null bit.

  if(ntohs(len)%2!=0)
  {
    pkt->data[ntohs(len)] = 0;
    for(i=0; i < (ntohs(len) + 1) / 2;i++)
      result+= *pShort++;
  }

  else  
    for(i=0;i< ntohs(len)/2;i++)
      result+= *pShort++;

  result = (result>>16) + ( result & 0xffff );
  result += (result>>16);
  result = (result & 0xffff) ;
  temp = result;
  //printf("Compute Checksum  %x\n",~temp);
  return ~result;

 }

 
/**********************************************************************

* Function Name : tcpSearchNonLstCb()
* Description   :
-> This function searches the non listen list to which block the packet
   belongs to....? By checking the local ip, local port, dst ip and 
   dst port with the dst ip, dst port, src ip and sorc port
   respectively.
-> If any of the block mathces with the above four fields it returns 
   the address of that control block.
-> If none of the block matches with the above four fields the it 
   returns NULL.
* Parameters    :
    Input       : Header of linked list,
                  ip part of the packet and
                  tcp part of the packet.
* Returns       :
-> It returns the address of the control block.
**********************************************************************/
UINT32 tcpSearchNonLstCb(ipHdr_t *ipHdr,tcpHdr_t *tcpHdr) //N
{
  tcpCb_t *temp;  
  temp = pNonListenQ;
  int ret;
 
  while(temp != NULL)
  {
    if((ret = memcmp(ipHdr -> srcAdrs, temp -> rip, 4) == 0)
      && (ntohs(tcpHdr -> srcport) == ntohs(temp -> rport))
      && (ret = memcmp(ipHdr -> dstAdrs, temp -> lip, 4) == 0)
      && (ntohs(tcpHdr -> dstport) == ntohs(temp -> lport)))
    {
       //printf("\nthe matched non listen block = %x\n",temp);
   //    printf("\nreturn temp\n");
       return (UINT32)temp;
    }

//    printf("temp");
    temp = temp -> pnxt;
  }
//  printf("\nreturn NULL\n");
  return NULL;
}

/**********************************************************************
* Function Name : tcpSearchLstCb()
* Description   :
-> This function searches the listen list to which block the packet
   belongs to....? By checking the local ip and local port with the 
   dst ip, dst port of the packet respectively.
-> If any of the block mathces with the above two fields it returns 
   the address of that control block.
-> If none of the block matches with the above four fields the it 
   returns NULL.
* Parameters    :
    Input       : Header of linked list,
                  ip part of the packet and
                  tcp part of the packet.
* Returns       :
-> It returns the address of the control block.
**********************************************************************/
UINT32 tcpSearchLstCb(ipHdr_t *ipHdr,tcpHdr_t *tcpHdr)//L
{
  tcpCb_t *temp; 
  int ret;
  temp = pListenQ;


  while(temp != NULL)        
  {
    //printf("\nsearching non listen control block.\n");
      if((ret = memcmp(ipHdr -> dstAdrs, temp -> lip, 4) == 0)
      && (ntohs(tcpHdr -> dstport) == ntohs(temp -> lport)))
     {
        return (UINT32)temp;
     }

    temp = temp -> pnxt;
  }
  return NULL;
} 


/*********************************************************************
* Function Name : prepareAndSendRSTpkt()
* Description   :
-> This function prepares and sends RST packet, if any received packet
   does not belong to it.
* Parameters    :
    Input       : ip part of the received packet and
                  the tcp part of the received packet.
* Returns       :
***********************************************************************/
INT32 prepareAndSendRSTpkt(ipHdr_t *ipHdr, tcpHdr_t *tcpHdr)
{
  pktBuf_t *pkt;
  UINT8 dstAdr[4];
  UINT8 psuedoHdr[12];
  tcpHdr_t *sndTcpHdr,*tempHdr;
  UINT16 pktLen;
  tcpCb_t *tcb;
 
  UINT8 zeros = 0x0000;

  //if(tcpHdr -> ackno == 0)
  //tempHdr -> seqno = 9348;

  preparePsuedoHdr(psuedoHdr, tcpHdr, ipHdr);

  //the next seqno will b in tcb block.
  pkt = pktAlloc();

  if(pkt == NULL)  
  {
    printf("\nthere is no free  pakets in the queue\n");
    return ERROR;
  }

  sndTcpHdr = (tcpHdr_t *)&(pkt -> buf[ETH_HDR_LEN + IP_HDR_LEN]);

  memcpy(dstAdr, &ipHdr -> srcAdrs, 4);//here we r sending the dst ip 
                                       //address to the ip layer.

  preparePsuedoHdr(psuedoHdr,tcpHdr,ipHdr);

  sndTcpHdr -> srcport   = tcpHdr -> dstport;
  sndTcpHdr -> dstport   = tcpHdr -> srcport;
  sndTcpHdr -> seqno     = 0;
  sndTcpHdr -> ackno     = htonl(tcpHdr -> seqno + 1);
  sndTcpHdr -> hdrlen    = 0x50;
  sndTcpHdr -> ctrlflgs  = RST_ACK_PKT;
  sndTcpHdr -> wndsize   = 0;
  sndTcpHdr -> chksum    = 0;
  sndTcpHdr -> urgptr    = 0;

  pkt -> len             = TCP_HDR_LEN;
  sndTcpHdr -> chksum    = computechecksum(psuedoHdr, pkt,                                           htons(TCP_HDR_LEN));

  //printBuf(pkt->buf,pkt->len);

  ipSendPkt(pkt,dstAdr,TCP_PROTO);
  tcb -> tmout   = 250;
  tcb -> timerid = alarmStart(tcb -> tmout,(void *)timeOut, tcb);  
}


/***********************************************************************
* Function Name : tcpFinEvtProc()
* Description   :
-> This function handles the FIN event.
-> Depending upon the state it switches to that state and then calls 
   prepareAndSendFinAckpkt() function.
* Parameters    :
    Input       : The incoming packet,
                  and the tcp Control block.
* Returns       :
**********************************************************************/
void tcpFinEvtProc(tcpCb_t *tcb, pktBuf_t *pkt)
{ 
  tcpHdr_t *tcpHdr;
  tcpHdr = (tcpHdr_t *)(pkt -> data);
  tcb -> nrsn = htonl(tcpHdr -> seqno) + 1;
  
  switch(tcb -> state)
  {
     case ESTABLISHED:
       prepareAndSendAckpkt(tcb, pkt);
       tcb -> state = CLOSE_WAIT;
       semGive(tcb->rxsem);
       break;

     case FIN_WAIT2:
       prepareAndSendAckpkt(tcb, pkt);
       tcb -> state = TIME_WAIT;
       semGive(tcb->rxsem);
       break;
  }
}

/**********************************************************************
* Function Name : prepareAndSendAckpkt()
* Description   :
-> This function prepares and sends the acknowledgement to the received
   FIN packet.
* Parameters    :
    Input       : The received incoming packet,
                  and the tcp control block.
**********************************************************************/
INT32 prepareAndSendAckpkt(tcpCb_t *tcb, pktBuf_t *ppkt)
{
  pktBuf_t *pkt;
  UINT8 dstAdr[4];
  UINT8 psuedoHdr[12];
  tcpHdr_t *sndTcpHdr,*tempHdr;
  tcpHdr_t *tcpHdr;
  ipHdr_t *ipHdr;
  tcpCb_t  *temp;
  UINT16 pktLen;
 
  tcpHdr = (tcpHdr_t *) (ppkt -> data);
  ipHdr  = (ipHdr_t *)  (ppkt -> data - IP_HDR_LEN);

  UINT8 zeros = 0x0000;

  preparePsuedoHdr(psuedoHdr,tcpHdr,ipHdr);

  //the next seqno will b in tcb block.
  pkt = pktAlloc();

  if(pkt == NULL)  
  {
    printf("\nthere is no free  pakets in the queue\n");
    return ERROR;
  }

  sndTcpHdr = (tcpHdr_t *)(pkt -> data - TCP_HDR_LEN);

  memcpy(dstAdr, &ipHdr -> srcAdrs, 4);//here we r copying the dst ip 
//address because this add is not avilable in ip layer.

  
  tcb -> nsn          = htonl(tcpHdr -> ackno);
  tcb -> lwin         = ntohs(tcpHdr -> wndsize);
  tcb -> rwin         = BUF_SIZE - tcb -> rrix;
  tcb -> nrsn         = htonl(tcpHdr -> seqno) + 1;
    
  sndTcpHdr -> srcport  = tcb -> lport;
  sndTcpHdr -> dstport  = tcb -> rport;
  sndTcpHdr -> seqno    = htonl(tcb -> nsn);
  sndTcpHdr -> ackno    = htonl(tcb -> nrsn);
  sndTcpHdr -> hdrlen   = 0x50;
  sndTcpHdr -> ctrlflgs = ACK_PKT;
  sndTcpHdr -> wndsize  = htons(tcb->rwin);//0;  //htons(tcb -> rwin);it should b changed
                              //according to sliding window protocol.
  sndTcpHdr -> chksum   = 0;
  sndTcpHdr -> urgptr   = 0;

  pkt -> len = TCP_HDR_LEN;

  pkt->data=(UINT8 *)sndTcpHdr;
  sndTcpHdr -> chksum = computechecksum(psuedoHdr, pkt,                                           htons(TCP_HDR_LEN));
  ipSendPkt(pkt,dstAdr,TCP_PROTO);
}  

/***********************************************************************
* Function Name : tcpClose()
* Description   :
-> This function sends the FIN packet depending upon the state.
* Parameters    :
     Input      : The control block of the socket,
                  the buffer and
                  the length of the data.
***********************************************************************/
INT32 tcpClose(tcpCb_t *tcb, UINT8 *buf, INT32 len)
{
  switch(tcb -> state)
  {
    case CLOSE_WAIT:
	tcb->state = LAST_ACK;
        prepareAndSendFINpkt(tcb,buf);
        semTake(tcb->rxsem,WAIT_FOREVER);
        return SUCCESS;
        break;

    case ESTABLISHED:
      tcb -> state  = FIN_WAIT1;
      prepareAndSendFINpkt(tcb,buf);
      semTake(tcb->rxsem,WAIT_FOREVER); 
      return SUCCESS;
      break;

    case FIN_WAIT2:
	tcb->state = TIME_WAIT;
	prepareAndSendAckpkt(tcb,(pktBuf_t *)buf);
	return SUCCESS;
	break;
  }      
}


/**********************************************************************
* Function Name :
* Description   :
-> This function prepares and sends a FIN packet.
* Parameters    :
    Input       : The control block of the socket.
**********************************************************************/
INT32 prepareAndSendFINpkt(tcpCb_t *tcb,UINT8 *buf)
{
  pktBuf_t  *pkt;
  iface_t   *pIf;
  UINT8	    psuedoHdr[12];
  ipHdr_t   *ipHdr;
  UINT8     dstAdrs[4];
  UINT32 zeros = 0x0000;
  UINT16    pktLen;
  
  if(tcb == NULL)
    return ERROR;

  //preparePsuedoHdr(psuedoHdr, rvdtcpHdr, ipHdr);

  memcpy(&psuedoHdr[0], &tcb -> lip, 4);
  memcpy(&psuedoHdr[4], &tcb -> rip, 4);
  psuedoHdr[8] = zeros;
  psuedoHdr[9] = TCP_PROTO;
  pktLen = htons(TCP_HDR_LEN);
  memcpy(&psuedoHdr[10], &pktLen, 2);
 
  
  pkt = pktAlloc();
  if(pkt == NULL)
  {
    printf("\nthere is no free buffers in packet queue...\n");
    return ERROR;
  }

  tcpHdr_t *tcpHdr = (tcpHdr_t *)(pkt ->data -  TCP_HDR_LEN);

  pIf = ifaceTbl[1];


  tcpHdr -> srcport  = tcb -> lport;
  tcpHdr -> dstport  = tcb -> rport;
  tcpHdr -> seqno    = htonl(tcb -> nsn);

  tcpHdr -> ackno    = htonl(tcb -> nrsn);
  tcpHdr -> hdrlen   = 0x50;
  tcpHdr -> ctrlflgs = FIN_PKT;
  tcpHdr -> wndsize  = htons(tcb -> lwin);
  tcpHdr -> chksum   = 0;
  tcpHdr -> urgptr   = 0;

  pkt -> len = TCP_HDR_LEN;
  memcpy(dstAdrs, &tcb -> rip, 4);
  pkt->data=(UINT8 *)tcpHdr;
  tcpHdr -> chksum = computechecksum(psuedoHdr, pkt,                                            htons(TCP_HDR_LEN));

  ipSendPkt(pkt, dstAdrs, TCP_PROTO);
  tcb -> timerid = alarmStart(tcb -> tmout,(void *)timeOut, tcb);
}

/**********************************************************************

* Function Name : tcpAckEvtProc()
  -------- ----

* Description   :
  -----------

-> This function handles the ACK event.

-> Depending upon the state it calls differnt functions or simply it 
   will change its state to another state.

**********************************************************************/

/*
void tcpAckEvtProc(tcpCb_t *tcb, tcpHdr_t *tcpHdr,ipHdr_t *ipHdr)
{
  switch(tcb -> state) 
  {
    case FIN_WAIT1 :
      tcb -> state |= FIN_WAIT2;
      break;

    //case FIN_WAIT2 :
      //prepareAndSendAckpkt(tcb, tcpHdr, ipHdr);
     // tcb -> state |= TIME_WAIT;
     // break;

    case TIME_WAIT:
      //alarmStart(tcb -> tmout, tmOut, tcb);
      tcb -> state |= CLOSED;
      break;
      
    case LAST_ACK :
      tcb -> state |= CLOSED;
      break;
  }
}
*/

void preparePsuedoHdr(UINT8 *psuedoHdr,tcpHdr_t *tcpHdr, ipHdr_t *ipHdr)
{
  UINT16 pktLen;
  UINT32 zeros = 0x0000;

  memcpy(&psuedoHdr[0], (char *)ipHdr -> srcAdrs, IP_ADD_LEN);
  memcpy(&psuedoHdr[4], (char *)ipHdr -> dstAdrs, IP_ADD_LEN);
  psuedoHdr[8] = 0;
  psuedoHdr[9] = ipHdr -> proto;
  pktLen = ipHdr -> pktLen - IP_HDR_LEN;
  pktLen = ntohs(pktLen);
  memcpy(&psuedoHdr[10], &pktLen, 2);
}

/**********************************************************************
* Function Name : prepareAndSendFINACKpkt
* Description   :
-> This function prepares and sends a FIN_ACK_PKT.
* Parameters    :
    Input       : The tcp contol block
***********************************************************************/
INT32 prepareAndSendFINACKpkt(tcpCb_t *tcb,UINT8 *buf)
{
  pktBuf_t  *pkt;
  iface_t   *pIf;
  UINT8	    psuedoHdr[12];
  ipHdr_t   *ipHdr;
  UINT8     dstAdrs[4];
  UINT32 zeros = 0x0000;
  UINT16    pktLen;
  
  if(tcb == NULL)
    return ERROR;

  //preparePsuedoHdr(psuedoHdr, rvdtcpHdr, ipHdr);

  memcpy(&psuedoHdr[0], &tcb -> lip, 4);
  memcpy(&psuedoHdr[4], &tcb -> rip, 4);
  psuedoHdr[8] = zeros;
  psuedoHdr[9] = TCP_PROTO;
  pktLen = htons(TCP_HDR_LEN);
  memcpy(&psuedoHdr[10], &pktLen, 2);
 
  //printf("\npsuedoHdr (FIN):");
  //printBuf(psuedoHdr,12);

  pkt = pktAlloc();
  if(pkt == NULL)
  {
    printf("\nthere is no free buffers in packet queue...\n");
    return ERROR;
  }

  tcpHdr_t *tcpHdr = (tcpHdr_t *)&(pkt ->buf[ETH_HDR_LEN + IP_HDR_LEN]);

  pIf = ifaceTbl[1];

  /*printf("\ntcb -> lport :%x\n",ntohs(tcb -> lport));
  printf("\ntcb -> rport :%x\n",ntohs(tcb -> rport));*/

  tcpHdr -> srcport  = tcb -> lport;
  tcpHdr -> dstport  = tcb -> rport;
  tcpHdr -> seqno    = htonl(tcb -> nsn);
  tcpHdr -> ackno    = htonl(tcb -> nrsn);
  tcpHdr -> hdrlen   = 0x50;
  tcpHdr -> ctrlflgs = FIN_ACK_PKT;
  tcpHdr -> wndsize  = 0;
  tcpHdr -> chksum   = 0;
  tcpHdr -> urgptr   = 0;

  pkt -> len = TCP_HDR_LEN;
  memcpy(dstAdrs, &tcb -> rip, 4);
  tcpHdr -> chksum = computechecksum(psuedoHdr, pkt,                                            htons(TCP_HDR_LEN));

  ipSendPkt(pkt, dstAdrs, TCP_PROTO);
  tcb -> timerid = alarmStart(tcb -> tmout,(void *)timeOut, tcb);
}


/**********************************************************************
* Function Name : tcpRstEvtProc
* Description   :
-> This function hadles the situation when we receives a RST_PKT or 
   RST_ACK_PKT from the other side.
* Parameters    :
     Input      : The tcp Contol block and
                  The recived packet.
***********************************************************************/
void tcpRstEvtProc(tcpCb_t *tcb, pktBuf_t *pkt)
{
  switch(tcb -> state)
  {
    case LISTEN:
    case SYN_SENT:
     //prepareAndSendAckpkt(tcb, pkt);
     tcb -> state = CLOSED;
     tcb -> errno = 1;
     semGive(tcb -> rxsem);
     break;

   case SYN_RCVD:
     prepareAndSendAckpkt(tcb, pkt);
     tcb -> state = CLOSED;
     break;

    case ESTABLISHED:
      prepareAndSendAckpkt(tcb, pkt);

      if(tcb -> lptr != NULL)
        tcb -> state = LISTEN;
    
      else
        tcb -> state = CLOSED;
      break;
  }
}


/**********************************************************************
* Function Name : deleteTcpBlock
* Description   :
-> This function deletes the tcp control block from the list and frees
   the memory allocated to it.
* Parameters    :
    Input       : The tcp Control blcok address.
**********************************************************************/
INT32 deleteTcpBlock(tcpCb_t *pnode)
{
   tcpCb_t *temp;
   temp = pnode;

   if((pnode -> pnxt == NULL) && (pnode->pprv == NULL))
   {
       pNonListenQ = NULL;
       free(temp);
       return SUCCESS;
   }
   
   else if(pnode -> pnxt == NULL)   //Tail
   {
       pnode -> pprv -> pnxt = NULL;
       free(temp);
       return SUCCESS;
   }
   else if(pnode -> pprv == NULL)   //Head
   {
       pNonListenQ = pnode -> pnxt;
       pNonListenQ -> pprv = NULL;
       free(temp);
       return SUCCESS;
   }
   else                                 //Middle
   {
       pnode -> pprv -> pnxt = pnode -> pnxt;
       pnode -> pnxt -> pprv = pnode -> pprv;
       free(temp);
       return SUCCESS;
   }
} 
 
