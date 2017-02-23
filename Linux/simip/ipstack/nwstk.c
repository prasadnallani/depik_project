#include"config.h"
#include"osdef.h"
#include"osif.h"
#include"rtldrv.h"
#include"nwstk.h"

static  pktQ_t  rxQ;
static  SEM_ID  semid;

void netEnQ(pktBuf_t *pkt)
{
  pktEnQ(&rxQ,pkt);
  semGive(semid); 
}

void netTask()
{
  pktBuf_t *pkt;

  while(1)
  {
    semTake(semid,WAIT_FOREVER);

    while((pkt = pktDeQ(&rxQ)) != NULL)
    {
     /** if(pkt->buf[0]==0x33)
      {
        printf("xpkt len: %d\n",pkt->len);
        printf("rxpkt iface: %d\n",pkt->ifNum);
        printBuf(pkt->buf, pkt->len);
        pktFree(pkt);
	continue;
      }**/

      switch( htons(*(UINT16*)&pkt->buf[12]))
      {
        case ARP_PKT:
          arpIn(pkt);
          break;
        case IP_PKT:
          ipIn(pkt);
          break;
        default:
          pktFree(pkt);
          break;
      }
    }
  }
}

int simnetInit()
{
  int tskid;

  installNetDrivers();
  semid = semBCreate(0,0);
  tskid = taskSpawn("netTask",40,0,0x1000,netTask, 0,0,0,0,0,0,0,0,0,0);
  icmpInit();
  ifConfInit();
  arpInit();
}
