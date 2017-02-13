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

int semTask();

SEM_ID inSemId;

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif
  inSemId = semBCreate(0,0);
  taskSpawn("semTask",40,0,0x1000,(FUNPTR)semTask,0,0,0,0,0,0,0,0,0,0);
}

int semTask()
{
  int stat;

  printf("I am a task waiting on semaphore\n");
  while(1)
  {
    //semTake(inSemId,WAIT_FOREVER);
    stat = semTake(inSemId,3000);
    if(stat == E_OK)
      printf("Semaphore task received a token\n");
    else
      printf("Timeout while waiting for token\n");
  }
}

int sendtoken()
{
  semGive(inSemId);
}

