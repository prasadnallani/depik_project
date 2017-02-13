/******************************************************************************* 
* file: ledcntl.c
* Description:
*   This is udp client program that controls the LEDs of dpKit. Basically this
*   program sends messages to the LED server running on dpkit.
* Ver  Date     Author         Version information
* ---- -------  -------------  ------------------------------------------------
* 1.00 26/12/03 karasala       Initial version 
*******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <winsock.h>
#include "srvapp.h"


// Function prototype
void DatagramClient(char *serverIp);

// Helper macro for displaying errors
#define PRINTERROR(s)  \
    fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())


void errExit(char *str)
{
  puts(str);
  exit(0);
}

/******************************************************************************
* Name: getLedCmd 
* Description:
******************************************************************************/
int getLedCmd(unsigned char *msg)
{
  unsigned int nop, op, ledno, indx, ii;

  printf("Enter number of LED operations to perform : ");
  scanf("%d",&nop);
  indx = 0;
  msg[indx++] = (unsigned char) nop;

  for(ii=0; ii<nop; ii++)
  {
    printf("Enter operation type (LED ON = 1, LED OFF = 0) : ");
    scanf("%d",&op);
    printf("Enter LED Number (1 to 8) : ");
    scanf("%d",&ledno);
    msg[indx++] = (unsigned char) op;
    msg[indx++] = (unsigned char) ledno-1;
  }
  return indx;
}

/******************************************************************************
* Name: main 
* Description:
******************************************************************************/
int main(int argc, char **argv)
{

  WORD      wVersionRequested = MAKEWORD(1,1);
  WSADATA   wsaData;
  int       nRet;
  

  //
  // Check for the host and port arguments
  //
  if (argc != 2)
  {
    fprintf(stderr,"\nSyntax: ledcntl <serverIp>\n");
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

/************************************************************************************************
 * Name : DatagramClient
 * Description :
 ***********************************************************************************************/
void DatagramClient(char *serverIp)
{
  char         szBuf[256];
  int          nRet, n;
  SOCKET       theSocket;
  SOCKADDR_IN  saServer;
  int          nFromLen;

  printf("\nUDP Client sending to server: %s on port: %d",
                                               serverIp, LED_SERV_PORT_ID);

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
  saServer.sin_addr.S_un.S_addr   = inet_addr(serverIp);
                    // ^ Server's address
  saServer.sin_port = htons(LED_SERV_PORT_ID);  // Port number from command line

  n = getLedCmd((unsigned char *)szBuf);
  nRet = sendto(theSocket,szBuf,n,0,(struct sockaddr *)&saServer, sizeof(saServer));
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
  n = recvfrom(theSocket,            // Socket
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
 
  if(n < 0)
    errExit("recv error\n");
  if(szBuf[0]==0)
    printf("Received command success status\n");
  else
    printf("Received command error status : %d\n",szBuf[0]); 
  
  closesocket(theSocket);
  return;
}


