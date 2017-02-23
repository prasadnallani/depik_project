
#include "config.h" 
#include "osdef.h"
#include "osif.h"
#include "rtldrv.h"
#include "nwstk.h"

/******************** Macros and Enumerations ******************/

#define  FREE        0
#define  FALSE       0
#define  TRUE        1 
#define  SUCCESS     0

/* Symbolic offsets to registers. */
#define  MAC0          0     /* Ethernet hardware address. */
#define  MCA           8     /* Multicast address offset reg */
#define  TXSTATUS0     0x10  /* Transmit status (Four 32bit regis) */
#define  TXADDR0       0x20  /* Tx descriptors (also four 32bit). */
#define  RXBUF         0x30  
#define  RXEARLYCNT    0x34  
#define  RXEARLYSTATUS 0x36 
#define  CHIPCMD       0x37  
#define  RXBUFPTR      0x38  
#define  RXBUFADDR     0x3A 
#define  INTRMASK      0x3C  
#define  INTRSTATUS    0x3E 
#define  TXCONFIG      0x40  
#define  RXCONFIG      0x44 
#define  RXMISSED      0x4C  /* 24 bits valid, write clears. */
#define  CFG9346       0x50  
#define  CONFIG0       0x51  
#define  CONFIG1       0x52 
#define  HLTCLK        0x5B 


enum RxStatusBits 
{
  RxMulticast = 0x8000, 
  RxPhysical  = 0x4000, 
  RxBroadcast = 0x2000,
  RxBadSymbol = 0x0020, 
  RxRunt      = 0x0010, 
  RxTooLong   = 0x0008, 
  RxCRCErr    = 0x0004,
  RxBadAlign  = 0x0002, 
  RxStatusOK  = 0x0001,
};

enum TxStatusBits 
{
  TxHostOwns    = 0x2000, 
  TxUnderrun    = 0x4000, 
  TxStatOK      = 0x8000,
  TxOutOfWindow = 0x20000000, 
  TxAborted     = 0x40000000, 
  TxCarrierLost = 0x80000000
};

#define  VEN_ID        0x10EC
#define  DEV_ID        0x8139

/*** Interrupt MASK or STATUS BITS ***/
#define   ROK              0x01
#define   RER              0x02
#define   TOK              0x04
#define   TER              0x08
#define   RXOVW            0x10

#define ACCEPT_BROADCAST   0x8
#define ACCEPT_MULTICAST   0x4
#define ACCEPT_MY_PHYS     0x2
#define ACCEPT_ALL         0x1
#define CMD_RX_ENB         0x8
#define CMD_TX_ENB         0x4
#define CMD_RESET          0x10

#define RX_FIFO_THRESH  4   /* Rx buffer level before first PCI xfer.  */
#define RX_DMA_BURST    4   /* Maximum PCI burst, '4' is 256 bytes */
#define TX_DMA_BURST    4   /* Calculate as 16<<val. */

#define RX_BUF_LEN_IDX  3      /* 0==8K, 1==16K, 2==32K, 3==64K */
#define RX_BUF_LEN      (8192 << RX_BUF_LEN_IDX)

#define TX_FIFO_THRESH 256  /* In bytes, rounded down to 32 byte units. */
#define TX_FLAG           (TX_FIFO_THRESH<<11) & 0x003f0000


/******************** Structure Type definitions *********************/

typedef struct
{
  pktQ_t           txQ;
  unsigned char    ringBuf[RX_BUF_LEN+16]; 
  char             txpkt[1528];
  unsigned int     rbIndx;
  unsigned char    hwAdrs[6];
  int              cur_desc;
  int              busy;
  int              iobase;
  int              ethirq;
  int              ifNum;
  unsigned int     statistics[ETH_MAX_STATS];
  
}ethDrv_t;

/********* Global Data definitions **********/


/************ Prototypes/Declrations for Local Functions ************/
static void rtlIsr();
static int isrTx();
static int isrRx();
static int rtlStartTx();
void registerEthCliCmds();
int ethPktDrvInit(char *name, ui32 iobase, ui32 irq);
void rtlSend(ethDrv_t *pCb, pktBuf_t *pkt);
int rtlIoctl(ethDrv_t *pCb, int cmd, void *buf);


/***************************************************************************/
/************************ Global Function Definitions **********************/
/***************************************************************************/

int installNetDrivers()
{
  int iobase;
  int irq;

  /*** Initialize packet buffers and create semaphore ***/
  pktBufInit();

  /*** Get IO Base address and IRQ of first ethernet card ***/
  if(pciGetBaseAdrs(VEN_ID, DEV_ID, 0, &iobase, &irq) != SUCCESS)
  {
    printf("Could not get Ethernet IO Base address\n\r");
    return (ETH_CARD_NOT_FOUND_ERR);
  }
  else
  {
    if(iobase & 1)
      iobase--;
    printf("Card found, iobase= 0x%x, irq = 0x%x\n",iobase, irq);
    ethPktDrvInit("eth0", iobase, irq);
  }

  #if 0
  /*** Get IO Base address and IRQ of second ethernet card ***/
  if(pciGetBaseAdrs(VEN_ID, DEV_ID, 1, &iobase, &irq) != SUCCESS)
  {
    printf("Could not get Ethernet IO Base address\n\r");
  }
  else
  {
    if(iobase & 1)
      iobase--;
    printf("Card found, iobase= 0x%x, irq = 0x%x\n",iobase, irq);
    ethPktDrvInit("eth1", iobase, irq);
  }
  #endif

  registerEthCliCmds();
}

/*******************************************************************************
* Name: ethPktDrvInit()
* Description:
*   Initializes the rtl8139 ethernet controller and packet driver
*******************************************************************************/
int ethPktDrvInit(char *name, ui32 iobase, ui32 irq)
{
  int ii;
  ethDrv_t  *pCb;
  
  pCb = malloc(sizeof(ethDrv_t));
  memset(pCb,0,sizeof(ethDrv_t)); 

  pCb->iobase = iobase;
  pCb->ethirq = irq;

  /*** Soft reset the chip. ***/
  outb(pCb->iobase+CHIPCMD, CMD_RESET);

  /* Check that the chip has finished the reset. */
  for (ii = 1000; ii > 0; ii--)
  {
    if ((inb(pCb->iobase+CHIPCMD) & CMD_RESET) == 0)
      break;
  }

  if(ii==0)
  {
    printf("RTL8139 Reset not complete\n\r");
    return (ETH_RESET_NOT_COMPLETE_ERR);
  }

  printf("MAC Address = ");
  for (ii = 0; ii < 6; ii++)
  {
    pCb->hwAdrs[ii] = inb(pCb->iobase+MAC0 + ii); 
    printf("%02x ",pCb->hwAdrs[ii]);
  }
  printf("\n" );

  for (ii = 0; ii < 8; ii++)
  {
    outb(pCb->iobase+MCA+ii, 0xff); 
  }

  ifcRegister(name,pCb,rtlSend,rtlIoctl,pCb->hwAdrs,&pCb->ifNum);

  /*** Must enable Tx/Rx before setting transfer thresholds! ***/
  outb(pCb->iobase+CHIPCMD, CMD_RX_ENB | CMD_TX_ENB);

  /*** Set rx and tx configuration settings ***/
  outl( pCb->iobase+RXCONFIG, (RX_FIFO_THRESH << 13)|(RX_BUF_LEN_IDX << 11) | 
        (RX_DMA_BURST<<8));
  outl(pCb->iobase+TXCONFIG, (TX_DMA_BURST<<8)|0x03000000);


  outb(pCb->iobase+CFG9346,0xC0);
  outb(pCb->iobase+CONFIG1, 0x20);
  outb(pCb->iobase+CFG9346,0x00);

  /*** Set receive buffer  ***/
  outl(pCb->iobase+RXBUF, pCb->ringBuf);

  /*** Install ISR ***/
  if(intConnect(pCb->ethirq, rtlIsr, pCb) != SUCCESS)
  {
    printf("Error in stalling ISR\n\r");
    return(ETH_ISR_INSTALL_ERR);
  }

  /*** Enable interrupt at PIC ***/
  sysIntEnable(pCb->ethirq); 

  /*** Enable interrupt on the controller (rxok, txok) ***/
  outb(pCb->iobase+INTRMASK, ROK | TOK); 

  /*** Enable Reception ***/
  outb( pCb->iobase+RXCONFIG, ACCEPT_BROADCAST | ACCEPT_MULTICAST | 
		                                        ACCEPT_MY_PHYS); 
  //outb( pCb->iobase+RXCONFIG, ACCEPT_BROADCAST | ACCEPT_MY_PHYS | ACCEPT_ALL); 
  //outb( pCb->iobase+RXCONFIG, ACCEPT_ALL); 

  return SUCCESS;
}
/*******************************************************************************
* Name: ethTxPkt 
* Description:
*******************************************************************************/
void rtlSend(ethDrv_t *pCb, pktBuf_t *pkt)
{
  pktEnQ(&pCb->txQ,pkt);
  rtlStartTx(pCb);
}

/*******************************************************************************
* Name: rtlIoctl 
* Description:
*******************************************************************************/
int rtlIoctl(ethDrv_t *pCb, int cmd, void *buf)
{
  int ii;
  unsigned char *ucb  = buf;
  unsigned int  *uib = buf;
  switch(cmd)
  {
    case IOCTL_GET_MAC_ADDRS:
      for(ii=0; ii<6; ii++)
      {
        ucb[ii] = pCb->hwAdrs[ii];
      }
      return (SUCCESS);

    case IOCTL_GET_STATISTICS:
      for(ii=0; ii<ETH_MAX_STATS; ii++)
      {
        uib[ii] = pCb->statistics[ii];
      }
      return (SUCCESS);
 
    case IOCTL_ENABLE_RECEPTION:
      outb( pCb->iobase+RXCONFIG, ACCEPT_BROADCAST | ACCEPT_MY_PHYS); 
      return (SUCCESS);

    case IOCTL_DISABLE_RECEPTION:
      outb( pCb->iobase+RXCONFIG, 0); 
      return (SUCCESS);

    case IOCTL_ENABLE_PROMISC:
      outb( pCb->iobase+RXCONFIG, ACCEPT_ALL); 
      return (SUCCESS);

    case IOCTL_DISABLE_PROMISC:
      outb( pCb->iobase+RXCONFIG, ACCEPT_BROADCAST | ACCEPT_MY_PHYS); 
      return (SUCCESS);

    default:
      return ETH_INV_CMD_ERR;
  }
}

/***************************************************************************/
/************************ Local  Function Definitions **********************/
/***************************************************************************/

/******************************************************************************
* Name: rtlStartTx
* Description:
******************************************************************************/
static int rtlStartTx(ethDrv_t *pCb)
{
  pktBuf_t *pkt;
  unsigned char *tx_buf = (pCb->txpkt + 3); 

  if(pCb->busy)
  {
    return 1; /** BUSY_ERR **/
  }
  /*** Deque the packet from interface queue ***/
  pkt = pktDeQ(&pCb->txQ);
  if(!pkt)
  {
    return 2; /** EMPTY_Q_ERR **/
  }

  pCb->busy = TRUE;

  tx_buf =  (char *) ((unsigned)tx_buf & ~3);
  memcpy(tx_buf, pkt->buf, pkt->len); 

  outl(pCb->iobase+TXADDR0 + (pCb->cur_desc * 4), tx_buf); 

  /* Note: the chip doesn't have auto-pad! */
  outl(pCb->iobase+TXSTATUS0 + (pCb->cur_desc * 4), TX_FLAG | 
                       (pkt->len >= 64 ?  pkt->len : 64));
  pktFree(pkt);
  return SUCCESS;
}

/*******************************************************************************
* Name: rtlIsr
* Description:
*******************************************************************************/
static void rtlIsr(ethDrv_t *pCb)
{
  unsigned short intStat;

  pCb->statistics[ETH_ISR_CNT]++;
  /** Read interrupt status register and acknowledge them **/
  intStat = inw(pCb->iobase+INTRSTATUS);
  outw(pCb->iobase+INTRSTATUS, intStat);

  if(intStat & ROK)
    isrRx(pCb);
  if(intStat & TOK)
    isrTx(pCb);
}

/*******************************************************************************
* Name: isrTx 
* Description:
*******************************************************************************/
static int isrTx(ethDrv_t *pCb)
{
  unsigned txStat;

  txStat = inl(pCb->iobase+TXSTATUS0 + pCb->cur_desc * 4);
  if (txStat & TxStatOK) 
    pCb->statistics[ETH_TXOK_CNT]++;
  else
    pCb->statistics[ETH_TXERR_CNT]++;
  pCb->cur_desc = (pCb->cur_desc + 1) & 3;
  pCb->busy = FALSE;
  rtlStartTx(pCb);
}

/*******************************************************************************
* Name: isrRx 
* Description:
*******************************************************************************/
static int isrRx(ethDrv_t *pCb)
{
  char      *buf;
  pktBuf_t  *pkt;
  int       ring_offset = pCb->rbIndx % RX_BUF_LEN;
  unsigned  rx_status   = *(unsigned*)(pCb->ringBuf + ring_offset);
  int       rx_size     = rx_status >> 16;

  if (rx_status & RxTooLong) 
  {
    pCb->statistics[ETH_TOOLONG_CNT]++;
    return 1;
  }
  else if (rx_status & (RxBadSymbol|RxRunt|RxTooLong|RxCRCErr|RxBadAlign)) 
  {
    pCb->statistics[ETH_BADPKT_CNT]++;
    return 2;
  }

  pkt = pktAlloc();
  if(pkt)
  {
    buf = pkt->buf;
    /** Packet is received properly copy it to the buffer passed **/
    if (ring_offset + rx_size + 4 > RX_BUF_LEN) 
    {
      int semi_count = RX_BUF_LEN - ring_offset - 4;
      memcpy(buf, &pCb->ringBuf[ring_offset + 4], semi_count);
      memcpy(buf+semi_count,pCb->ringBuf, rx_size - semi_count);
    }
    else 
    {
      memcpy(buf, &pCb->ringBuf[ring_offset + 4], rx_size);
    }
    pkt->len   = rx_size;
    pkt->ifNum = pCb->ifNum;
    /** Enque the mbuf to IP task queue **/
    netEnQ(pkt);
  }

  /*** move the ring buffer index to the next packet **/
  pCb->rbIndx = (pCb->rbIndx + rx_size + 4 + 3) & ~3;

  /** Tell the controller that, we read the packet **/
  outw(pCb->iobase+RXBUFPTR, pCb->rbIndx - 16);

  pCb->statistics[ETH_RXOK_CNT]++;
  return SUCCESS;
}

/******************************* CLI Commands ******************************/

char * statStrs[] = { 
                      "ETH_ISR_CNT", 
                      "ETH_RXOK_CNT",   
                      "ETH_TXOK_CNT",  
                      "ETH_TOOLONG_CNT",       
                      "ETH_BADPKT_CNT",       
                      "ETH_TXERR_CNT"
                    };       

/*******************************************************************************
* Name:
* Descritpion:
*******************************************************************************/
int ethIoctl(int argc , char *argv[])
{
  int ifNum;
  int ioctl;

  if(argc == 3)
  {
    ifNum = atoi(argv[1]);
    ioctl = atoi(argv[2]);
    if((ifNum < MAX_IFACES) && ifaceTbl[ifNum])
      rtlIoctl(ifaceTbl[ifNum]->pDev,ioctl , NULL );
    else
      printf("Invalid Iface number\n");
  }
  else
    printf("Usage: ethioctl <ifNum> <ioctlNum>\n");
}

/*******************************************************************************
* Name:
* Descritpion:
*******************************************************************************/
int printEthCnts(int argc , char *argv[])
{
  int ifNum;
  unsigned int statbuf[ETH_MAX_STATS] ;
  int ii ;
 
  if(argc == 2)
  {
    ifNum = atoi(argv[1]);
    if((ifNum < MAX_IFACES) && ifaceTbl[ifNum])
    {
      rtlIoctl(ifaceTbl[ifNum]->pDev,IOCTL_GET_STATISTICS, statbuf );
    }
    else
    {
      printf("Invalid Iface number\n");
      return ERROR;
    }
  }
  else
  {
    printf("Invalid arguments\n");
    return ERROR;
  }

  for(ii = 0 ; ii < ETH_MAX_STATS ; ii ++)
  {
     printf("%25s:%d\n", statStrs[ii], statbuf[ii]);
  }
}    

/*******************************************************************************
* Name: 
* Description:
*******************************************************************************/
void registerEthCliCmds()
{
  //shellRegCmd("ethStat",printEthCnts, "Prints ethernet  status   counters");
  //shellRegCmd("ethioctl", ethIoctl, "Ioctl operations on eth driver");
}
