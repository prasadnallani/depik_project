
/**************************** udpsrv.c ************************************/ 

#include <stdio.h>
#include <string.h>
#include <winsock.h>

#define     MAX_MSG       100

// Function prototype
void DatagramServer( short port);

// Helper macro for displaying errors
#define PRINTERROR(s)  \
    fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

////////////////////////////////////////////////////////////

void main(int argc, char **argv)
{
  WORD wVersionRequested = MAKEWORD(1,1);
  WSADATA wsaData;
  int nRet;
  short nPort;

  //
  // Check for port argument
  //
  if (argc != 2)
  {
    fprintf(stderr,"\nSyntax: udpsrv PortNumber\n");
    return;
  }

  nPort = atoi(argv[1]);
  
  //
  // Initialize WinSock and check version
  //
  nRet = WSAStartup(wVersionRequested, &wsaData);
  if (wsaData.wVersion != wVersionRequested)
  {  
    fprintf(stderr,"\n Wrong version\n");
    return;
  }

  //
  // Do all the stuff a datagram server does
  //
  DatagramServer( nPort);
  
  //
  // Release WinSock
  //
  WSACleanup();
}

////////////////////////////////////////////////////////////

void DatagramServer( short nPort)
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
  // This isn't normally done or required, but in this 
  // example we're printing out where the server is waiting
  // so that you can connect the example client.
  //
  nLen = sizeof(SOCKADDR);

  printf("Server waiting for messages\n");
 
  while(1)
  {
    //
    // Wait for data from the client
    //
    memset(szBuf, 0, sizeof(szBuf));
    nRet = recvfrom(theSocket,             // Bound socket
                  szBuf,                 // Receive buffer
                  sizeof(szBuf),         // Size of buffer in bytes
                  0,                     // Flags
                  (LPSOCKADDR)&saClient, // Buffer to receive client address 
                  &nLen);                // Length of client address buffer

    //
    // Send data back to the client
    //
    sendto(theSocket,              // Bound socket
         szBuf,                  // Send buffer
         strlen(szBuf),          // Length of data to be sent
         0,                      // Flags
         (LPSOCKADDR)&saClient,  // Address to send data to
         nLen);                  // Length of address

    printf("Received following message from client %s\n%s\n",
            inet_ntoa(saClient.sin_addr), szBuf );
  }
  //
  // Normally a server continues to run so that
  // it is available to other clients. In this
  // example, we exit as soon as one transaction
  // has taken place.
  //
  closesocket(theSocket);
  return;
}


