
#define MAX_PKT_BUF_SIZE             1600 

typedef struct pktBuf_s
{
  struct pktBuf_s   *pNxt;
  int               len;
  int               ifNum;
  unsigned char     buf[MAX_PKT_BUF_SIZE];

}pktBuf_t;


typedef struct pktQ_s
{
  pktBuf_t *pHd;
  pktBuf_t *pTl;
  int      cnt;

}pktQ_t;


void     pktQInit();
pktBuf_t *pktAlloc();
void     pktFree(pktBuf_t *pPkt);

void     pktEnQ(pktQ_t *pPktQ, pktBuf_t *pPkt);
pktBuf_t *pktDeQ(pktQ_t *pPktQ);


