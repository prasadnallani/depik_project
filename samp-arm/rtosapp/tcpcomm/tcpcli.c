/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/

/******* TCP CLIENT TASK ***************************/
/*********************SOCKET API TESTING*****************************/

#include"in.h"

struct sockaddr_in tcpcliaddr, tcpaddr;
char tcpBuf[] = "DEPIK SYSTEMS";

int tcpClient(int argc, char *portstr, char *ipAdrStr)
{
  int fd,temp, n;
  unsigned short     portNum;

  if(argc != 3)
  {
    printf("Invalid number of arguments\n");
    printf("usage  : tcpcli <portNumberInDecimal> <ServerIpAdrs>\n");
    printf("Example: tcpcli 5678 192.168.0.1\n");
    return 1;
  }

  fd = socket(AF_INET,SOCK_STREAM,TCP_PROTO);
  printf("SOCK FD :%d\n",fd);

  if( fd == 0 )
  {
    printf(" Socket Function Call Failed\n");
    return 0;
  }

  portNum = atoi(portstr);

  tcpaddr.sin_family      = AF_INET; 
  tcpaddr.sin_port        = htons(portNum); 
  tcpaddr.sin_addr.s_addr = inet_addr(ipAdrStr);

  if( connect(fd,(struct sockaddr_in *)&tcpaddr,sizeof(tcpaddr))  == ERROR )
  {
    printf("CONNECT FAILED\n");
    return 0;
  }

  while(1)
  {
    if((n = send(fd, tcpBuf, strlen(tcpBuf), 0)) == 0)
    {
       printf("send error\n");
       socketClose(fd);
       return 0;
    }
    if((n = recv(fd, tcpBuf, sizeof(tcpBuf), 0)) == 0)
    {
      printf("recv ERROR\n");
      socketClose(fd);
      return 0;
    }
    tcpBuf[n] = 0;
    printf("read buf = %s\n",tcpBuf);
  }
  socketClose(fd);
}


