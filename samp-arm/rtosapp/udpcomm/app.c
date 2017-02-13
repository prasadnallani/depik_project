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

int  audioFd; 

int startUdpServer(int argc, char *argv[]);
int udpClient(int argc, char *argv[]);

void applicationStart()
{
#ifdef NETWORK 
  addRoute("192.168.0.0","255.255.255.0","0.0.0.0",0,1);
  ifConfig(1, "192.168.0.100");
#endif

  shellRegCmd("udpsrv", startUdpServer, "Starts UDP Server on given port");
  shellRegCmd("udpcli", udpClient, "To run UDP client ");
}

