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
      switch( htons(*(UINT16*)&pkt->data[12]))
      {
        case ARP_PKT:
          arpIn(pkt);
          break;
        case IP_PKT:
          pkt->data=pkt->data+sizeof(ethHdr_t);
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
  icmpInit();
  ifConfInit();
  arpInit();
  alarmInit();
  tskid = taskSpawn("netTask",1,0,0x1000,netTask, 0,0,0,0,0,0,0,0,0,0);
}
