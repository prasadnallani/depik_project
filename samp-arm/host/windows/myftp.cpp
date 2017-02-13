//
// myftp.cpp
//
// Extremely simple, stream client example.
// Works in conjunction with Server.cpp.
//
// The program attempts to connect to the server and port
// specified on the command line. The Server program prints
// the needed information when it is started. Once connected,
// the program sends data to the server, waits for a response
// and then exits.
//
// Compile and link with wsock32.lib
//
// Pass the server name, command and filename from command line. 
//
// Example: myftp 192.168.2.200 get sample.txt
//
#include <stdio.h>
#include <winsock.h>

#define PORT_NUM  9999

// Function prototype
void transferFile(char *srvIp, char *file, int cmd);

// Helper macro for displaying errors
#define PRINTERROR(s)	\
		fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

static char szBuf[128];
////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  WORD wVersionRequested = MAKEWORD(1,1);
  WSADATA wsaData;
  char srvIp[32];
  int nRet, cmd;
  FILE *fp;

  //
  // Check for the host and port arguments
  //
  if (argc != 4)
  {
    fprintf(stderr,"\nSyntax: myftp <srvIpAddr> <cmd (get/put)> <fileName>\n");
    return 0;
  }

  
  if( !strcmp(argv[2], "put") )
  {
    cmd = 1;
    
    /*
     * if command is put file should be exist in path.
     */   
    fp = fopen(argv[3], "r");
    if( !fp )
    {
      printf("File trying to send is not exist in current directory\r\n");
      return 0;
    }
    fclose(fp);
  }
  else if( !strcmp(argv[2], "get") )
  {
    cmd = 2;
  } 
  else
  {
    printf("[Worn] Command entered was not suppoted\r\n");
    return 0;
  }
       
  //
  // Initialize WinSock and check the version
  //
  nRet = WSAStartup(wVersionRequested, &wsaData);
  if (wsaData.wVersion != wVersionRequested)
  {	
    fprintf(stderr,"\n Wrong version\n");
    fclose(fp);
    return 0;
  }


  //
  // Go do the stuff a stream client does
  //
  transferFile(argv[1], argv[3], cmd);

	
  //
  //Release WinSock
  //
  WSACleanup();
}

////////////////////////////////////////////////////////////

void transferFile( char *serverAddr, char *file, int cmd)
{
  unsigned short nPort = PORT_NUM;
  FILE *fp;
  
  printf("\nStream Client connecting to server: %s on port: %d",
			serverAddr, nPort);


  //
  // Create a TCP/IP stream socket
  //
  SOCKET	theSocket;

  theSocket = socket(AF_INET,				// Address family
  		     SOCK_STREAM,			// Socket type
		     IPPROTO_TCP);		// Protocol
  if (theSocket == INVALID_SOCKET)
  {
    PRINTERROR("socket()");
    return;
  }

  //
  // Fill in the address structure
  //
  SOCKADDR_IN saServer;

  saServer.sin_family = AF_INET;
  saServer.sin_addr.S_un.S_addr = inet_addr(serverAddr);
					// ^ Server's address
  saServer.sin_port = htons(nPort);	// Port number from command line

  //
  // connect to the server
  //
  int nRet;

  nRet = connect(theSocket,	     // Socket
	   (LPSOCKADDR)&saServer,    // Server address
	   sizeof(struct sockaddr)); // Length of server address structure
  if (nRet == SOCKET_ERROR)
  {
    PRINTERROR("socket()");
    closesocket(theSocket);
    return;
  }


  if( cmd == 1 )
  {
     int rdLen; 
     
     //send command.
     szBuf[0] = 1;
     strcpy( &szBuf[1], file);
     nRet = send(theSocket,			// Connected socket
		szBuf,			// Data buffer
		strlen(file) + 2,			// Length of data
		0);			// Flags
     if (nRet == SOCKET_ERROR)
     {
       printf("Unable to send put command\r\n");	     
       PRINTERROR("send()");
       closesocket(theSocket);
       return;
     }

     fp = fopen(file, "rb");
     if( !fp )
     {
       printf("File trying to send is not exist in current directory\r\n");
       closesocket(theSocket);
       return;
     }
     
     //Read from file and send to server.
           
     while((rdLen = fread(szBuf, 1, 128, fp)) != 0)
     { 
       nRet = send(theSocket,			// Connected socket
		szBuf,			// Data buffer
		rdLen,			// Length of data
		0);
       
       if (nRet == SOCKET_ERROR)
       {
  	 PRINTERROR("send()");
	 closesocket(theSocket);
	 return;
       }
     }
     fclose(fp);
     printf(" File was sent successfully \r\n");
     
   }
   else if ( cmd == 2 )
   {
     int rdLen; 
     
     //send command.
     szBuf[0] = 2;
     strcpy( &szBuf[1], file);
     nRet = send(theSocket,			// Connected socket
		szBuf,			// Data buffer
		strlen(file) + 2,			// Length of data
		0);			// Flags
     if (nRet == SOCKET_ERROR)
     {
       printf("Unable to send get command\r\n");	     
       PRINTERROR("send()");
       closesocket(theSocket);
       return;
     }

     fp = fopen(file, "wb+");
     if( !fp )
     {
       printf("File trying to send is not exist in current directory\r\n");
       closesocket(theSocket);
       return;
     }
     //
     // recieve data from server and write it into file
     //
     while((nRet = recv(theSocket, szBuf, 128, 0)) != 0)
     {
       if (nRet == SOCKET_ERROR)
       {
 	 PRINTERROR("recv()");
	 closesocket(theSocket);
	 return;
       }
       fwrite(szBuf, 1, nRet, fp);
     }
     fclose(fp);
     printf(" File Recied successfully from server\r\n");
   }
   closesocket(theSocket);
   return;
}
