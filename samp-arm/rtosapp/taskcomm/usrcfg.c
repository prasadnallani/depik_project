/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/
/****************************************************************************** 
*This program to create initialise OS and to create mainTsk  
******************************************************************************/

#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "fatfs.h"

#include "usrcfg.h"

int testTask();
int testTask1();

extern unsigned char _edata; 
extern unsigned char _end; 

int semid;
char serDevName[] = "/dev/ttyS0";
char mountPointName[] = "/ram0/";
char conDevName[] = "/dev/console";


#define UART1_DATA	*(volatile unsigned int *)0x808C0000

void usrRoot()
{
  blkdev_t *blkdev; 
  int arg, irq = 4;
  unsigned int baseaddr = 0x3ffd000;
  int serDrvNum;
  int conDrvNum;

  /** Initialize the I/O Subsystem **/
  iosysInit();

  /** Install the serial driver **/
  serDrvNum = serDrv();
  printf("drvnum = %d\n",serDrvNum);
  serDevCreate(irq,baseaddr,serDevName,serDrvNum);

  open("/dev/ttyS0", 0);
  open("/dev/ttyS0", 1);
  open("/dev/ttyS0", 2);
  
#ifdef BANNER
  /** Display the kernel banner **/
  dispBanner();
#endif

  
#ifdef SHELL_TASK
  /** Create shell task **/
  taskSpawn("shellTask",10,0,0x4000,shellTask,0,0,0,0,0,0,0,0,0,0);
#endif


#ifdef FILESYS
  blkdev = createRamdisk(0xc00000, 0x400000);
  fsFormat(blkdev, 0x400000);
  fsInit(blkdev,mountPointName);
#endif

#ifdef NETWORK 
  netInit();
#endif


#ifdef APPLICATION 
  /** Invoke the application starting function **/
  applicationStart();
#endif
}

usrInit()
{
  unsigned char *bssStart = &_edata;
  unsigned char *bssEnd = &_end;

  /**** Initialize the BSS section to zero ***/
  while(bssStart <= bssEnd)
    *bssStart++ = 0;

  initOs(usrRoot,1,0x5000,0);
}

                         
