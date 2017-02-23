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
//#define SRV_IP_ADRS	"192.168.0.22"
#define SRV_IP_ADRS	"127.0.0.1"
#define SRV_TCP_PORT	8000	
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
  struct sockaddr_in	srvAdr;
  char			txMsg[MAX_MSG];
  char			rxMsg[MAX_MSG];
  int 			n;

  if( ( sockFd = socket(AF_INET, SOCK_STREAM, 0) ) < 0)
    errExit("Can't open datagram socket\n");
  
  memset(&srvAdr, 0, sizeof(srvAdr));
  srvAdr.sin_family 	= AF_INET;
  srvAdr.sin_addr.s_addr= inet_addr(SRV_IP_ADRS);
  srvAdr.sin_port 	= htons(SRV_TCP_PORT);
  
  if( (connect(sockFd, (struct sockaddr *)&srvAdr, sizeof(srvAdr))) < 0)    errExit("can't Connect To server\n");

  while(1)
  {
    printf("Enter message to send\n");
    fgets(txMsg, MAX_MSG, stdin);
  
    n = strlen(txMsg) + 1;
    printf("client n = %d\n", n);
    if( (send(sockFd, txMsg, n, 0)) != n)
      errExit("Send Eror\n");
    printf("mesg = %s\n", txMsg);
  
    n = recv(sockFd, rxMsg, MAX_MSG, 0);
    if(n < 0)
      errExit("Recv Eror\n");

    printf("Recieved following mesage: \n%s\n", rxMsg);
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

