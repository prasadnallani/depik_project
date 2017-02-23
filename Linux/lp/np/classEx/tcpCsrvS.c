/********************************************************************
                   TCP concurrent server with select call
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
  int			sockFd, newSockFd, fd;
  struct sockaddr_in	srvAdr, cliAdr;
  int 			cliLen, n;
  char			ii, mesg[MAX_MSG];
  fd_set		readFds, testFds;
  int			stat;

  if( ( sockFd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)
    errExit("Can't open stream socket\n");
  
  memset(&srvAdr, 0, sizeof(srvAdr));
  srvAdr.sin_family 	= AF_INET;
  srvAdr.sin_addr.s_addr= htonl(INADDR_ANY);
  srvAdr.sin_port 	= htons(SRV_TCP_PORT);

  if( ( bind(sockFd, (struct sockaddr*)&srvAdr, sizeof(srvAdr)) )  < 0)
    errExit("Can't bind local address\n");

  listen(sockFd, 5);
  
  FD_ZERO(&readFds);
  FD_SET(sockFd, &readFds);
  printf("server waiting for new connection \n");
  
  while(1)
  {
    testFds = readFds;
    stat = select( FD_SETSIZE, &testFds, (fd_set*)0, (fd_set*)0, (struct timeval *)0 );
    if(stat < 1)
      printf("select error\n");
    
    for(fd = 0; fd < FD_SETSIZE; fd++)
    {
      if(FD_ISSET(fd, &testFds))
      {
        if(fd == sockFd)
	{
	  newSockFd = accept(fd, (struct sockaddr*)0, NULL);
    	  if(newSockFd < 0)
	   errExit("accept Error\n");
	  FD_SET(newSockFd, &readFds);
	  printf("Adding client fd : %d to readFdset\n", newSockFd);
	}
	else
	{
      	  n = recv(newSockFd, mesg, MAX_MSG, 0);
	  if( n < 0)
	   errExit("recv Error\n");
	  else if(n == 0)
	  {
	    close(newSockFd);
	    FD_CLR(fd, &readFds);
	    printf("Removing client fd: %d from readFdSet\n", fd);
	  }
          else
	  {
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

