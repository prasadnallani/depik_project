/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/

#include"in.h"

int udpServer(int portNum)
{ 
  int sockfd;
  struct sockaddr_in ser_addr, cliaddr;
  int cli,ii, len;
  int structlen;
  int sendsock,stat;
  char buffer[100];
  
  sockfd = socket(AF_INET, SOCK_DGRAM, UDP_PROTO);

  if(sockfd == ERROR)
  {
    printf(" SOCKET ERROR\n");
    return;
  }

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_port   = htons(portNum);
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  stat = bind(sockfd, (struct sockaddr_in *)&ser_addr, sizeof(ser_addr));
  if(stat == ERROR)
  {
    printf(" BIND ERROR\n");
    return;
  }

  while(1)
  {
    len = recvfrom(sockfd, buffer, 100, 0, &cliaddr, &cli);
    if(len == ERROR)
    {
      printf(" RECEIVE ERROR \n");
      return;
    }
    printf("receive len = %d\n",len);
    buffer[len] = '\0';
    printf("\nMESSAGE :%s\n",buffer);

    structlen = sizeof(cliaddr);
    len = sendto(sockfd, buffer, len, 0, &cliaddr,structlen);

    printf("\nCLIENT ADDRESS : %x", cliaddr.sin_addr.s_addr);
    printf("CLIENT PORT :%d\n",cliaddr.sin_port);
  }   
}

int startUdpServer(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("Usage: startUdpServer <portNum>\n"); 
    return 1;
  }
  taskSpawn("udpsrv",40,0,0x1000,udpServer,atoi(argv[1]),0,0,0,0,0,0,0,0,0);
}
