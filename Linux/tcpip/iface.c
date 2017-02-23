/***********************************************************************
* File: iface.c
* Description:
***********************************************************************/
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "rtldrv.h"
#include "nwstk.h"
#include "nwutil.h"


#define    IFC_UP    1

iface_t  *ifaceTbl[MAX_IFACES];
unsigned char testIp[4] = {192,168,2,100};

void ifaceShow(int argc, char *argv[]);
void ifConfig(int argc, char *argv[]);

/***********************************************************************
* Name:
* Description:
***********************************************************************/
ifaceInit()
{
  //shellRegCmd("iface",ifaceShow, "Show Ifaces");
  //shellRegCmd("setip",ifConfig, "Set IP address");
}

/***********************************************************************
* Name:
* Description:
***********************************************************************/
int ifcRegister(char *name, void *pDev, int (*sendFP)(void *, pktBuf_t *),
                 int (*ioctlFP) (void *, int ,void *),
                 char *macAdrs,int *pIfNum)
{
  int ifNum;
  iface_t *pif;

  /*** Find empty slot in iface table ***/
  for(ifNum=1; ifNum < MAX_IFACES; ifNum++)
  {
    if(!ifaceTbl[ifNum])
      break;
  }
  if(ifNum == MAX_IFACES)
    return ERROR;

  pif = malloc(sizeof(iface_t));
  memcpy(pif->name, name,10);
  pif->unitNum = ifNum; 
  pif->sendFP  = sendFP;
  pif->ioctlFP = ioctlFP;
  pif->pDev    = pDev;
  pif->flags   = IFC_UP;
  memcpy(pif->macAdrs, macAdrs, 6);
  memcpy(pif->ipAdrs, testIp, 4);

  ifaceTbl[ifNum] = pif;
  *pIfNum = ifNum;
  return OK;
}

/***********************************************************************
* Name:
* Description:
***********************************************************************/
void dispIface(iface_t *pif)
{
  int ii;

  printf("iface Name : %s\n",pif->name);
  printf("MAC address: ");
  for(ii=0; ii < 6; ii++)
   printf("%02x ",pif->macAdrs[ii]);
  printf("\nIP address: ");
  for(ii=0; ii < 4; ii++)
  {
    printf("%d",pif->ipAdrs[ii]);
    if(ii<3) putchar('.');
  }
  printf("\nIfNum: %d\n", pif->unitNum);
  printf("Flags: %08x\n", pif->flags);
}

/***********************************************************************
* Name:ifaceShow()
* Description:
***********************************************************************/
void ifaceShow(int argc, char *argv[])
{
  int ii;

  for(ii=1; ii< MAX_IFACES; ii++)
  {
    if(ifaceTbl[ii])
      dispIface(ifaceTbl[ii]);
  }
}

/***********************************************************************
* Name:ifConfig
* Description:
***********************************************************************/
void ifConfig(int argc, char *argv[])
{
  int ifNum;
  UINT8 ipAdrs[4];
  if(argc < 3)
  {
    printf("Parameters missing\n");
    return;
  }
  ifNum = atoi(argv[1]);
  ip2bin(argv[2],ipAdrs);
  if((ifNum < MAX_IFACES) && ifaceTbl[ifNum])
  {
    memcpy(ifaceTbl[ifNum]->ipAdrs,ipAdrs,4);
  }
}

void ifConfInit()
{
  shellRegCmd("ifconfig",(void *)ifConfig,"To set IP address");
}  
