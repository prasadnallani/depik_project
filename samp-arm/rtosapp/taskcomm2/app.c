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

#define		NO_OF_MSGS		4
#define		MAX_MSG_LEN		8
#define		MSG_DEFAULT_OPT		0

int inputTask();
int processTask();

MSG_Q_ID msgqId;

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

  msgqId = msgQCreate(NO_OF_MSGS,MAX_MSG_LEN,MSG_DEFAULT_OPT);
  taskSpawn("inTask",40,0,0x1000,(FUNPTR)inputTask,0,0,0,0,0,0,0,0,0,0);
  taskSpawn("procTask",40,0,0x1000,(FUNPTR)processTask,0,0,0,0,0,0,0,0,0,0);
}

int inputTask()
{
  unsigned int preDi, cuDi;

  printf("I am input task\n");
  preDi = inl(IOPDATA);
  preDi = (preDi >> 4) & 0xf;

  while(1)
  {
    /** Read the digital inputs **/
    cuDi = inl(IOPDATA);
    cuDi = (cuDi >> 4) & 0xf;

    if(cuDi != preDi)
      msgQSend(msgqId,&cuDi,1,WAIT_FOREVER,MSG_PRI_NORMAL);
    preDi = cuDi;
    taskDelay(10);
  }
}

int processTask()
{
  unsigned char msg[MAX_MSG_LEN];
  int len;

  printf("I am Process task\n");
  while(1)
  {
    len = msgQReceive(msgqId,msg,MAX_MSG_LEN,WAIT_FOREVER);
    printf("I process task processing message %02x\n",msg[0]);
  }
}
