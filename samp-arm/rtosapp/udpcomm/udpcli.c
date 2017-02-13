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

int udpClient(int argc, char *argv[])
{ 
  int                sockfd;
  struct sockaddr_in ser_addr;
  int                structlen, len;
  unsigned short     portNum;
  char               buffer[] = "Depik systems ltd";
  
  if(argc != 3)
  {
    printf("Invalid number of arguments\n");
    printf("usage  : udpcli <portNumberInDecimal> <ServerIpAdrs>\n");
    printf("Example: udpcli 5678 192.168.0.1\n");
    return 1;
  }

  sockfd = socket(AF_INET, SOCK_DGRAM, UDP_PROTO);

  if(sockfd == ERROR)
  {
    printf(" SOCKET ERROR\n");
    return;
  }

  portNum = atoi(argv[1]);

  ser_addr.sin_family      = AF_INET;
  ser_addr.sin_port        = htons(portNum);
  ser_addr.sin_addr.s_addr = inet_addr(argv[2]);
  structlen = sizeof(ser_addr);
  //while(1)
  //{
    len = sendto(sockfd, buffer, strlen(buffer), 0, &ser_addr,structlen);
  
    len = recvfrom(sockfd, buffer, 100, 0, &ser_addr, &structlen);
    if( (len == ERROR) || (len == 0) )
    {
      printf(" RECEIVE ERROR \n");
      return;
    }
    buffer[len] = '\0';
    printf("\nMESSAGE :%s\n",buffer);
    /*******
    printf("\nCLIENT ADDRESS : %x", cliaddr.sin_addr.s_addr);
    printf("CLIENT PORT :%d\n",cliaddr.sin_port);
    ********/
    
  //}
    close(sockfd);   
}

