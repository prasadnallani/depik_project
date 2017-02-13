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

int helloCmdFun(int argc, char *argv[])
{
  int num1, num2;

  if(argc != 3)
  {
    printf("Please enter two numbers along with command\n");
    printf("Usage: %s <Number1> <Number2>\n",argv[0]);
    return 1;
  }
  num1 = atoi(argv[1]);
  num2 = atoi(argv[2]);
  printf("You entered first number as %d and second as %d\n",num1,num2);
  return 0;
}

int mycmd1(int argc, char *argv[])
{
  int i;

  printf("You entered %d number command arguments\n",argc-1);
  if(argc > 1)
  {
    printf("These arguments are:\n");
    for(i=1;i<argc;i++)
      printf("Argument %d = %s\n",i,argv[i]);
  }
}

int mycmd2(int argc, char *argv[])
{
  int i;

  printf("You entered %d number command arguments\n",argc-1);
  if(argc > 1)
  {
    printf("These arguments are:\n");
    for(i=1;i<argc;i++)
      printf("Argument %d = %s\n",i,argv[i]);
  }
}


void applicationStart()
{
  int gid;

#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

  /** Register a new command with name hello in defualt group **/
  shellRegCmd("hello", helloCmdFun, "Sample command");

  /** Create new group **/
  gid = shellRegGrp("mygrp", "My sample group to add my commands");

  /** Add commands to this new group **/
  shellRegGrpCmd("mycmd1", mycmd1, "My command One",gid);
  shellRegGrpCmd("mycmd2", mycmd2, "My command Two",gid);
}

