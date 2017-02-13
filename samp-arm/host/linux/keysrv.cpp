/******************************************************************************* 
* file: keysrv.c
* Description:
*   This is udp server program that receives key press messages from the RTOS
*   programing running on dpKit and displays them.
* Ver  Date     Author         Version information
* ---- -------  -------------  ------------------------------------------------
* 1.00 26/12/03 karasala       Initial version 
*******************************************************************************/


#include <stdio.h>
#include <winsock.h>
#include "srvapp.h"

#define     MAX_MSG       100
 

unsigned char keyids[5] = {5,4,3,1,2};
void DatagramServer(short nPort);

void errExit(char *str)
{
	printf("%s\r\n",str);
  exit(0);
}

// Helper macro for displaying errors
#define PRINTERROR(s)  \
    fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

/******************************************************************************
* Name: displayAction
* Description:
******************************************************************************/
void displayKeyPressStatus(unsigned char keystat)
{
  static unsigned char oldstat = 0xf;
  unsigned char oldstats[5];
  unsigned char newstats[5];
  int i;

  for(i=0;i<5;i++)
   oldstats[i] = oldstat & (1 << i);

  keystat = keystat >> 3;
  for(i=0;i<5;i++)
   newstats[i] = keystat & (1 << i);

  for(i=0; i<4; i++)
  {
    if(oldstats[i] == newstats[i])
      continue;
    if(newstats[i])
      printf("Key %d is released\n",keyids[i]);
    else
      printf("Key %d is pressed\n",keyids[i]);
  }

  if(oldstats[4] != newstats[4])
  {
    if(newstats[4])
      printf("Key %d is pressed\n",keyids[4]);
    else
      printf("Key %d is released\n",keyids[4]);
  }

  oldstat = keystat;
}


/******************************************************************************
* Name: main
* Description:
******************************************************************************/
int main( int argc, char **argv )
{
  WORD wVersionRequested = MAKEWORD(1,1);
  WSADATA wsaData;
  int nRet;
  short nPort;

  nPort = KEY_SERV_PORT_ID;
  
  //
  // Initialize WinSock and check version
  //
  nRet = WSAStartup(wVersionRequested, &wsaData);
  if (wsaData.wVersion != wVersionRequested)
  {  
    fprintf(stderr,"\n Wrong version\n");
    return 0;
  }

  //
  // Do all the stuff a datagram server does
  //
  DatagramServer(nPort);
  
  //
  // Release WinSock
  //
  WSACleanup();
}

/*******************************************************************************
 * Name : DatagramServer
 * Description :
 ******************************************************************************/
void DatagramServer(short nPort)
{
  int nRet;
  int nLen;
  char szBuf[256];
  //
  // Create a UDP/IP datagram socket
  //
  SOCKET theSocket;
  SOCKADDR_IN saServer;
  SOCKADDR_IN saClient;

  theSocket = socket(AF_INET,      // Address family
                     SOCK_DGRAM,   // Socket type
                     IPPROTO_UDP);  // Protocol
  if (theSocket == INVALID_SOCKET)
  {
    PRINTERROR("socket()");
    return;
  }
  
  //
  // Fill in the address structure
  //

  saServer.sin_family      = AF_INET;
  saServer.sin_addr.s_addr = INADDR_ANY;   // Let WinSock assign address
  saServer.sin_port        = htons(nPort); // Use port passed from user


  //
  // bind the name to the socket
  //

  nRet = bind(theSocket,        // Socket descriptor
        (LPSOCKADDR)&saServer,  // Address to bind to
        sizeof(struct sockaddr)  // Size of address
        );
  if (nRet == SOCKET_ERROR)
  {
    PRINTERROR("bind()");
    closesocket(theSocket);
    return;
  }



  //
  // Wait for data from the client
  //
  memset(szBuf, 0, sizeof(szBuf));
  printf("Server Waiting for Key press status messages\n");
  while(1)
  {
    nLen = sizeof(saClient);
    nRet = recvfrom(theSocket, szBuf, sizeof(szBuf), 0,
		         (LPSOCKADDR)&saClient, &nLen);
    if(nRet < 0)
    {
      closesocket(theSocket);
      errExit("recvfrom error\n");
    }

    displayKeyPressStatus(szBuf[0]);
  }
  
  closesocket(theSocket);
  return;
}

