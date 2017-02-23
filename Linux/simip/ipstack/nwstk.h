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
  unsigned short type;
}ethHdr_t;

typedef struct 
{
  unsigned short hwType;
  unsigned short protoType;
  unsigned char  hwaLen;
  unsigned char  protoLen;
  unsigned short operation;
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

}iface_t;

#define MAX_IFACES   8
extern iface_t *ifaceTbl[];

typedef struct 
{
  UINT16  sport;
  UINT16  dport;
  UINT16  len;
  UINT16  cksum;
}udpHdr_t;

typedef struct 
{
  UINT16 status;
  UINT16 sockType;
  void   *pSockCb;
}sock_t;

struct in_addr
{
  unsigned int s_addr;
};

struct sockaddr_in
{
  short  sin_family;
  UINT16 sin_port;
  struct in_addr sin_addr;
  char   sin_zero[8];
};

typedef struct udpCb_s
{
  UINT16          state;
  UINT8           lip[4];
  UINT8           rip[4];
  UINT16          lport;
  UINT16          rport;
  UINT16          pktCnt;
  pktQ_t         *pCbpktQ;
  SEM_ID          semID;
  struct udpCb_s *pNext;
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

