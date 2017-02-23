

#include "pktbuf.h"


#define ETH_BASE_ERR                  0x100 
#define ETH_ISR_INSTALL_ERR           ETH_BASE_ERR + 1
#define ETH_CARD_NOT_FOUND_ERR        ETH_BASE_ERR + 2
#define ETH_INV_CMD_ERR               ETH_BASE_ERR + 3
#define ETH_RESET_NOT_COMPLETE_ERR    ETH_BASE_ERR + 4


#define ETH_ISR_CNT               0 
#define ETH_RXOK_CNT              1 
#define ETH_TXOK_CNT              2
#define ETH_TOOLONG_CNT           3 
#define ETH_BADPKT_CNT            4
#define ETH_TXERR_CNT             5
#define ETH_MAX_STATS	          6 


/*** Commands for ethIoctl() function ***/
#define IOCTL_GET_MAC_ADDRS       1
#define IOCTL_GET_STATISTICS      2
#define IOCTL_ENABLE_RECEPTION    3
#define IOCTL_DISABLE_RECEPTION   4 
#define IOCTL_GET_RXQ_PKTS        5


/*** Interface (global) functions ***/

int       ethPktDrvInit();

void      ethTxPkt(pktBuf_t *pkt);

pktBuf_t  *ethRxPkt();

int       ethIoctl(int cmd, void *buf);


