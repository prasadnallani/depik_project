/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "usrcfg.h"
#include "fatfs.h"
#include "board.h"

#define UART1_IRQ         6
#define UART1_BASE_ADRS   0x3ffe000

int serialIoTask();

void applicationStart()
{
  int devno;

#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

  devno = myserDrv();
  myserDevCreate(UART1_IRQ,UART1_BASE_ADRS,"myserdev",devno);

  taskSpawn("serialTask",40,0,0x1000,(FUNPTR)serialIoTask,0,0,0,0,0,0,0,0,0,0);
}


int serialIoTask()
{
  int serfd; 
  char ch;

  serfd = open("myserdev", O_RDWR);
  if(serfd < 0)
  {
    printf("Could not open serial port 2\n");
    return 1;
  }

  while(1)
  {
    read(serfd, &ch, 1);
    if(ch=='#')
      write(serfd,"# char entered\r\n",16);
    else
      write(serfd,&ch, 1);
  }
}



