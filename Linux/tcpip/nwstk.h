#ifndef   _NWSTK_H_
#define   _NWSTK_H_ 

#include"pktbuf.h"

typedef  char            INT8;
typedef  short           INT16;
typedef  int             INT32;

typedef  unsigned char    UINT8;
typedef  unsigned short   UINT16;
typedef  unsigned int     UINT32;

#define  IP_ADRS_LEN                4
#define  HW_ADRS_LEN                6
#define  ETH_HDR_LEN                14 
#define  IP_HDR_LEN                 20 

#define  IP_PKT                     0x800 
#define  ARP_PKT                    0x806 

#define  PROTO_ICMP                 1 
#define  PROTO_TCP                  6 
#define  PROTO_UDP                  17 

typedef struct 
{
  unsigned char  dstHwa[6];
  unsigned char  srcHwa[6];
  unsigned short type;  //this field tells the type of the data received                         i.e. ARP request or IP packet
}ethHdr_t;

typedef struct 
{
  unsigned short hwType; 
  unsigned short protoType;
  unsigned char  hwaLen;
  unsigned char  protoLen;
  unsigned short operation;//this field tell the operation to be                                    performed on the packet
  unsigned char  senderHwa[6];
  unsigned char  senderPra[4];
  unsigned char  targetHwa[6];
  unsigned char  targetPra[4];

}arpPkt_t;

typedef struct
{
  UINT8   verlen;
  UINT8   tos;
  UINT16  pktLen;
  UINT16  pktId;
  UINT16  flagFrag;
  UINT8   ttl;
  UINT8   proto;
  UINT16  cksum;
  UINT8   srcAdrs[4];
  UINT8   dstAdrs[4];
} ipHdr_t;   

typedef struct 
{
  INT8    name[16];
  UINT8   macAdrs[6];
  UINT8   ipAdrs[4];
  void    *pDev;
  INT32   (*sendFP)(void *, pktBuf_t *);
  INT32   (*ioctlFP)(void *, int cmd, void *);
  UINT32  flags;
  UINT32  unitNum;

}iface_t; //this structure is useful for storing the information of       sender i.e. ipaddr,name of the host etc.

#define MAX_IFACES   8

extern iface_t *ifaceTbl[];

typedef struct 
{
  UINT16  sport;
  UINT16  dport;
  UINT16  len;
  UINT16  cksum;
}udpHdr_t; //this sturcture is UDP header.

typedef struct 
{
  UINT16 status;  //this field tell the status of the socket i.e.USED or                                                                  FREE
  UINT16 sockType; //this field tells the type i.e.SOCK_DGRAM or                                                           SOCK_STREAM
  void   *pSockCb; //this field is pointer to the socket control block
}sock_t; //this structure is socket


struct in_addr
{
  unsigned int s_addr;
};

struct sockaddr_in
{
  short  sin_family;           //this field tells the family i.e.AF_INET                                                          or PF_INET
  UINT16 sin_port;             //this filed is the port number

  struct in_addr sin_addr;     //this field is ip address

  char   sin_zero[8];
}; 

typedef struct udpCb_s
{

  UINT16          state;   //this filed is state of socket i.e. BINDED 
                                   //or CONNECTED
  UINT8           lip[4];  //local ip
  UINT8           rip[4];  //remote ip
  UINT16          lport;   //local port
  UINT16          rport;   //remote port
  UINT16          pktCnt;  //packet count
  pktQ_t         *pCbpktQ; //pointer to packet Queue
  SEM_ID          semID;   //semaphore id
  struct udpCb_s *pNext;   //this is pointer to next control block in                              linked list
 
}udpCb_t;

#define SUCCESS     0
#define BIND_BIT    0x0e
#define CONNECT_BIT 0x0f
#define HDR_LEN     42
#define UDP_PROTO   17
#define AF_INET     0x01
#define SOCK_DGRAM  0x03
#define SOCK_STREAM 0x04
#define MAX_SOCKETS 30
#define FREE 0
#define USED 1


#endif
