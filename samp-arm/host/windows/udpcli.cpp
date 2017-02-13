
/**************************** udpcli.c ************************************/ 


#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include "srvapp.h"

// Function prototype
void DatagramClient(char *serverIp);

// Helper macro for displaying errors
#define PRINTERROR(s)  \
    fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())


#define     MAX_MSG       100
    
void errExit(char *str)
{
  puts(str);
  exit(0);
}

int main( int argc, char **argv )
{
  WORD      wVersionRequested = MAKEWORD(1,1);
  WSADATA   wsaData;
  int       nRet;
  
  //
  // Check for the host and port arguments
  //
  if (argc != 2)
  {
    fprintf(stderr,"\nSyntax: udpcli <ServerIpAddr>\n");
    return 0;
  }

  //
  // Initialize WinSock and check the version
  //
  nRet = WSAStartup(wVersionRequested, &wsaData);
  if (wsaData.wVersion != wVersionRequested)
  {  
    fprintf(stderr,"\n Wrong version\n");
    return 0; 
  }

  //
  // Go do all the stuff a datagram client does
  //
  DatagramClient(argv[1]);
  
  //
  // Release WinSock
  //
  WSACleanup();
}

/*******************************************************************************
 * Name : DatagramClient
 * Description :
 ******************************************************************************/
void DatagramClient(char *serverIp)
{
  char         szBuf[256];
  int          nRet;
  SOCKET       theSocket;
  SOCKADDR_IN  saServer;
  int          nFromLen;

  printf("\nUDP Client sending to server: %s on port: %d\n", 
		                              serverIp, SRV_UDP_PORT);

  //
  // Create a UDP/IP datagram socket
  //

  theSocket = socket(AF_INET,       // Address family
                     SOCK_DGRAM,    // Socket type
                     IPPROTO_UDP);  // Protocol

  if (theSocket == INVALID_SOCKET)
  {
    PRINTERROR("socket()");
    return;
  }

  //
  // Fill in the address structure for the server
  //

  saServer.sin_family = AF_INET;
  saServer.sin_addr.S_un.S_addr   = inet_addr( serverIp );
                    // ^ Server's address
  saServer.sin_port = htons(SRV_UDP_PORT);  // Port number from command line

  //
  // Send data to the server
  //

  printf("Enter message to send:\n");
  fgets(szBuf,MAX_MSG,stdin);
 
  
  nRet = sendto(theSocket,                    // Socket
                szBuf,                        // Data buffer
                strlen(szBuf) + 1,                // Length of data
                0,                            // Flags
                (LPSOCKADDR)&saServer,        // Server address
                sizeof(struct sockaddr));     // Length of address

  if (nRet == SOCKET_ERROR)
  {
    PRINTERROR("sendto()");
    closesocket(theSocket);
    return;
  }

  //
  // Wait for the reply
  //
  memset(szBuf, 0, sizeof(szBuf));

  
  nFromLen = sizeof(struct sockaddr);
  recvfrom(theSocket,            // Socket
           szBuf,                // Receive buffer
           sizeof(szBuf),        // Length of receive buffer
           0,                    // Flags
           (LPSOCKADDR)&saServer,// Buffer to receive sender's address
           &nFromLen);           // Length of address buffer

  if (nRet == SOCKET_ERROR)
  {
    PRINTERROR("recvfrom()");
    closesocket(theSocket);
    return;
  }
  

  //
  // Display the data that was received
  //
  printf("Received following message:\n%s\n",szBuf);

  closesocket(theSocket);
  return;
}

