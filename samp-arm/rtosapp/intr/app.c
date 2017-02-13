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

int isrfun(int arg);
int semTask();

SEM_ID inSemId;

void applicationStart()
{
  unsigned int existVal; 

#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif
  inSemId = semBCreate(0,0);
  taskSpawn("semTask",40,0,0x1000,(FUNPTR)semTask,0,0,0,0,0,0,0,0,0,0);

  /** Enable interrupt from parallel port **/
  outb(0x37a,0x10);

  outl(50000000,TDATA1);
  existVal = inl(TMOD);
  outl(existVal | 8, TMOD);

  /*** Install ISR ***/
  if(intConnect(11, isrfun, 0) != 0)
  {
    printf("Error in stalling ISR\n\r");
  }

  /*** Enable interrupt for timer 1 ***/
  sysIntEnable(11); 
}


int semTask()
{
  int stat;

  printf("I am a task waiting on semaphore\n");
  while(1)
  {
    semTake(inSemId,WAIT_FOREVER);
    printf("Got token from ISR\n");
  }
}

int isrfun(int arg)
{
  semGive(inSemId);
}

