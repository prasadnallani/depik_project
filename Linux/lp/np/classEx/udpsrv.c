/********************************************************************
	                       UDP	 
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

/*********Macros*******/
#define SRV_UDP_PORT	8000
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
  int			sockFd;
  struct sockaddr_in	srvAdr, cliAdr;
  int 			cliLen, n;
  char			mesg[MAX_MSG];

  if( ( sockFd = socket(AF_INET, SOCK_DGRAM, 0) ) < 0)
    errExit("Can't open datagram socket\n");
  
  memset(&srvAdr, 0, sizeof(srvAdr));
  srvAdr.sin_family 	= AF_INET;
  srvAdr.sin_addr.s_addr= htonl(INADDR_ANY);
  srvAdr.sin_port 	= htons(SRV_UDP_PORT);

  if( ( bind(sockFd, (struct sockaddr*)&srvAdr, sizeof(srvAdr)) )  < 0)
    errExit("Can't bind local address\n");
  
  printf("server waiting for message\n");
  
  while(1)
  {
    cliLen = sizeof(cliAdr);
    n = recvfrom(sockFd, mesg, MAX_MSG, 0, &cliAdr, &cliLen);
    if(n < 0)
      errExit("recvfrom Error\n");
  
    if( (sendto(sockFd, mesg, n, 0, &cliAdr, cliLen)) != n)
      errExit("sendto Error\n");

    printf("recieved following message from client: %s\n %s\n", inet_ntoa(cliAdr.sin_addr), mesg);
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

