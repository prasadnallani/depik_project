
#include"config.h"
#include"osdef.h"
#include"osif.h"
#include"iodrv.h"


#define  SUCCESS      0
#define  MAX_CQ_SIZE      2048 

#define  ULCON        0x0
#define  UCON         0x4
#define  USTAT        0x8
#define  UTXBUF       0xc
#define  URXBUF       0x10
#define  UBRDIV       0x14
#define  BRDCNT       0x18
#define  BRDCLK       0x1c


typedef struct 
{
  unsigned int RdIndex;
  unsigned int WrIndex;
  unsigned int NoOfChar;
  char Buf[MAX_CQ_SIZE];

}cirq_t;


/***  control block structure ****/
typedef struct
{
  DevDesc_t    devHdr;
  unsigned int txSem;
  unsigned int rxSem;
  ui32         baseAddr;
  int          irq;
  cirq_t       Txq;
  cirq_t       Rxq;
}cblock_t;

void sysIntEnable(unsigned long);
static  void myisrRx(cblock_t *Cblk);
static  void myisrTx(cblock_t *Cblk);

static int (*funcPtrNull)();
int myserDrv();
int myserDevCreate(int, unsigned int, char *, int);

static cblock_t *myserOpen(cblock_t *,int);
static cblock_t *myserInit(int ,unsigned int );
static int      myserWrite(cblock_t *, char *, int );
static int      myserRead(cblock_t *,char *,int);
static int      myserClose(cblock_t *);

int  serisrtx;

int myserDrv()
{
  int drvNum;
  funcPtrNull = 0;

  drvNum = iosDrvInstall(funcPtrNull, funcPtrNull,myserOpen, 
                         myserClose, myserRead, myserWrite, funcPtrNull);
  if(drvNum == ERROR)
  {
    return ERROR;
  }
  return drvNum;
}

int myserDevCreate(int irq, unsigned int baseAddr, char *devName, int drvNum)
{
  int status;
  cblock_t *cblk;

  cblk = myserInit(irq, baseAddr);
  
  if(!cblk)
  {
    return ERROR;
  }
  status = iosDevAdd((DevDesc_t *)(&(cblk->devHdr)), devName, drvNum);
  if(status == ERROR)
  { 
    return status;
  }
  return OK;
}

static cblock_t * myserInit(int irq, unsigned int baseaddr)
{
  cblock_t *cblkp;
  
  cblkp = (cblock_t *)malloc(sizeof(cblock_t));

  cblkp->Rxq.RdIndex  = 0;
  cblkp->Rxq.WrIndex  = 0;
  cblkp->Rxq.NoOfChar = 0;
  cblkp->Txq.RdIndex  = 0;
  cblkp->Txq.WrIndex  = 0;
  cblkp->Txq.NoOfChar = 0;

  cblkp->baseAddr = baseaddr;
  cblkp->irq      = irq;
  
  /**** Create a semaphore ****/
  cblkp->rxSem = semBCreate(0,0);
  cblkp->txSem = semBCreate(0,0);
  
  outl(cblkp->baseAddr+ULCON, 0x03);
  outl(cblkp->baseAddr+UCON, 0x09);
  outl(cblkp->baseAddr+UBRDIV, 0x500);

  intConnect(cblkp->irq, myisrTx, (void *)cblkp);
  intConnect(cblkp->irq+1, myisrRx, (void *)cblkp);
  
  return cblkp;
}

static cblock_t *myserOpen(cblock_t *devPtr, int flag)
{
  /*** unmask interrupt for reception ***/ 
  sysIntEnable(devPtr->irq+1);
  sysIntEnable(devPtr->irq);
  return devPtr;
}

static  void myisrRx(cblock_t *Cblk)
{
  if(inl(Cblk->baseAddr+USTAT) & 0x20)
  {
    if(Cblk->Rxq.NoOfChar < MAX_CQ_SIZE)
    {
      Cblk->Rxq.Buf[Cblk->Rxq.WrIndex] = inb(Cblk->baseAddr + URXBUF);
      Cblk->Rxq.WrIndex++;
      Cblk->Rxq.NoOfChar++;
      if(Cblk->Rxq.WrIndex == MAX_CQ_SIZE)
        Cblk->Rxq.WrIndex = 0;
      semGive(Cblk->rxSem);
    }
    else
    {
      inb(Cblk->baseAddr + URXBUF);
    }
  }
}   

static void myisrTx(cblock_t *Cblk)
{
  if(inl(Cblk->baseAddr+USTAT) & 0x40)
  {
    if(Cblk->Txq.NoOfChar > 0)
    {
      outl(Cblk->baseAddr+UTXBUF, Cblk->Txq.Buf[Cblk->Txq.RdIndex++]);
      Cblk->Txq.NoOfChar--;    
      if(Cblk->Txq.RdIndex == MAX_CQ_SIZE)
         Cblk->Txq.RdIndex = 0;
    }
  }
  if(Cblk->Txq.NoOfChar < 10)
      semGive(Cblk->txSem);
}

static int myserRead(cblock_t *Cblk, char *cBufR,int len)
{
  int cLen,i;

  while(Cblk->Rxq.NoOfChar == 0)
  { 
    semTake(Cblk->rxSem,WAIT_FOREVER);
  }
  if(len < Cblk->Rxq.NoOfChar)
    cLen = len;
  else
    cLen = Cblk->Rxq.NoOfChar;

  for(i=0; i<cLen; i++)
  {
    cBufR[i] = Cblk->Rxq.Buf[Cblk->Rxq.RdIndex++];
    Cblk->Rxq.NoOfChar--;
    Cblk->Rxq.RdIndex = Cblk->Rxq.RdIndex % MAX_CQ_SIZE;
  }
  return(cLen);
}

static int myserWrite(cblock_t *Cblk,char *cBufW, int len)
{
  int ii;

  sysIntDisable(Cblk->irq);
  for(ii=0; ii<len; ii++)
  {
    while(Cblk->Txq.NoOfChar == MAX_CQ_SIZE)
    {
      sysIntEnable(Cblk->irq);
      semTake(Cblk->txSem, WAIT_FOREVER);
      sysIntDisable(Cblk->irq);
    }
    Cblk->Txq.Buf[Cblk->Txq.WrIndex++] = cBufW[ii];
    Cblk->Txq.NoOfChar++;
    if(Cblk->Txq.WrIndex == MAX_CQ_SIZE)
      Cblk->Txq.WrIndex = 0;
  }
  myisrTx(Cblk);
  sysIntEnable(Cblk->irq);
  return(len);
}

static int myserClose(cblock_t *Cblk)
{
  sysIntDisable(Cblk->irq+1);
  sysIntDisable(Cblk->irq);
}



