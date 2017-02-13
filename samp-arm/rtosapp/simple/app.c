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


void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif

}

testfile()
{
  int fd;

  fd = open("/ram0/abc.txt", O_RDWR|O_CREAT);
  if(fd < 0)
  {
    printf("Could not open file\n");
    return 1;
  }
  write(fd, "abcdefghijklmnopqrstuvwxyz\n",27);
  write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n",27);
  close(fd);
}


