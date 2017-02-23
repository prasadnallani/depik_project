#include"config.h"
#include"osdef.h"
#include"osif.h"
#include"nwstk.h"

#define  SRV_TCP_PORT    8000
#define  MAX_MSG         1000

void errexit(char *str)
{
  puts(str);
  return ;
}


/*********************************************************************
Function Name: tcpEcho()
Description:
*********************************************************************/
void tcpEcho()
{
  int 	  sockfd,newsockfd;
  struct  sockaddr_in srvadr,cliadr;
  int 	  n,clilen,val;
  int 	  msg[MAX_MSG];

  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    errexit("can't open stream socket\n");

  memset(&srvadr,0,sizeof(srvadr));
  srvadr.sin_family       =  AF_INET;
  srvadr.sin_addr.s_addr  =  inet_addr("192.168.0.120");
  srvadr.sin_port         =  htons(SRV_TCP_PORT);

  if(bind(sockfd,(struct sockaddr *)&srvadr,sizeof(srvadr))<0)
    errexit("can't bind local address \n");

  listen(sockfd,5);

  while(1)
  {
    clilen = sizeof(cliadr);
    printf("Server Waiting For New Client...\n");
    newsockfd = accept(sockfd,(struct sockaddr *)&cliadr,&clilen);
    if(newsockfd<0)
      errexit("accept error \n");
    printf("connected to client.\n");

    while(1)
    {
      n=recv(newsockfd,msg,MAX_MSG,0);
      if(n<0)
        errexit("recv error \n");
      if(n==0)
      {
        send(newsockfd,"BABU.DR",7,0);
        socketClose(newsockfd);
        break;
      }
      printf("RX_MSG:%s\n",msg);
      if(send(newsockfd,msg,n,0)!=n)
        errexit("send error \n:");
    } 
  }
}

/********************************************************************
Function Name : tcpEchoSrv()
Description:
********************************************************************/
void tcpEchoSrv()
{
  int tskid;
  tskid = taskSpawn("tcpTask",2,0,0x6000,tcpEcho,0,0,0,0,0,0,0,0,0,0);
}

/*********************************************************************
Function Name : tcpCli()
Description:
********************************************************************/
void tcpCli()
{
  int 	  sockfd;
  struct  sockaddr_in srvadr;
  char    txmsg[MAX_MSG];
  char    rxmsg[MAX_MSG];
  int     n;
  int     retVal;
  short   srvtcpport;
  char    srvIp[20]; 

  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    errexit("can't open stream socket \n");

  memset(&srvadr,0,sizeof(srvadr));
  srvadr.sin_family      =  AF_INET;
//  srvadr.sin_addr.s_addr =  inet_addr("192.168.0.100");
  srvadr.sin_addr.s_addr =  inet_addr("192.168.0.28");
  srvadr.sin_port        =  htons(8000);

  if((retVal = connect(sockfd,(struct sockaddr *)&srvadr,sizeof(srvadr)))<0)
    errexit("can't connect to server \n");
  else 
    printf("retVal of connect sys call = %d\n",retVal);   

  while(1)
  {
    printf("Msg:");
    gets(txmsg,MAX_MSG);

    if(txmsg[0]=='#')
      break;

    n = strlen(txmsg)+1;  
    if(send(sockfd,txmsg,n,0)!=n)
      errexit("send error \n");

    n=recv(sockfd,rxmsg,MAX_MSG,0);

    if(n<0)
      errexit("recv error \n");

    printf("RxMsg:%s\n",rxmsg);
  }
  socketClose(sockfd);
}                       


