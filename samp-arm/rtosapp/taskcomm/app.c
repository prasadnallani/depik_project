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
#define		MAX_MSG_LEN		80
#define		MSG_DEFAULT_OPT		0

int msgqTask();
MSG_Q_ID msgqId;

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

  msgqId = msgQCreate(NO_OF_MSGS,MAX_MSG_LEN,MSG_DEFAULT_OPT);
  taskSpawn("msgqTask",40,0,0x1000,(FUNPTR)msgqTask,0,0,0,0,0,0,0,0,0,0);
}


int msgqTask()
{
  unsigned char msg[MAX_MSG_LEN];
  int len;

  printf("I am Process task\n");
  while(1)
  {
    //len = msgQReceive(msgqId,msg,MAX_MSG_LEN,WAIT_FOREVER);
    len = msgQReceive(msgqId,msg,MAX_MSG_LEN, 3000);
    if(len > 0)
      printf("Rx Msg: %s\n",msg);
    else
      printf("Message Queue Timeout\n");
  }
}

int sendmsg(char *str)
{
  msgQSend(msgqId, str, strlen(str)+1,0,WAIT_FOREVER);
}

