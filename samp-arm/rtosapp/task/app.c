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

int ledTask();
int sleepTask(int tskno, int sleepSeconds);

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

  taskSpawn("sleepTask1",40,0,0x1000,(FUNPTR)sleepTask,1,7,0,0,0,0,0,0,0,0);
  taskSpawn("sleepTask2",30,0,0x1000,(FUNPTR)sleepTask,2,11,0,0,0,0,0,0,0,0);
  taskSpawn("ledTask",40,0,0x1000,(FUNPTR)ledTask,0,0,0,0,0,0,0,0,0,0);
}

int sleepTask(int tskno, int sleepSeconds)
{

  printf("I am sleep task %d\n",tskno);
  while(1)
  {
    printf("I am task %d going to sleep for %d seconds\n",tskno,sleepSeconds);
    taskDelay(sleepSeconds * 100);
  }
}

int ledTask()
{
  unsigned int ledval=0;

  printf("I am LED task\n");
  outl(0x3ff0f, IOPMOD);
  outl(0, IOPCON);

  while(1)
  {
    ledval = ledval << 1;
    ledval = ledval & 0xf;
    if(!ledval)
      ledval=1;
    outl(~ledval,IOPDATA);
    taskDelay(25);
  }
}



