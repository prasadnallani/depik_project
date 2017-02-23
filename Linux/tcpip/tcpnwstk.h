#ifndef __TCP_NWSTK_H_
#define __TCP_NWSTK_H_

#include"timer.h"
#define   MAX_LQ_SIZE        12


#define   IP_ADD_LEN         4
#define   ETH_ADD_LEN        6
#define   IP_HDR_LEN         20
#define   ETH_HDR_LEN        14
#define   TCP_HDR_LEN        20
#define   TCP_TOT_HDR_LEN    54   
#define   PSUDO_HDR_LEN      12


#define   FIN_PKT            0x01
#define   SYN_PKT            0x02
#define   RST_PKT            0x40
#define   PSH_PKT	     0x08 
#define   ACK_PKT            0x10
#define   URG_PKT            0x20


#define   SYN_ACK_PKT        0x12
#define   PSH_ACK_PKT        0x18 
#define   FIN_PSH_ACK_PKT    0x19
#define   RST_ACK_PKT        0x14
#define   FIN_ACK_PKT        0x11


#define   BIND_BIT           0x0e
#define   CONNECT_BIT        0x0f


#define   ISN                1000
#define   ERROR              -1
#define   INTIAL_WND_SIZE    1024
#define   TCP_PROTO          6
#define   BUF_SIZE           8192
#define   ISN2               5000    //87387
#define   MAX_RETRYS         5       //
#define   MIN_SPACE          10      //   1024 ///
#define   MSS		     1460    //	

typedef struct tcpCb_s
{
  struct tcpCb_s *pnxt;//pionter to next control block.
  struct tcpCb_s *pprv;//pionter to previous control block.

  UINT32 sockIndx;//the socket index.
  
  struct tcpCb_s *listenQ[MAX_LQ_SIZE],*lptr;
  UINT32 lqcnt;//present listen Q count.
  UINT32 lqmax;//Maximum listen Q count.

  UINT32 timerid;//Timer Id.
  UINT32 retrys;//The no of retries made to transmit the same packet.
  UINT32 tmout;//The maximum time to wait to receive response or ACK.
  UINT32 rtriptime;//Round trip time.
  
  SEM_ID mxsem;//mutual exclusion semaphore.
  SEM_ID rxsem;//receive binary semaphore.
  SEM_ID txsem;//transmit binary semaphore.

  UINT16 state;//Present state of the socket.
  UINT16 lport;//Local port of the host.
  UINT8  lip[4];//Local IP address of the host.
  UINT8  rip[4];//Remote IP address of the host.
  UINT16 rport;//Remote port number of the host.

  UINT32 flags;//flags for bind or not.
  INT32  errno;//error no.
  
  UINT32 isn;//Initial sequnece number.
  UINT32 nsn;//Next sequence no.
  UINT32 lasn;//Last acknowledged sequence number.
  UINT32 avlsn;//Upto this seqno data is avilable in tx buffer.
  UINT32 alsn;//Data is allowed to send upto this sequece number.
  UINT32 rwin;//remote window size.

  //UINT32 *txbuf;//transission buffer.
  UINT8 *txbuf;//transission buffer.
  UINT32 twix;//transmission buffer write index. 
  UINT32 trix;//transission buffer read index.
  UINT32 tcnt;//transission count.

  UINT32 nrsn;//Next receiving sequence no.
  UINT32 lwin;//local window size.

  //UINT32 *rxbuf;//receive buffer
  UINT8  *rxbuf;//receive buffer
  UINT32 rwix;//receive buffer write index.
  UINT32 rrix;//receive buffer read index.
  UINT32 rcnt;//receive count.

  pktBuf_t *sendpkt; 
  UINT32 windflag; //
  UINT32 winctlflg; //
  UINT32 ackpendflg; // 
  UINT32 winzeroflg; //

  UINT16 mss;
  
}tcpCb_t;
  
  
  

typedef  struct tcpOpt_s
{
  char eop;
  char nop;
  char mss[4];
  char wsf[3];
  char ts[10];
}tcpOpt_t;


typedef  struct tcpHdr_s
{
  UINT16  srcport;
  UINT16  dstport;
  
  INT32   seqno;
  INT32   ackno;

  UINT8   hdrlen;
  UINT8   ctrlflgs;

  UINT16  wndsize;
  UINT16  chksum;
  UINT16  urgptr;
  
  //tcpOpt_t opt;
}tcpHdr_t;

enum 
{
  CLOSED,
  SYN_SENT,
  SYN_RCVD,
  LISTEN,
  ESTABLISHED,
  FIN_WAIT1,
  CLOSE_WAIT,
  FIN_WAIT2,
  TIME_WAIT,
  LAST_ACK,
};

#endif

