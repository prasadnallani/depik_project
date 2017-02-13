/****Concurent server by forking a new process ***/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SRV_TCP_PORT 8000
#define MAX_MSG 100
void errExit(char *str)
{
  puts(str);
  exit(0);
}
int main()
{
  int                sockFd,newSockFd;
  struct sockaddr_in srvAdr,cliAdr;
  int                cliLen,n;
  char               mesg[MAX_MSG];
  int                pid;

  if((sockFd=socket(AF_INET,SOCK_STREAM,0))<0)
    errExit("can't open stream socket\n");

    memset(&srvAdr,0,sizeof(srvAdr));
    srvAdr.sin_family=AF_INET;
    srvAdr.sin_addr.s_addr=htonl(INADDR_ANY);
    srvAdr.sin_port=htons(SRV_TCP_PORT);

    if(bind(sockFd,(struct sockaddr*)&srvAdr,sizeof(srvAdr))<0)
      errExit("can't bind local address\n");
    listen(sockFd,5);

    while(1)
    {
      printf("server waiting for new connection:\n");
      cliLen=sizeof(cliAdr);
      newSockFd=accept(sockFd,(struct sockaddr *) &cliAdr,&cliLen);
      if(newSockFd < 0)
	errExit("accept error\n");
      printf("connected to client :%s\n",inet_ntoa(cliAdr.sin_addr));

      pid=fork();
      if(pid == 0)/***child process***/
      {
	while(1)
	{
	  n=read(newSockFd,mesg,MAX_MSG);
	  if(n<0)
	    errExit("recv error\n");
	  if(n==0)
	    break;
	  mesg[n]=0;
	  if(write(newSockFd,mesg,n) != n)
	    errExit("send error\n");
	  printf("received and sent following message:\n%s\n",mesg);
	}
	exit(0);
      }
      else /*** parent process***/
      {
	close(newSockFd);
      }
    }
  }



    
