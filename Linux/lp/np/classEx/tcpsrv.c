/********************************************************************
	                      TCP	 
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

/*********Macros*******/
#define SRV_TCP_PORT    8000 	
#define MAX_MSG		200

/*********Global Variables*******/

/********* Function prototypes *****/
void errExit(char *);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
int main()
{
  int			sockFd, newSockFd;
  struct sockaddr_in	srvAdr, cliAdr;
  int 			cliLen, n;
  char			ii, mesg[MAX_MSG];

  if( ( sockFd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)
    errExit("Can't open stream socket\n");
  
  memset(&srvAdr, 0, sizeof(srvAdr));
  srvAdr.sin_family 	= AF_INET;
  srvAdr.sin_addr.s_addr= htonl(INADDR_ANY);
  srvAdr.sin_port 	= htons(SRV_TCP_PORT);

  if( ( bind(sockFd, (struct sockaddr*)&srvAdr, sizeof(srvAdr)) )  < 0)
    errExit("Can't bind local address\n");

  listen(sockFd, 5);
  
  while(1)
  {
    printf("server waiting for new connection \n");
    newSockFd = accept(sockFd, (struct sockaddr*)&cliAdr, &cliLen);
    if(newSockFd < 0)
      errExit("accept Error\n");
    printf("Comnnected to client : %s\n", inet_ntoa(cliAdr.sin_addr));
    while(1)
    {
      n = recv(newSockFd, mesg, MAX_MSG, 0);
       printf("server n = %d\n", n);
      if( n < 0)
        errExit("recv Error\n");
      if(n == 0)
      {
        close(newSockFd);
        break;
      }
      mesg[n] = 0;

      printf("Recieved mesg : %s\n", mesg);
      for(ii = 0; ii < n; ii++)
         mesg[ii] = toupper(mesg[ii]);

      if( (send(newSockFd, mesg, n, 0)) != n)
        errExit("send Error\n");

      printf("Sent mesg : %s\n", mesg);
    }
  }
}

/**********************************************************************
* Name	      : void errExit(char *)
* Description :
* Inputs      : char * 
* outputs     : none
*********************************************************************/
void errExit(char *str)
{
  puts(str);
  exit(1);
}

