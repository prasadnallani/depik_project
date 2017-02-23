#include "pktbuf.h"

#define NULL                         0 
#define MAX_PKT_BUFS                 32

static  pktBuf_t pktBufs[MAX_PKT_BUFS];
static  pktQ_t frQ;

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
void pktEnQ(pktQ_t *pPktQ, pktBuf_t *pPkt)
{
  pPkt->pNxt = NULL;

  if(pPktQ->cnt)
  {
    pPktQ->pTl->pNxt = pPkt;
    pPktQ->pTl       = pPkt;
  }
  else
  {
    pPktQ->pHd = pPkt;
    pPktQ->pTl = pPkt;
  }
  pPktQ->cnt++;
}

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
pktBuf_t *pktDeQ(pktQ_t *pPktQ)
{
  pktBuf_t *pPkt;

  if(pPktQ->cnt == 0)
    return NULL;

  pPkt       = pPktQ->pHd;
  pPktQ->pHd = pPktQ->pHd->pNxt;
  pPktQ->cnt--;

  if(pPktQ->cnt == 0)
    pPktQ->pTl  = NULL;

  return pPkt; 
}

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
void freeBufs()
{
  printf("Free buffers: %d\n",frQ.cnt); 
}

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
void pktBufInit()
{
  int ii;

  for(ii=0; ii<MAX_PKT_BUFS; ii++)
  {
    pktEnQ(&frQ, &pktBufs[ii]);
  }
  //shellRegCmd("bufs",freeBufs, "show free bufs");
}

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
pktBuf_t *pktAlloc()
{
  return pktDeQ(&frQ);
}

/******************************************************************************
 * Name:
 * Description:
 *****************************************************************************/
void pktFree(pktBuf_t *pPkt)
{
  pktEnQ(&frQ, pPkt);
}

