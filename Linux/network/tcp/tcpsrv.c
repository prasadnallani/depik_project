#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SRV_TCP_PORT  8000
#define  MAX_MSG     100

void errExit(char *str)
 {
   puts(str);
   exit(0);
 }
int main()
{
  int  sockFd,newsockFd;
  struct sockaddr_in  srvAdr,cliAdr;
  int cliLen,n;
  char mesg[MAX_MSG];
  if((sockFd =socket(AF_INET,SOCK_STREAM,0)) < 0)
    errExit("can't open stream  socket\n");

  memset(&srvAdr,0,sizeof(srvAdr));
  srvAdr.sin_family  =AF_INET;
  srvAdr.sin_addr.s_addr=htonl(INADDR_ANY);
  srvAdr.sin_port  =htons(SRV_TCP_PORT);

  if(bind(sockFd,(struct sockadr*)&srvAdr,sizeof(srvAdr)) < 0)
    errExit("can't bind local addess\n");

  listen(sockFd,5);
  while(1)
  {
    printf("Servor waiting for new connection:\n");
    cliLen=sizeof(cliAdr);
    newsockFd=accept(sockFd,(struct sockaddr *) &cliAdr,&cliLen);
    if(newsockFd < 0)
      errExit("accept error\n");
    printf("connected to client; %s\n",inet_ntoa(cliAdr.sin_addr));
    while(1)
    {
      n=recv(newsockFd,mesg,MAX_MSG,0);
      if(n < 0)
	errExit("recv error\n");
      if(n==0)
      {
	close(newsockFd);
	break;
      }
      mesg[n]=0;
      if(send(newsockFd,mesg,n,0) != n)
	errExit("send error\n");

      printf("received and sent following message:\n%s\n",mesg);
    }
  }
}

