#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "pktbuf.h"
#include "nwstk.h"


void udpCli();
void toggleCase(char *buf,int cnt)
{
   int i;
   for(i=0;i<cnt;i++)
   {
       if(buf[i]>=65&&buf[i]<=90)
          buf[i]+=32;
       else if(buf[i]>=97&&buf[i]<=122)
          buf[i]-=32;
   }
}      
/******************************************************************************
 * Name :
 * Description:
 *****************************************************************************/
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
  srvAddr.sin_addr.s_addr = inet_addr("192.168.0.100");
  srvAddr.sin_port = htons(8000);

  if( (bind(sockFd,(struct sockaddr *)&srvAddr, sizeof(srvAddr))) < 0 )
  {
    printf("Can't Bind port Number 7\n");
    return;
  }
  
  printf("UDP ECHO server started\n");
  while(1)
  {
    cliLen = sizeof(cliAddr);
    n = recvfrom(sockFd, msg, 80, 0, &cliAddr, &cliLen);
    printf("recv %d bytes\n", n);
    
    if(n < 0)
      printf("UDP ECHO serv recv error\n");

    msg[strlen(msg)] = 0;
    toggleCase(msg,strlen(msg));
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
  tskid = taskSpawn("udpSrvTask",40,0,0x1000,udpEcho, 0,0,0,0,0,0,0,0,0,0);
}

/*int udpEchoCli()
{
  int tskid;
  tskid = taskSpawn("udpCliTask",40,0,0x1000,udpCli, 0,0,0,0,0,0,0,0,0,0);
}*/
/***********************************************************************
 * Name:
 * Description:
 **********************************************************************/

void udpCli()
{
  struct sockaddr_in srvAddr,cliAddr;
  int sockFd;
  int n,port_no;
  char msg[80];
  char srvipadr[20];
  int ii=0;
  int len=0;

  if((sockFd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
  {
    printf("Can't create socket\n");
    return;
  }
  
  srvAddr.sin_family      = AF_INET;
  //srvAddr.sin_addr.s_addr = inet_addr("192.168.0.120");//srvipadr);
  srvAddr.sin_addr.s_addr = inet_addr("192.168.0.23");//srvipadr);
  srvAddr.sin_port        = htons(8000);
  while(1)
  {
    printf("\nEnter Mssg to send to the srv:\n");
    memset(msg,0,sizeof(msg));
    gets(msg,80);
    n = strlen(msg) ;
    if(msg[0]=='#')
      return;
    if(sendto(sockFd, msg, n, 0, &srvAddr,sizeof(srvAddr))!= n)
    {
      printf("Send Error\n");
      socketClose(sockFd);
      return;
    }
    printf("Pkt No = %d\n",ii++);
    printf("Waiting for recv\n");
    memset(msg,0,sizeof(msg));
    n= recv(sockFd, msg, 80,0);
  
    if( n < 0)
    {
      printf("Receive Error\n");
      socketClose(sockFd);
      return;
    }
    printf("Received the following message:\n%s\n",msg);
  }
    socketClose(sockFd);
}

