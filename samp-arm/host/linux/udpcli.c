/**************************** udpcli.c ************************************/ 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "srvapp.h"

// Function prototype
void DatagramClient(char *serverIp);

#define     MAX_MSG       100
    
void errExit(char *str)
{
  puts(str);
  exit(0);
}

int main( int argc, char **argv )
{
  int       nRet;
  
  if (argc != 2)
  {
    fprintf(stderr,"\nSyntax: udpcli <ServerIpAddr>\n");
    return 0;
  }

  DatagramClient(argv[1]);
}

/*******************************************************************************
 * Name : DatagramClient
 * Description :
 ******************************************************************************/
void DatagramClient(char *serverIp)
{
  char                szBuf[256];
  int                 nRet;
  int                 theSocket;
  struct sockaddr_in  saServer;
  int                 nFromLen;

  printf("\nUDP Client sending to server: %s on port: %d\n", 
		                              serverIp, SRV_UDP_PORT);

  //
  // Create a UDP/IP datagram socket
  //

  theSocket = socket(AF_INET,       // Address family
                     SOCK_DGRAM,    // Socket type
                     IPPROTO_UDP);  // Protocol

  if (theSocket < 0)
  {
    printf("socket()");
    return;
  }

  //
  // Fill in the address structure for the server
  //

  saServer.sin_family = AF_INET;
  saServer.sin_addr.s_addr   = inet_addr( serverIp );
  saServer.sin_port = htons(SRV_UDP_PORT);  // Port number from command line

  //
  // Send data to the server
  //

  printf("Enter message to send:\n");
  fgets(szBuf,MAX_MSG,stdin);
 
  
  nRet = sendto(theSocket, szBuf, strlen(szBuf) + 1, 0, 
                (struct sockaddr *)&saServer, sizeof(struct sockaddr));

  if (nRet < 0)
  {
    printf("sendto()");
    close(theSocket);
    return;
  }

  memset(szBuf, 0, sizeof(szBuf));
  
  nFromLen = sizeof(struct sockaddr);
  nRet = recvfrom(theSocket, szBuf, sizeof(szBuf), 0, 
                  (struct sockaddr *)&saServer, &nFromLen);

  if (nRet < 0)
  {
    close(theSocket);
    return;
  }
  
  // Display the data that was received
  printf("Received following message:\n%s\n",szBuf);

  close(theSocket);
  return;
}

