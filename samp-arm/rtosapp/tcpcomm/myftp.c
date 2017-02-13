/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/


#include "in.h"
#include "fatfs.h"

int myftpd( int argc, char *argv[]);
#define MYFTP_SERV_PORT_ID 10002


int tcpFtpServer( int port );
int tcb1;

int myftpd( int argc, char *argv[])
{
  int port = MYFTP_SERV_PORT_ID;

  printf(" This is example program for TCP Server!!\r\n");
  
  //printf("Enter port number : ");
  //scanf("%x", &port);

  tcb1 = taskSpawn("tcp_server", 10, 0, 0x2000, tcpFtpServer, port, 
		                       0, 0, 0, 0, 0, 0, 0, 0, 0 );
}
	


/******************************************************************************
 * Name : tcpServer
 * Description : TCP Server.
 ******************************************************************************/

int tcpFtpServer( int port )
{
  int sfd, temp, newsockfd;
  unsigned short     portNum;
  struct sockaddr_in tcpaddr, tcpcliaddr;

  sfd = socket(AF_INET,SOCK_STREAM, TCP_PROTO);
  
  if( sfd == 0 )
  {
    printf(" Socket Function Call Failed\n");
    return 0;
  }

  portNum = (unsigned short)port;
  tcpaddr.sin_family      = AF_INET;
  tcpaddr.sin_port        = htons(portNum);
  tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if( (temp=bind(sfd,(struct sockaddr_in *)&tcpaddr,sizeof(tcpaddr))) == ERROR )
  {
    printf("BIND FAILED  %d\n",temp);
    return 0;
  }
  
  listen(sfd, 15);

  while(1)
  {
    printf("Server waiting for connection\r\n");
    newsockfd = accept(sfd,(struct sockaddr_in *)&tcpcliaddr, sizeof(tcpaddr));
    printf("new client connected fd = %d\r\n",newsockfd);
    
    processClientRequest(newsockfd);
  }
  close(sfd);
}

static char tcpBuf[256];
/*******************************************************************************
 * Name : processClientRequest
 * Description :
 ******************************************************************************/
int processClientRequest( int sfd )
{
  int n, ii, fd, size = 0;
  char fileName[32], path[64];
  
  if((n = read(sfd, tcpBuf, sizeof(tcpBuf))))
  { 
    /*
     * Client sending a file.
     */ 
    if( tcpBuf[0] == 1 )
    {
      strcpy( fileName, &tcpBuf[1]);
      ii = strlen(fileName);
      current_directory( path );
      strcpy( &path[strlen(path)], fileName);
      fd = open( path, O_RDWR | O_CREAT);
      if( fd < 0 )
      {
	printf("[Worn] Unable to open file %s\r\n", path);
	close(sfd);
	return -1;
      }
       
      /*
       * write data into file, if any came with command.
       */
      if( (n-(ii+2)) > 0 )
      {
        write(fd, &tcpBuf[ ii + 2], n - (ii + 2));
      
        size += (n - (ii + 2));
      }
      printf(" command size %d , file %s, size %d\r\n", n, fileName, size);

      while( (n = read(sfd, tcpBuf, sizeof(tcpBuf))) != 0)
      {
        write(fd, tcpBuf, n);
	size += n;
      }
      
      printf(" recieved file %s, size %d\r\n", fileName, size);
      close(fd);
      close(sfd);
      return 0;
    }
    
    /*
     * Client requesting a file.
     */ 
    if( tcpBuf[0] == 2 )
    {
      strcpy( fileName, &tcpBuf[1]);
      current_directory( path );
      strcpy( &path[strlen(path)], fileName );
      fd = open( path, O_RDONLY );
      if( fd < 0 )
      {
	printf("[Worn] Unable to open file %s\r\n", path);
	close(sfd);
	return -1;
      }

      while( (n = read(fd, tcpBuf, sizeof(tcpBuf))) != 0)
      {
        write(sfd, tcpBuf, n);
	size += n;
      }
      
      printf(" sent file %s, size %d\r\n", fileName, size);
      close(fd);
      close(sfd);
      return 0;
    }
  }
  printf( "Invalid command sent by client!!!\r\n");
  close(sfd);
  return -1;
}
 
