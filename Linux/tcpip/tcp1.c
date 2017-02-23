/***** this program to read the data  and it also include the BUF_SIZE
 while copying to the tcb -> rxbuf ******/
/******** it avoids the sillywindow syndrome created by the receiver **/
/******** it is to send Ack for the probewindows *******/

#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "ethdrv.h"
//#include "nwstk.h"
#include"tcpnwstk.h"


/********* function prototypes ***********/
UINT16 computeChksum(unsigned char *pseudoHdr,pktBuf_t *pkt,short Len);
tcpCb_t *tcpNLSearchCb(UINT16);
tcpCb_t *tcpLSearchCb(UINT16 port);
void prepareSyn(tcpCb_t *,pktBuf_t *);
//int allocLocalPort();
void timeOut(tcpCb_t *);
void probeTimeOut(tcpCb_t *);
void  addToNonLQList(tcpCb_t *);
UINT32 alarmStart(INT32 ,void(*fp)(void *arg),void *arg);
void prepareAck(pktBuf_t *,tcpCb_t *);
void prepareWinAck(pktBuf_t *,tcpCb_t *);
void prepareSynAck(pktBuf_t *,tcpCb_t *);
void addToLQList(tcpCb_t *);
INT32 prepareDataPkt(tcpCb_t *,pktBuf_t *);
void tcpDataEvtProc(pktBuf_t *,tcpCb_t *);
void tcpReadEvtProc(tcpCb_t *);
void copydata(pktBuf_t *,tcpCb_t *,INT32 ,INT32 );
INT32 copybuf(tcpCb_t *,UINT8 *,INT32 *);
INT32 min(INT32,INT32);

/*** pointers to ListenQ and Non-ListenQ linked lists *****/
tcpCb_t *pListenQ;
tcpCb_t *pNonListenQ;

/************ tcp function implementations *************/
/********** tcpSocket() fuction implementation **********/
tcpCb_t *tcpSocket(int protocol)
{
  tcpCb_t *tcb;
  
  tcb=(tcpCb_t *)malloc(sizeof(tcpCb_t));
  if(tcb==NULL)
  {
    printf("error at tcp control block creation \n");
    return NULL;
  }

  memset(tcb,0,sizeof(tcpCb_t));
  tcb->rxsem=semBCreate(0,0);
  tcb->txsem=semBCreate(0,0);
  tcb->mxsem=semBCreate(0,1);
  tcb->state= CLOSED;
  tcb->pnxt=NULL;
  tcb->pprv=NULL;
 
  return tcb;
}

/************ tcpBind() function implementation ***************/

INT32 tcpBind(tcpCb_t *tcb,struct sockaddr_in *addr,int len)
{
  // check the tcp control block and sockaddr
  if(tcb==NULL)
  {
    printf("invalid tcp control block \n");
    return ERROR;   
  }
  if(addr==NULL)
  {
    printf("invalid sockaddr error \n");
    return ERROR;
  }
  
  // check the port is already bind or not
  // if port already exists in bind, return error
  if(tcpLSearchCb(addr->sin_port))
   return ERROR;

   
  tcb->lport=addr->sin_port;
  memcpy(tcb->lip,(UINT8 *)&addr->sin_addr.s_addr,4);
  tcb->flags=BIND_BIT;
  return SUCCESS;
}


/************ tcpListen() function implementation **************/
INT32 tcpListen(tcpCb_t *tcb,int qlen)
{
  tcb->state=LISTEN;
  tcb->lqmax=qlen;

  // add this cb to listenQ
  addToLQList(tcb);
  //printf("\nsuccessfully added to listen list and pListenQ : %x\n",pListenQ);

 }

/********** tcpConnect() function implementation *************/
int tcpConnect(tcpCb_t *tcb,struct sockaddr_in *adr,int *adrlen)
{
  UINT8 dstadr[4];  
  pktBuf_t *pkt;
  iface_t *pif=ifaceTbl[1];

  // check the validity of the tcp control block 
  if(tcb == NULL)
  {
    // tcp control block is not valid
    printf("tcp cntol block is not avilable \n");
    return ERROR; 
  }
  
  // check the validy of destination address 
  if(adr == NULL)
  {
    printf("sockaddr is not valide one \n");
    return ERROR;
  }

  // lport
  if((tcb->flags & BIND_BIT) == 0)
  {
    tcb->lport=ntohs(allocLocalPort());//????????????
  }
   
  tcb->rport=adr->sin_port;
  memcpy(tcb->rip,(UINT8 *)&adr->sin_addr.s_addr,4);
  memcpy(dstadr,(UINT8 *)&adr->sin_addr.s_addr,4);
  // lip
  memcpy(tcb->lip,pif->ipAdrs,4);
  
  tcb -> txbuf=(unsigned char *)malloc(BUF_SIZE);
  tcb -> rxbuf=(unsigned char *)malloc(BUF_SIZE);
  tcb -> isn = ISN;
  tcb -> nsn = tcb -> isn+1;
  tcb -> avlsn = tcb -> isn;
  tcb -> lwin = INTIAL_WND_SIZE;
  pkt=pktAlloc();
  
  if(pkt==NULL)
  {
    printf("pkt Alloc ERROR\n");
    return ERROR;
  }

  prepareSyn(tcb,pkt);
  pkt->len = sizeof(tcpHdr_t) + 4;

  // add the SYN pkt to the tcpControl Block
  ipSendPkt(pkt,dstadr,TCP_PROTO);
  tcb->sendpkt=pkt;

  // add this cb to non-listenQ 
  addToNonLQList(tcb);

  // strt timer 250msec
  tcb->tmout=250;
  tcb->retrys=0;
  tcb->state=SYN_SENT;  
  tcb->timerid=alarmStart(tcb->tmout,(void *)timeOut,tcb);
  semTake(tcb->rxsem,WAIT_FOREVER); 
  puts("TAKEN SEMAPHORE\n\n\n"); 
  if(tcb->retrys==MAX_RETRYS)
  {
    printf("connection is not possible TIME OUT....\n");
    return ERROR;
  }
  return SUCCESS;
}


/************ tcpAccept() function implementation ************/
/*****Listen returns 0 on success, -1 on error ********/
INT32 tcpAccept(tcpCb_t *tcb,struct sockaddr_in *adr,int *adrLen)
{

  if(tcb->state != LISTEN)
  {
    printf("Accept Failed Error \n"); 
    return ERROR;
   }
   
  if(tcb->lqcnt>0) 
  {
    tcb->lqcnt--;
    // fill the sockaddr_in structure
    adr->sin_port = tcb->listenQ[tcb->lqcnt]->lport;
    memcpy(&adr->sin_addr.s_addr,&tcb->listenQ[tcb->lqcnt]->lip,4);
    return (int)tcb->listenQ[tcb->lqcnt];
  }
  semTake(tcb->rxsem,WAIT_FOREVER);
  if(tcb->errno) //if retrys reached the MAX_RETRYS return from accept
  {
    printf("Accept failed ......\n");
    return ERROR;
  }
  else
  {
    tcb->lqcnt--;
    adr->sin_port = tcb->listenQ[tcb->lqcnt]->lport;
    memcpy(&adr->sin_addr.s_addr,&tcb->listenQ[tcb->lqcnt]->lip,4);
    return (int)tcb->listenQ[tcb->lqcnt];
  }
}


//prepare  SYN Packet
void prepareSyn(tcpCb_t *tcb,pktBuf_t *pkt)
{
  tcpHdr_t *ptcp;
  UINT8 *pseudohdr;
  UINT16 chksum;  
  short hdrLen;
  short msslen = htons(MSS);

  ptcp=(tcpHdr_t *)(pkt->data - TCP_HDR_LEN );
  //printf("Pointr to tcp header:%x \n",ptcp);
  ptcp->srcport=tcb->lport;
  ptcp->dstport=tcb->rport;
  //printf("remote port is :%x \n",tcb->rport);
  //printf("pkt remote port is :%x \n",ptcp->dport);
  //printf("local port is:%x \n",tcb->lport);
  //printf("pkt local port is:%x \n",ptcp->sport);
  ptcp->seqno=htonl(tcb->isn);
  ptcp->hdrlen=0x60;  // tcp hdrlen + options(mss)
  ptcp->ctrlflgs=0x02;  
  ptcp->wndsize=htons(INTIAL_WND_SIZE);
  ptcp->chksum=0; //change after the calculation of checksum
  ptcp->urgptr=0;
  
  // send the MSS size
  pkt -> data[0] = 2;  // type
  pkt -> data[1] = 4;  // length
  memcpy(&pkt ->data[2],&msslen,2);  // MSS value
//printf("MSS Option is:");
//printBuf(pkt -> buf+ 56 , 2);

  // create the pseudoheader and calculate the checksum
  pseudohdr=(char *)malloc(12);
  memset(&pseudohdr,0,sizeof(pseudohdr));
  memcpy(&pseudohdr[0],(char *)tcb->lip,4);
  memcpy(&pseudohdr[4],(char *)tcb->rip,4);
  pseudohdr[8]=htons(0x0);
  pseudohdr[9]=TCP_PROTO;

  hdrLen = htons(24);
  memcpy(pseudohdr+10,&hdrLen,2);

  //printf("pseudohdr:\n");
  //printBuf(pseudohdr,12);
  pkt->data=(UINT8 *)ptcp;
  chksum=computeChksum(pseudohdr,pkt,hdrLen);
  ptcp->chksum=chksum; 
}

// checksum calculation function implementation
UINT16 computeChksum(unsigned char *pseudoHdr,pktBuf_t *pkt,short Len)
{
  UINT16 *pShort,check = 0;
  UINT16 temp = 0;
  UINT16 word = 0,tempword = 0;
  unsigned int result = 0;
  int i,j;

  pShort = (UINT16 *) pseudoHdr;
  for(i = 0;i < 6;i++)
  {
    result += *pShort++;
  }

  pShort = (UINT16 *) pkt->data;

  //if payload len is odd then make it even by adding null bit.

  if(ntohs(Len)%2 != 0)
  {
    pkt -> data[ntohs(Len)] = 0;
    for(i = 0; i < (ntohs(Len) + 1) / 2;i++)
      result += *pShort++;
  }

  else  
    for(i = 0;i < ntohs(Len)/2;i++)
      result += *pShort++;

  result  = (result >> 16) + ( result & 0xffff );
  result += (result >> 16);
  result  = (result & 0xffff) ;
  temp    = result;
  //printf("Compute Checksum  %x\n",~temp);
  return ~result;
}
 

// timeout function implementation
void timeOut(tcpCb_t *tcb)
{
  switch(tcb->state)    
  {
    case SYN_SENT:
      tcb->retrys++;
      if(tcb->retrys==MAX_RETRYS)
      {
        tcb->errno=1;
        semGive(tcb->rxsem);
        printf("IN timeOut GAVE SEMAPHORE\n\n\n"); 
      }
      else
      {
        tcb->tmout=2*tcb->tmout;
        tcb->timerid=alarmStart(tcb->tmout,(void *)timeOut,tcb);
      }
      break;     
    
    case ESTABLISHED:
      tcb->retrys++;
      if(tcb->retrys==MAX_RETRYS)
      {
        tcb->errno=1;
        semGive(tcb->rxsem);
        semGive(tcb->txsem);
      }
      else
      {
        tcb->tmout=2*tcb->tmout;
        tcb->timerid=alarmStart(tcb->tmout,(void *)timeOut,tcb);
      }
      break;

    case SYN_RCVD:
      tcb->retrys++;
      if(tcb->retrys==MAX_RETRYS)
      {
        tcb->errno=1;
        semGive((tcb->lptr)->rxsem); 
      //  printf("GAVE SEMAPHORE\n\n\n"); 
      }
      else
      {
        tcb->tmout=2*tcb->tmout;
        tcb->timerid=alarmStart(tcb->tmout,(void *)timeOut,tcb);
      }
      break;     

    case TIME_WAIT:
      deleteTcpBlock(tcb);
      tcb -> state = CLOSED;
      break;
  }
}

/*int allocLocalPort()
{
  static unsigned short port=5024;
  while(1)
  {
    port++;
    if(tcpNLSearchCb(port) == NULL)
     return port;
   }
   return NULL;
}***/


/********** search the port in non-listen Q  ************/
tcpCb_t *tcpNLSearchCb(UINT16 port)
{
  tcpCb_t *pnonlstcb;
  pnonlstcb=pNonListenQ;

  while(pnonlstcb != NULL)
  {
    if(pnonlstcb->lport == port)
      return pnonlstcb;
    pnonlstcb=pnonlstcb->pnxt;
  }
  return NULL;
}

/************* search the port in listen Q *************/
tcpCb_t *tcpLSearchCb(UINT16 port)
{
  tcpCb_t *plsttcb;
  plsttcb=pListenQ;

  while(plsttcb != NULL)
  {
    if(plsttcb->lport == port)
      return plsttcb;
    plsttcb=plsttcb->pnxt;
  }

  return NULL;
}

/************** add the TCB to Listen Q ****************/
void addToLQList(tcpCb_t *tcb)
{
  if(pListenQ==NULL) // if list is empty
  {
    pListenQ=tcb;
  }
  else // if list is non-empty,add at the head side
  {
    pListenQ->pprv=tcb;
    tcb->pnxt=pListenQ;
    pListenQ=tcb;
  }
}

/************** add the TCB to Non-Listen Q List ************/
void  addToNonLQList(tcpCb_t *tcb)
{
  if(pNonListenQ==NULL) // if list is empty
  {
    pNonListenQ=tcb;
    tcb->pnxt=NULL;
    tcb->pprv=NULL;
  }
  else // if list is non-empty,add at the head
  {
    pNonListenQ->pprv=tcb;
    tcb->pnxt=pNonListenQ;
    pNonListenQ=tcb;
  }
}


/************* tcpSynEvtProc() function implementation************/

void tcpSynEvtProc(pktBuf_t *pkt,tcpCb_t *tcb)
{
  tcpCb_t *pctcb;
  tcpHdr_t *ptcphdr;
  ipHdr_t *piphdr;
  pktBuf_t *pktsack;
  iface_t *pif=ifaceTbl[1];
  UINT8 rip[4];

  ptcphdr = (tcpHdr_t *)(pkt->data);  
  piphdr =(ipHdr_t *)(pkt-> data - IP_HDR_LEN);

  if(tcb->state == LISTEN)
  {
    // allocate the new tcb structure
    pctcb=(tcpCb_t *)malloc(sizeof(tcpCb_t));

    if(pctcb == NULL)
    {
      printf("new control block mem allocation failed \n");
      return ;
    }
    else
    {
      memset(pctcb,0,sizeof(tcpCb_t));
      // create the semaphores for the connected control block
      pctcb->txsem=semBCreate(0,0);
      pctcb->rxsem=semBCreate(0,0);
      pctcb->mxsem=semBCreate(0,1);

      // allocate txbuf & rxbuf for new tcb structure
      pctcb->txbuf=malloc(BUF_SIZE);
      pctcb->rxbuf=malloc(BUF_SIZE);
      
      // fill the rport & rip with the pkt lport & lip
      pctcb->rport = ptcphdr->srcport;
      memcpy(pctcb->rip,piphdr->srcAdrs,4);
      memcpy(rip,pctcb->rip,4);

      // lip & lport
      pctcb->lport = tcb->lport;
      memcpy(pctcb->lip,pif->ipAdrs,4);
  
      // add this to non-listen Q 
      addToNonLQList(pctcb);
      pctcb->state = SYN_RCVD;
      pctcb->nrsn = htonl(ptcphdr->seqno) + 1;
  
      // choose the isn to send SYN+ACK
      pctcb->isn = ISN2;
      pctcb->nsn = pctcb->isn+1;

         
      // prepare the SYN+ACK Packet
      pktsack=pktAlloc();
      if(pktsack == NULL)
      {
        printf("Pkt Allocation Failed \n");  
        return ;
      }

      // prepare SYN+ACK Packet
      prepareSynAck(pktsack,pctcb);
      pktsack->len = TCP_HDR_LEN+4;
      //printf("\n\nseding SYN+ACK PKT \n\n");
  //  printBuf(pktsack -> buf + ETH_HDR_LEN + IP_HDR_LEN, pktsack -> len);

      // send the SYN+ACK Packet
      ipSendPkt(pktsack,pctcb->rip,TCP_PROTO);

      // add SYN+ACK Packet to the TCB
      pctcb->sendpkt = pktsack;

      // save listen TCB associated with this new TCB
      pctcb->lptr = tcb;
   
      // start timer 250msec
      pctcb->tmout = 250;
      pctcb->retrys = 0;
      pctcb->timerid = alarmStart(tcb->tmout,(void *)timeOut,pctcb);//
      if(pctcb->retrys==MAX_RETRYS)
      {
        pktFree(pkt); 
        printf("connection is not possible \n");
        return ;
      }
    }
  }
  //(if state != LISEN & state ==SYN_RCVD)
  else if(tcb->state==SYN_RCVD)
  {
    // send the SYN+ACK Packet
    ipSendPkt(tcb->sendpkt,pctcb->rip,TCP_PROTO);
  }
  pktFree(pkt); 
}

// prepare the SYN+ACK Packet
void prepareSynAck(pktBuf_t *pkt,tcpCb_t *pctcb)
{
  tcpHdr_t *ptcp;
  UINT8 *pseudohdr;
  UINT16 chksum;
  short hdrLen;  
  short msslen = htons(1460);

  ptcp=(tcpHdr_t *)(pkt-> data - TCP_HDR_LEN);
  // fill the sport and lip
  ptcp->srcport = pctcb->lport;
  //printf("lport is :%x \n",pctcb->lport);
  ptcp->dstport = pctcb->rport;
  //printf("dest port is :%x \n",pctcb->rport);
  ptcp->seqno= htonl(pctcb->isn);
  ptcp->ackno= htonl(pctcb->nrsn);
  ptcp->hdrlen = 0x60; //tcp hdr is 20 bytes + mss 4 bytes
  ptcp->ctrlflgs= 0x12; // flags are SYN+ACK
  pctcb ->lwin = INTIAL_WND_SIZE;
  ptcp->wndsize=htons(pctcb -> lwin);
  ptcp->chksum=0;
  ptcp->urgptr=0;

  pkt -> data[0] = 2;  // type
  pkt -> data[1] = 4;  // length
  memcpy(&pkt ->data[2],&msslen,2);  // MSS value*/
  
  pseudohdr=(char *)malloc(12);
  memcpy(&pseudohdr[0],(char *)pctcb->lip,4);
  memcpy(&pseudohdr[4],(char *)pctcb->rip,4);
  pseudohdr[8]=0x0;
  pseudohdr[9]=TCP_PROTO;
  hdrLen=htons(TCP_HDR_LEN+4);
  memcpy(&pseudohdr[10],&hdrLen,2);
  
  pkt->data=(UINT8 *)ptcp;
  chksum=computeChksum(pseudohdr,pkt,hdrLen);
  ptcp->chksum = chksum; //

} 

  
/********* tcpSynAckEvtProc() function implementation ***********/
// this function receives the pkt that consists no data but SYN+ACK
void tcpSynAckEvtProc(pktBuf_t *pkt,tcpCb_t *tcb)
{
  tcpHdr_t *ptcphdr;
  pktBuf_t *pktack;
  tcpCb_t  *port;
  int      opIndx=0,ii=0;
  tcpOpt_t opt;
  char *opBuf = pkt->data + TCP_HDR_LEN;

  ptcphdr=(tcpHdr_t *)(pkt->data);
  while(1)
  {
    if(opBuf[opIndx] == 0)
    {
      opt.eop = opBuf[opIndx];
      opIndx++;
    }
    else if(opBuf[opIndx] == 1)
    {
      opt.nop = opBuf[opIndx];
      opIndx++;
    }
    else if(opBuf[opIndx] == 2)
    {
      memcpy(opt.mss , &opBuf[opIndx], 4);
      memcpy(&tcb -> mss, &opt.mss[2],2);
      tcb->mss = htons(tcb->mss);
      opIndx += 4;
      break;
    }
    else if(*opBuf == 3)
    {
      //memcpy(ptcphdr ->opt.wsf,opBuf[0],3);
    }
    else if(*opBuf == 8)
    {
      //memcpy(ptcphdr -> opt.ts,
    } 
  }
  
  switch(tcb->state)
  { 
    case SYN_SENT:
      tcb->state = ESTABLISHED;
      tcb->rwin = ntohs(ptcphdr->wndsize);
      tcb->nrsn = htonl(ptcphdr->seqno) + 1; 
    // printf("tcb -> lasn before update in syn ack :%d\n",tcb -> lasn);
    
      // prepare ACK Packet  
      pktack=pktAlloc();
      if(pktack == NULL)
        return ;

      tcb ->lwin = INTIAL_WND_SIZE;
      tcb -> alsn = tcb -> isn + tcb ->rwin;  //ccc      
      tcb -> lasn = htonl(ptcphdr -> ackno) - 1;
    //  printf("tcb -> lasn after update in syn ack :%d\n",tcb -> lasn);

     //intially set the winzero flag
      tcb -> winzeroflg =1;

      prepareAck(pktack,tcb);
      pktack->len = TCP_HDR_LEN;
    /*  printf("ACK PKT: \n");
      printBuf(pktack -> buf + ETH_HDR_LEN + IP_HDR_LEN, pktack -> len);*/
      
      // send the Ack Pkt
      ipSendPkt(pktack,tcb->rip,TCP_PROTO);
   
      // add the ACK Packet to the Tcp control block
      tcb->sendpkt = pktack;
     
      // search the port in non-listen Q
      port=tcpNLSearchCb(tcb->lport);
      if(port == NULL)
      {
        pktFree(pkt);
        printf("it is not a client socket \n");
        return ;
      }
      else
      {
        tcb->errno=0;
        semGive(tcb->rxsem);
      }
      break;    
    
    // it is the case when ACK send by the Client is lost
    case ESTABLISHED:
      // retransmit the ACK Packet
      ipSendPkt(tcb->sendpkt,tcb->rip,TCP_PROTO);
      break;
  }
  pktFree(pkt);
}

// prepare ACK PKT
void prepareAck(pktBuf_t *pkt,tcpCb_t *ptcb)
{
  tcpHdr_t *ptcp;
  UINT8 *pseudohdr;
  UINT16 chksum;
  UINT16 pktLen;

  ptcp=(tcpHdr_t *)(pkt->data - TCP_HDR_LEN );

  ptcp->srcport    = ptcb->lport;
  ptcp->dstport    = ptcb->rport;
  ptcp->seqno      = htonl(ptcb->nsn);
  ptcp->ackno      = htonl(ptcb->nrsn);
  ptcp->hdrlen     = 0x50;
  ptcp->ctrlflgs   = 0x10; // only ACK flag is set
  ptcp->wndsize    = htons(ptcb -> lwin);
  ptcp->chksum     = 0; //change after the calculation of checksum
  ptcp->urgptr     = 0;
  
  // create the pseudoheader and calculate the checksum
  pseudohdr=(char *)malloc(12);
  memcpy(&pseudohdr[0],(char *)ptcb->lip,4);
  memcpy(&pseudohdr[4],(char *)ptcb->rip,4);

  pseudohdr[8] = 0x0;
  pseudohdr[9] = TCP_PROTO;

  pktLen = htons(20);  

  memcpy(&pseudohdr[10],&pktLen,2);
  
  pkt->data=(UINT8 *)ptcp;
  chksum = computechecksum(pseudohdr,pkt,htons(20));

  ptcp->chksum = chksum; //

 }


/*********** tcpAckEvtProc() function implementation ***********/
void tcpAckEvtProc(pktBuf_t *pkt,tcpCb_t *tcb)
{
  tcpHdr_t *tcphdr;
  tcpCb_t *chktcb;
  pktBuf_t *resppkt;
  UINT32 dcnt,lasn1,len;
  UINT32 optlen,datalen;

  tcphdr=(tcpHdr_t *)(pkt->data);
  
  switch(tcb->state)
  {
    case SYN_RCVD:
      if(htonl(tcphdr->ackno) == tcb ->nsn)
      {
        tcb->state = ESTABLISHED;
        
        // add this to the LISTEN TCB Listen Q
        tcb->lptr->listenQ[tcb->lptr->lqcnt++]=tcb;
 
        tcb -> rwin =  ntohs(tcphdr -> wndsize);
        tcb -> alsn =  tcb -> isn + tcb -> rwin;
        tcb -> lasn = htonl(tcphdr -> ackno) -1;     
        tcb -> avlsn = tcb -> isn;
        tcb -> mss = 1460;
     
        // check the availability of this port in Listen Q
        chktcb=tcpLSearchCb((tcb->lptr)->lport);
        if(chktcb == NULL)  
        {
          pktFree(pkt);
          return ;
        }
        semGive((tcb->lptr)->rxsem); //
        pktFree(pkt);

      }
      else
      //
    break;

    case ESTABLISHED:
    // check the ACK  ackno
    if(htonl(tcphdr ->ackno) <=  tcb ->nsn)
    {
      //last acknowledged sequence number
      lasn1 = htonl(tcphdr -> ackno) -1;
      dcnt = lasn1 - tcb ->lasn;

      // update the tcb ->tcnt value whenever receiving the ack
      tcb ->lasn = lasn1; 
      tcb -> tcnt -= dcnt;
      //printf("no.of elements in the txbuf :%d \n",tcb -> tcnt);
     
      // update the alsn field according to rwin in received tcphdr
      tcb -> alsn = tcb -> nsn + htons(tcphdr -> wndsize);
      
      // update the ackpendflag according to present conditions
      // if ack is pending set the flag otherwise reset the flag
      if((tcb -> nsn - 1) == tcb -> lasn)
        tcb -> ackpendflg = 0;
      else
        tcb -> ackpendflg = 1;
     
      // if the ACK Pkt contains data call the dataEvtProc()
      // to know this check the Pkt Len
      optlen = ((tcphdr -> hdrlen >> 4) * 4) - TCP_HDR_LEN;
      datalen = pkt -> len - (TCP_TOT_HDR_LEN + optlen);
    //  printf("datalen in AckEvtProc() = %d \n",datalen);
      if(datalen > 0)
      {
        //printf("called dataEvtProc()....\n");
        tcpDataEvtProc(pkt,tcb);
      }
      else
      {
        //printf("DATA_LEN = 0\n");
        pktFree(pkt);
      }
 
    
      // check the received window size if it is 0 send window probes
      if(tcphdr -> wndsize == 0)
      {
        // set the winzeroflag and decrement the tcb -> nsn
        tcb -> winzeroflg = 0;
 
        // prepare and send the window probes
        resppkt = pktAlloc();
        if(resppkt == NULL)
          printf("window probe pkt allocation failed \n");
  
        
        prepareWinAck(resppkt,tcb);
        resppkt -> len = TCP_HDR_LEN; //fill
        printf("window probe send from the AckEvtProc \n");
        ipSendPkt(resppkt, tcb -> rip, TCP_PROTO);

        // start the Timer
        tcb->sendpkt = resppkt;
   
        // start timer 250msec
        tcb->tmout = 250;
        tcb->retrys = 0;
        tcb->timerid = alarmStart(tcb->tmout,(void *)probeTimeOut,tcb);//

      }
      else
      {
        //if data is avilable in txbuf,prepare pkt to send remaing data
        // if no data is available in txbuf,break the case
        if(tcb -> winzeroflg == 0)
          tcb -> winzeroflg = 1;

        if(tcb -> nsn < tcb -> avlsn)  // <= or <  ??
        {
          // prepare data pkt
          resppkt = pktAlloc();
          len = prepareDataPkt(tcb,resppkt);
          resppkt -> len = len + TCP_HDR_LEN;
          ipSendPkt(resppkt, tcb -> rip, TCP_PROTO);
          tcb -> ackpendflg =1;// change
        }
      } 

        semGive(tcb -> txsem); // check this condition once again??
    }

      break;

  case FIN_WAIT1 :
      //printf("\nthe state of the block is Fin wait1\n");
      prepareAndSendAckpkt(tcb, pkt);
      tcb -> state = TIME_WAIT;
      semGive(tcb->rxsem);
      pktFree(pkt);
      break;

    case FIN_WAIT2 :
      //printf("\nthe state of the block is Fin wait2\n");
      prepareAndSendAckpkt(tcb, pkt);
      tcb -> state = TIME_WAIT;
      pktFree(pkt);
      break;

    case TIME_WAIT:
      pktFree(pkt);
      break;

    case CLOSE_WAIT:
      semGive(tcb->rxsem);
      break;	      
    case LAST_ACK :
      tcb -> state = CLOSED;     
      semGive(tcb->rxsem);
      pktFree(pkt);
      break;

  }
}

// prepare the window probes
void prepareWinAck(pktBuf_t *pkt,tcpCb_t *ptcb)
{
  tcpHdr_t *ptcp;
  UINT8 *pseudohdr;
  UINT16 chksum;
  UINT16 pktLen;

  ptcp=(tcpHdr_t *)(pkt->data - TCP_HDR_LEN);

  ptcp->srcport    = ptcb->lport;
  ptcp->dstport    = ptcb->rport;
  ptcp->seqno      = htonl(ptcb->nsn - 1);
  ptcp->ackno      = htonl(ptcb->nrsn);
  ptcp->hdrlen     = 0x50;
  ptcp->ctrlflgs   = 0x10; // only ACK flag is set
  ptcp->wndsize    = htons(ptcb -> lwin);
  ptcp->chksum     = 0; //change after the calculation of checksum
  ptcp->urgptr     = 0;
  
  // create the pseudoheader and calculate the checksum
  pseudohdr=(char *)malloc(12);
  memcpy(&pseudohdr[0],(char *)ptcb->lip,4);
  memcpy(&pseudohdr[4],(char *)ptcb->rip,4);

  pseudohdr[8] = 0x0;
  pseudohdr[9] = TCP_PROTO;

  pktLen = htons(20);  

  memcpy(&pseudohdr[10],&pktLen,2);
  
  pkt->data=(UINT8 *)ptcp;
  chksum = computechecksum(pseudohdr,pkt,htons(20));

  ptcp->chksum = chksum; //

 }

void probeTimeOut(tcpCb_t *tcb)
{
  switch(tcb->state)    
  {
    case ESTABLISHED:
      tcb->retrys++;
      tcb->tmout=2*tcb->tmout;
      tcb->timerid=alarmStart(tcb->tmout,(void *)probeTimeOut,tcb);
    break;     
   }
}


/******** function to display the Listen control block **************/
int lisndispCtlBlk()
{
  int ii;
  tcpCb_t *tcpCbListp;
  tcpCbListp = pListenQ;

  if(tcpCbListp == NULL)
  {
     printf("there is no control blocks\n");
  }
  while(tcpCbListp != NULL)
  {
    printf("state = %x\n",tcpCbListp->state);
    printf("local ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",tcpCbListp->lip[ii]);
    printf("\n");
    printf("destination ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",tcpCbListp->rip[ii]);
    printf("\n");
    printf("local port = %d\n",htons(tcpCbListp->lport));
    printf("destination port = %x\n",htons(tcpCbListp->rport));

    tcpCbListp = tcpCbListp->pnxt;
  }

}

/******** function to display the Non-Listen control block **********/
int nonLisndispCtlBlk()
{
  int ii;
  tcpCb_t *tcpCbListp;
  tcpCbListp = pNonListenQ;

  if(tcpCbListp == NULL)
  {
     printf("there is no control blocks\n");
  }
  while(tcpCbListp != NULL)
  {
    printf("state = %x\n",tcpCbListp->state);
    printf("local ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",tcpCbListp->lip[ii]);
    printf("\n");
    printf("destination ip = ");
    for(ii = 0; ii< 4; ii++)
    printf(" %d",tcpCbListp->rip[ii]);
    printf("\n");
    printf("local port = %d\n",htons(tcpCbListp->lport));
    printf("destination port = %x\n",htons(tcpCbListp->rport));

    tcpCbListp = tcpCbListp->pnxt;
  }
}

/********** tcpWrite() function implementation ****************/
INT32 tcpWrite(tcpCb_t *tcb,UINT8 *buff, INT32 len)
{
  UINT32 datalen = len,len1 = 0,val=0;
  pktBuf_t  *datapkt;
 
  
  while(datalen > 0)
  {
    // copy the user data to the txbuf
    val += copybuf(tcb,buff+val,&datalen);
    
    // check the ack pending flag and send the data pkt
    if((tcb -> ackpendflg == 0) && (tcb -> winzeroflg != 0))
    {
      datapkt = pktAlloc();
      if(datapkt == NULL)
      {
        printf("data pkt allocation failed \n");
        return ;
      }

      len1 = prepareDataPkt(tcb,datapkt);
      datapkt -> len = len1 + TCP_HDR_LEN;
      ipSendPkt(datapkt, tcb -> rip, TCP_PROTO);  
      tcb -> ackpendflg =1;
    }
    while((datalen != 0) && (tcb ->tcnt == BUF_SIZE))
    {  
      semTake(tcb ->txsem,WAIT_FOREVER);
    }
    //else
      //break;
  }
  return len;
}
   
// copy the user data to the txbuf
INT32 copybuf(tcpCb_t *tcb,UINT8 *buff,INT32 *datalen)
{
  INT32 indx = 0;
  UINT32 lasnindx,avlsnindx;
  UINT32 space, val,aspace,totspace;

  lasnindx = (tcb ->lasn - (tcb ->isn +1)) % BUF_SIZE ; //??
  //printf("lasn= %d  isn = %d\n", tcb ->lasn,tcb ->isn);
  avlsnindx = (tcb ->avlsn -(tcb ->isn + 1)) % BUF_SIZE; 
  if(tcb -> avlsn == tcb -> isn)
     avlsnindx = 0;
  if(tcb -> lasn == tcb -> isn)
     lasnindx = 0;
  //if((tcb -> avlsn > tcb -> isn) && (avlsnindx == 0))
    //avlsnindx = BUF_SIZE;  
 
//  printf("avlsnindx = %d\n",avlsnindx);
  //printf("avlsn = %d\n",tcb->avlsn);
//  printf("lasn = %d\n",tcb->lasn);
  //printf("lasnindx = %d \n",lasnindx);
  space = BUF_SIZE - (tcb->twix ); //
  totspace = BUF_SIZE -(tcb ->avlsn - tcb ->lasn);
  aspace = min(space,totspace);
 // printf("space = %d\n",space);
 // printf("aspace = %d \n",aspace);

  val = min(aspace,*datalen);
 //   printf("In Copybuff() tcb -> twix = %d \n",tcb -> twix);
//copy until all data copied or txbuf filled
  while((*datalen !=0) && (tcb ->tcnt != (BUF_SIZE)))
  {
    memcpy(&tcb ->txbuf[tcb -> twix],&buff[indx],val); ///
   //printf("user buffer is: ");
    //printBuf(&buff[indx],*datalen);
    //printf("\n");
    *datalen -= val;
   // printf("*datalen = %d\n",*datalen);
    tcb -> twix +=val;
    tcb -> tcnt +=val;
//    printf("tcb -> tcnt = %d\n",tcb->tcnt);

    indx += val;
    tcb -> avlsn += val ;
   // printf("avlsn = %d\n",tcb->avlsn);

    if(tcb -> twix >= BUF_SIZE)
      tcb -> twix = 0;

    val = (lasnindx + 1) - tcb -> twix  ;///c
  //  printf("sace available is val =%d \n",val);
    val = min(val,*datalen);
  }
//  printf("tcb -> twix after copied data = %d \n",tcb-> twix);
 // printf("txbuf contents are: ");
//  printBuf(tcb ->txbuf,20);
//  printf("\n ");
   return indx;
   
}

// prepare the data pkt
INT32 prepareDataPkt(tcpCb_t *tcb, pktBuf_t *datapkt)
{
  UINT32 adata,awin,vliddata;  // available data and available window
  UINT32 val,space,val1,len;
  tcpHdr_t *ptcp;
  UINT8 *pseudohdr;
  UINT16 chksum;
  UINT16 hdrLen;
  UINT16 hdrlen;
  INT32 lasnindx,nsnindx;
  UINT32 avlsnindx,alsnindx;

  ptcp = (tcpHdr_t *)(datapkt ->data - TCP_HDR_LEN);
    
    adata = tcb -> avlsn - tcb ->nsn + 1;
    awin = tcb -> alsn -tcb ->nsn;
    vliddata = min(tcb -> mss,adata);
    
   
  val = min(vliddata,awin);
  len = val;
  space = BUF_SIZE - tcb ->trix;
  val1 = min(space,val);
  memcpy(datapkt ->data,&tcb ->txbuf[tcb -> trix],val1);  

  // update the corresponding indices
  tcb -> trix += val1;
  //printf("txbuf trix index is:%d \n",tcb ->trix);  

  if(tcb -> trix >= BUF_SIZE)
     tcb -> trix = 0;
 
  //tcb -> nsn += val1;
  val = val - val1;
 
  if(val > 0)
  {
    memcpy(datapkt->data+val1,&tcb->txbuf[tcb->trix],val);
    
   // tcb -> nsn += val;
    tcb -> trix += val;
  }

// fill the tcp header
  ptcp -> srcport = tcb ->lport;
  ptcp -> dstport = tcb ->rport;
  ptcp -> seqno = htonl(tcb -> nsn);
  ptcp -> ackno = htonl(tcb -> nrsn);   
  ptcp -> hdrlen = 0x50;
  ptcp -> ctrlflgs = 0x18;  // PSH + ACK Flags
  ptcp ->wndsize = htons(INTIAL_WND_SIZE); //??
  ptcp ->chksum =0x0;
  ptcp ->urgptr = 0;
  

  // create pseudoheader and calculate checksum
  pseudohdr = (char *)malloc(12);
  memcpy(&pseudohdr[0],(char *)tcb -> lip,4);
  memcpy(&pseudohdr[4],(char *)tcb -> rip,4);
  pseudohdr[8] = 0x0;
  pseudohdr[9] = TCP_PROTO;
  
  //hdrLen = htons(TCP_HDR_LEN);
  hdrlen = htons(TCP_HDR_LEN +len);
  memcpy(&pseudohdr[10],&hdrlen,2);
  datapkt->data=(UINT8 *)ptcp;
  chksum=computeChksum(pseudohdr,datapkt,hdrlen);
  ptcp -> chksum =chksum;

  tcb -> nsn += len;
  return len;
}



 
/********** tcpDataEvtProc() function implementation ***********/
void tcpDataEvtProc(pktBuf_t *pkt,tcpCb_t *tcb)
{
  tcpHdr_t *ptcp;
  INT32 datalen;
  INT32 optlen;
  INT32 val;
  pktBuf_t *ackpkt;
  INT32 space,lasn1,dcnt;

  ptcp   = (tcpHdr_t *)(pkt -> data);
  optlen = ((ptcp -> hdrlen >> 4) * 4) - TCP_HDR_LEN;

  // check the ACK  ackno
  // updation of flags will be done only in the case of of PUSH+ACK

  if(ptcp -> ctrlflgs == PSH_ACK_PKT || ptcp -> ctrlflgs == FIN_PSH_ACK_PKT)
  {
    if(htonl(ptcp ->ackno) <=  tcb ->nsn)
    {
      //last acknowledged sequence number
      lasn1 = htonl(ptcp -> ackno) -1;
      dcnt = lasn1 - tcb ->lasn;

      // update the tcb ->tcnt value whenever receiving the ack
      tcb ->lasn = lasn1; 
      tcb -> tcnt -= dcnt;
      //printf("no.of elements in the txbuf :%d \n",tcb -> tcnt);
    
      // update the alsn field according to rwin in received tcphdr
      tcb -> alsn = tcb -> nsn + htons(ptcp -> wndsize);
     
      // update the ackpendflag according to present conditions
      // if ack is pending set the flag otherwise reset the flag
      if((tcb -> nsn - 1) == tcb -> lasn)
        tcb -> ackpendflg = 0;
      else
        tcb -> ackpendflg = 1;
    } 
  }
 
  datalen = pkt -> len - (TCP_TOT_HDR_LEN + optlen);
  
  if(htonl(ptcp -> seqno) == tcb -> nrsn)
  {
    copydata(pkt,tcb,datalen,optlen);
    
  }
  else if(htonl(ptcp -> seqno) < tcb ->nrsn)
  {
    val = tcb ->nrsn -htonl(ptcp ->seqno);  // change htonl
    copydata(pkt,tcb,datalen-val,optlen+val);
    
  }
  else
  {
    printf("\n\n IF THE SEQ NO > NRSN (IF ANY PKT LOSS)....\n\n");
    pktFree(pkt);
     return ;
  }
   
  // check the available space in rxbuf
  // if rxbuf is full set the  windowsize to 0 and set the windowflag
  if(tcb -> rcnt >= BUF_SIZE)
  {
    tcb ->lwin = 0;
    tcb -> windflag = 1;
    tcb -> winctlflg =1;
  }

  else
  {
    space = BUF_SIZE - tcb ->rcnt;
    tcb -> lwin = space;
  } 

  pktFree(pkt);

  // prepare the ACK Pkt
  ackpkt = pktAlloc();
  if(ackpkt == NULL)
  {
    printf("Pkt Allocation Failed for Ack in DataEvtProc\n");
    return ;
  } 

  prepareAck(ackpkt,tcb);
  ackpkt->len = TCP_HDR_LEN;
      

  // send Ack Pkt to the IP
  ipSendPkt(ackpkt,tcb -> rip, TCP_PROTO);
 
  // release the rxsem semaphore
  semGive(tcb -> rxsem); 
   return ;
}
  

/*********** tcpRead() function implementation *************/
INT32 tcpRead(tcpCb_t *tcb,UINT8 *buf,INT32 len)
{
  INT32 datalen,len1;
  INT32 val;

  if(tcb -> state != ESTABLISHED && tcb->state != FIN_WAIT2)
  {
    printf("TCB State Error \n");
    return ERROR;
  }
  
  semTake(tcb ->rxsem, WAIT_FOREVER);

  if(tcb->state == CLOSE_WAIT)
  {
    return 0;
  }
 
  datalen = (len > tcb -> rcnt) ? tcb -> rcnt : len;
  len1 = datalen;


  val = BUF_SIZE - (tcb -> rrix);
  val = min(val, datalen);

  // copy the rxbuf data into the user buffer
  if(tcb -> rcnt)
  {
    memcpy(buf, &tcb -> rxbuf[tcb -> rrix], val);
    // change the indicies
    tcb -> rcnt -= val;
    tcb -> rrix += val;
    if(tcb -> rrix == BUF_SIZE)
      tcb -> rrix = 0;
    datalen -= val;

    if(datalen > 0)
    {
      memcpy(buf+val,&tcb -> rxbuf[tcb ->rrix], datalen);
      tcb ->rcnt -= datalen;
      tcb -> rrix += datalen;
    }

    if(tcb -> windflag == 1)
    {
      printf("Application data read & tcb -> rcnt = %d \n",tcb -> rcnt);
    }
  }
  // call the tcpReadEvtProc()
  tcpReadEvtProc(tcb);

  return len1;
}

/**************tcpReadEvtProc() function implementation ************/
void tcpReadEvtProc(tcpCb_t *tcb)
{
  INT32 space;
  pktBuf_t *pkt;
  
  space = BUF_SIZE - tcb ->rcnt;
//  printf("s = %d \n",space); 
 
  if((space >= MIN_SPACE) && (tcb -> windflag == 1))
  {
    tcb ->lwin = space;

    // preare the Ack Pkt
    if(tcb -> winctlflg ==1)
    {
      pkt = pktAlloc(); 
      if(pkt == NULL)
      {
        printf("ack preaparation failed \n");
        return ;
      }

      // tcb ->lwin = space; //???
      prepareAck(pkt,tcb);
      pkt -> len = TCP_HDR_LEN;
    
      tcb -> winctlflg =0;    
      // send the ip pkt
      ipSendPkt(pkt, tcb ->rip, TCP_PROTO);
    }
  }
}

// to copy the pkt buf data to the tcb -> rxbuf
void copydata(pktBuf_t *pkt,tcpCb_t *tcb,INT32 datalen,INT32 optn)
{
  INT32 space;
  INT32 val;
  INT32 indx = 0;  //

  space = BUF_SIZE - tcb -> rwix;
  val = min(space,datalen);
  while((datalen != 0) && (tcb -> rcnt != (BUF_SIZE - 1)))
  {
    memcpy(&tcb->rxbuf[tcb->rwix],(pkt->data+TCP_HDR_LEN+optn+indx), val);
    tcb -> rwix += val;
    tcb -> rcnt += val;
    tcb -> nrsn += val;
    indx += val;  //
    
    if(tcb -> rwix == BUF_SIZE)
      tcb -> rwix = 0;//since it is a circular buffer.
  
    datalen -= val;
    val = tcb -> rrix - tcb -> rwix;
    val = min(val,datalen);
  }
}

// minspace() functon implementation
INT32 min(INT32 val,INT32 datalen)
{
  if(val <= datalen)
    return val;
  else
    return datalen;
}
