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

int inputTask();
int processTask();

SEM_ID inSemId;

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif
  inSemId = semBCreate(0,0);
  taskSpawn("inTask",40,0,0x1000,(FUNPTR)inputTask,0,0,0,0,0,0,0,0,0,0);
  taskSpawn("procTask",40,0,0x1000,(FUNPTR)processTask,0,0,0,0,0,0,0,0,0,0);
}


int inputTask()
{
  unsigned char preDi, cuDi;

  printf("I am input task\n");
  preDi = inl(IOPDATA);
  preDi = (preDi >> 4) & 0xf;

  while(1)
  {
    /** Read the digital inputs **/
    cuDi = inl(IOPDATA);
    cuDi = (cuDi >> 4) & 0xf;

    if(cuDi != preDi)
      semGive(inSemId);
    preDi = cuDi;
    taskDelay(10);
  }
}

int processTask()
{
  printf("I am Process task\n");
  while(1)
  {
    semTake(inSemId,WAIT_FOREVER);
    printf("I process task processing the event ;-)\n");
  }
}


