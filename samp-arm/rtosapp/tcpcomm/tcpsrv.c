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

char tcpBuf[200];

/*******************************************************************************
* Name:
* Description: 
*******************************************************************************/
int tcpServer(int port)
{
  int ii, fd,temp, n,newsockfd;
  unsigned char      ipaddr[4];
  unsigned short     portNum;
  struct sockaddr_in tcpaddr, tcpcliaddr;

  fd = socket(AF_INET,SOCK_STREAM,TCP_PROTO);
  printf("SOCK FD :%d\n",fd);

  if( fd == 0 )
  {
     printf(" Socket Function Call Failed\n");
     return 0;
  }

  portNum = (unsigned short)port;

  tcpaddr.sin_family      = AF_INET; 
  tcpaddr.sin_port        = htons(portNum);
  tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  
  if( (temp=bind(fd,(struct sockaddr_in *)&tcpaddr,sizeof(tcpaddr))) == ERROR )
  {
    printf("BIND FAILED  %d\n",temp);
    return 0;
  }
  listen(fd, 5);

  while(1)
  {
    printf("waiting for client connection \n"); 
    newsockfd = accept(fd,(struct sockaddr_in *)&tcpcliaddr,sizeof(tcpaddr));
    printf("New sock fd = %d\n",newsockfd);

    /**************************************************************
    printf("new sock fd = %d\n",newsockfd);
    memcpy(ipaddr, &tcpcliaddr.sin_addr.s_addr, 4);
    printf("\nIp addr :  ");
    for(ii = 0; ii< 4; ii++)
    {
      printf("%d",ipaddr[ii]);
      if(ii < 3)
        printf(".");
    }
    portNum = tcpcliaddr.sin_port;
    printf("\nPort num = %d\n",htons(portNum));
    ****************************************************************/

    while(1)
    { 
      if((n = read(newsockfd, tcpBuf, sizeof(tcpBuf))) == 0)
      {
        printf("Client closed the socket\n");
        close(newsockfd);
        break;
      }
      else
      {
        tcpBuf[n] = 0;
        printf("rx msg : %s\n",tcpBuf);
      }
      if((n = send(newsockfd, tcpBuf, n,0)) == 0)
      {
         printf("send error\n");
         close(newsockfd);
         break;
      }
    } 
  }
}

testtcpsrv()
{
  taskSpawn("tcpSrvTsk",10,0,0x4000,(FUNPTR)tcpServer,8888,0, 0,0,0,0,0,0,0,0);
}

