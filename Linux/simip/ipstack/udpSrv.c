
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "pktbuf.h"
#include "nwstk.h"
/******************************************************************************
 * Name :
 * Description:
 *****************************************************************************/
void udpCli();
void udpEcho()
{
  struct sockaddr_in cliAddr, srvAddr;
  int i, n, sockFd;
  int cliLen;
  char msg[80];
  
  sockFd = socket(AF_INET, SOCK_DGRAM, 0);
  printf("sockfd = %d\n",sockFd);
  if(sockFd < 0)
  {
    printf("Can't create socket\n");
    return;
  }
  srvAddr.sin_family = AF_INET;
  srvAddr.sin_addr.s_addr = inet_addr("192.168.0.120" );
  srvAddr.sin_port = htons(8000);

  if( (bind(sockFd,(struct sockaddr *)&srvAddr, sizeof(srvAddr))) < 0 )
  {
    printf("Can't Bind port Number 7\n" ) ;
    return;
  }
  
  printf("UDP ECHO server started\n" ) ;
  while(1)
  {
    cliLen = sizeof(cliAddr);
    n = recvfrom(sockFd, msg, 80, 0, &cliAddr, &cliLen);
    // printf("recv %d bytes\n", n);
    if(n < 0)
      printf("UDP ECHO serv recv error\n");

    msg[strlen(msg)] = 0;
    printf("MSG is : %s\n",msg);
    if (sendto(sockFd,msg,n,0,&cliAddr,cliLen) != n)
      printf("UDP ECHO serv send error\n");
  }
}
/******************************************************************************
 * Name:
 * Descrption:
 ******************************************************************************/
int udpEchoSrv()
{
  int tskid;
  tskid = taskSpawn("udpTask",5,0,0x1000,udpEcho, 0,0,0,0,0,0,0,0,0,0);
}
int udpEchoCli()
{
  int tskid;
  tskid = taskSpawn("cliTask",6,0,0x1000,udpCli, 0,0,0,0,0,0,0,0,0,0);
}

/*******************************************************************************
 * Name:
 * Description:
 ******************************************************************************/
void udpCli()
{
  struct sockaddr_in srvAddr,cliAddr;
  int sockFd;
  int n,port_no;
  char msg[80];
  char srvipadr[20];

  if( (sockFd = socket(AF_INET,SOCK_DGRAM,0) ) < 0)
  {
    printf("Can't create socket\n");
    return;
  }
  printf("sockfd = %d\n",sockFd);
/*  printf("\nEnter Server IP Address:");
  gets(srvipadr,20);
  printf("\nEnter Port Number to connect:\n");
  scanf("%d",&port_no); */
  
  srvAddr.sin_family      = AF_INET;
  srvAddr.sin_addr.s_addr = inet_addr("192.168.0.120" );
  srvAddr.sin_port        = htons(8000);
  
/*  printf("\nEnter Mssg to send to the srv:\n");
  gets(msg,80);*/
   strcpy(msg,"hello\n");

  n = strlen(msg) ;
  if( sendto(sockFd, msg, n, 0, &srvAddr,sizeof(srvAddr)) != n)
  {
    printf("Send Error\n" );
    return;
  }
  printf("client : Waiting for response\n" );
  n = recv(sockFd, msg, 80,0);
 
  
  if( n < 0)
  {
    printf("Receive Error\n");
    return;
  }
  
  printf("Received the following message:\n%s\n",msg);
  socketClose(sockFd);
}
