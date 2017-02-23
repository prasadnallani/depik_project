#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "pktbuf.h"
#include "nwstk.h"

sock_t  sockets[MAX_SOCKETS];


/*******************************************************************************
* Function Name : socket
* Description :
*   It check the type field .If it is valid then it get one free entry in 
*   socket table, put the type field in that .Based on the type it decides
*   which function to call( udp - SOCK_DGRAM or tcp - SOCK_STREAM) ,
*   gets the control block pointer or index and put into socket structure.
*   It finally it returns the index of the socket table.
* Parameters : 
*   Input: domain name - AF_INET, PF_INET etc.
*          type - SOCK_DGRAM, SOCK_STREAM
*          protocol - 0
* Returns : socket table index.
*******************************************************************************/
int socket(int domain, int type, int protocol)
{
  int sockfd,tcbindx,temp;

  if(domain != AF_INET)
    return ERROR;

  if(type != SOCK_DGRAM && type != SOCK_STREAM )
    return ERROR;
  
  
  if(allocSocket(&sockfd) != SUCCESS)
    return ERROR;
  

  sockets[sockfd].sockType = (UINT16)type;
  if(type == SOCK_DGRAM)
  {
    sockets[sockfd].pSockCb = (void *)udpSocket(protocol); 
  }
  else if(type == SOCK_STREAM)
  { 
    //temp = tcpSocket(protocol);
    //sockets[sockfd].pSockCb = (void *)temp; 
  }
  else
  {
    /***********OTHER PROTOCOLS***************************/
  }
  if(!sockets[sockfd].pSockCb)
    return ERROR;


  return sockfd;
}
/*******************************************************************************
* Name: * allocSocket ( int *sockfd) -
* Description:
*******************************************************************************/
int allocSocket(int *sockfd)
{
  int ii;

  for(ii = 1; ii< MAX_SOCKETS; ii++)
  {
    if(sockets[ii].status == FREE)
    {
      sockets[ii].status = USED;
      *sockfd = ii;
      return SUCCESS;
    }
  }
  return ERROR;
}
/*******************************************************************************
* Function Name : bind 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpBind or tcpBind and pass the
*   control block pointer or index , sockaddr_in structure pointer and 
*   length of the structure.
*   It returns success or fail.
* Parameters :
*   input    : socket table index
*            : sockaddr_in pointer
*            : length of the structure.
* Returns : success or fail
*******************************************************************************/
int bind(int sockfd, struct sockaddr_in *addr, int addLen)
{
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf("this is bind error in bind\n" );
    return ERROR;
  }
  
  if( sockets[sockfd].sockType == SOCK_DGRAM )
  {
    return udpBind(sockets[sockfd].pSockCb, (struct sockaddr_in *)addr, addLen);
  }
  else if( sockets[sockfd].sockType == SOCK_STREAM )
  {
    //return tcpBind(sockets[sockfd].pSockCb, (struct sockaddr_in *)addr, 
    //               addLen);
  }
  else ERROR;   
  

  return SUCCESS;
}
/*******************************************************************************
* Function Name : connect 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpConnect or tcpConnect and pass the
*   control block pointer or index , sockaddr_in structure pointer and 
*   length of the structure.
*   It returns success or fail.
* Parameters :
*   input    : socket table index
*            : sockaddr_in pointer
*            : length of the structure.
* Returns : success or fail
*******************************************************************************/
int connect(int sockfd, struct sockaddr_in *addr, int addLen)
{
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf ("this is in connect connect error\n" );
    return ERROR;
  }
  if(sockets[sockfd].sockType == SOCK_DGRAM)
  {
    return udpConnect(sockets[sockfd].pSockCb, 
                             (struct sockaddr_in *)addr, addLen);
  }
  else if(sockets[sockfd].sockType == SOCK_STREAM)
  {
    //return tcpConnect(sockets[sockfd].pSockCb, 
    //                         (struct sockaddr_in *)addr, addLen);
  }
  else
  {
    return ERROR;
  }
}
#if 0
/*******************************************************************************
* Function Name : listen
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the  tcpListen and pass the
*   index , queue length.
*   It returns success or fail.
* Parameters :
*   input    : socket table index
*            : sockaddr_in pointer
*            : length of the structure.
* Returns : success or fail
*******************************************************************************/
int listen(int sockfd, int qlen)
{
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf ("this is in connect connect error\n");
    return ERROR;
  }

  if(sockets[sockfd].sockType == SOCK_STREAM)
  {
     tcpListen(sockets[sockfd].pSockCb, qlen);
     return SUCCESS;
  }
  return ERROR;
}
/****************************************************************************
* Function Name : accept
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the tcpAccept and pass the
*   control block pointer or index , sockaddr_in structure pointer and 
*   length of the structure.
*   It returns success or fail.
* Parameters :
*   input    : socket table index
*   output   : sockaddr_in pointer
*            : length of the structure.
* Returns : success or fail
*****************************************************************************/
int accept(int sockfd, struct sockaddr_in *addr, int addLen)
{
  int newsockfd, tcbIndex;

  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf ("this is in accept first error\n");
    return ERROR;
  }

  if(sockets[sockfd].sockType == SOCK_STREAM)
  {
    tcbIndex = tcpAccept(sockets[sockfd].pSockCb, 
                             (struct sockaddr_in *)addr, addLen);
    if(allocSocket(&newsockfd) != SUCCESS)
       return ERROR;

    sockets[newsockfd].sockType = SOCK_STREAM;
    sockets[newsockfd].pSockCb = (void *)tcbIndex; 

    return newsockfd;
  }
  else
  {
    printf("ERROR IN SOCKET ACCEPT \n");
    return ERROR;
  }
}

#endif
/*****************************************************************************
* Function Name : send 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpSendto or tcpWrite and pass the
*   control block pointer or index , buffer pointer and length of the
*   buffer.
* Parameters :
*   input    : socket table index
*   output   : buffer pointer
*            : length of the buffer.
* Returns : how many byte it write  otherwise error
*****************************************************************************/
int send(int sockfd, char *buf,  int len, int flags)
{
  int temp ;
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
    return ERROR;
  if(sockets[sockfd].sockType == SOCK_DGRAM)
  {
    return udpSendto(sockets[sockfd].pSockCb, buf, len, flags, 0, 0);
  }
  else if(sockets[sockfd].sockType == SOCK_STREAM)
  {
     
    //temp =  tcpWrite(sockets[sockfd].pSockCb, buf, len); 
    //return temp;                         
  }
  else
  {
    return ERROR;
  }
}
/*****************************************************************************
* sendto () -
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpSendto  and pass the
*   control block pointer or index , buffer pointer,length of the
*   buffer, sockaddr_in structure pointer and length of the structure.
* Parameters :
*   input    : socket table index
*            : buffer pointer
*            : length of the buffer.
*            : sockaddr_in structure pointer.
*            : length of the sockaddr_in structure.
* Returns : success or fail
*****************************************************************************/
int sendto(int sockfd, char *buf,  int len, int flags, 
                 struct sockaddr_in *sadd, int addrLen)
{
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
    return ERROR;
  return udpSendto(sockets[sockfd].pSockCb, buf, len, flags,
                                  (struct sockaddr_in *)sadd, addrLen);
}
/*****************************************************************************
* Function Name : recvfrom 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpRecvfrom  and pass the
*   control block pointer , buffer pointer,length of the
*   buffer, sockaddr_in structure pointer and length of the structure.
* Parameters :
*   input    : socket table index
*            : buffer pointer
*            : length of the buffer.
*   output   : sockaddr_in structure pointer
*            : length of the sockaddr_in structure.
* Returns : length of the buffer it received in buffer or error
*****************************************************************************/
int recvfrom(int sockfd, char *buf,  int len, int flags,                                                                struct sockaddr_in *sadd,int *addrLen)
{
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf("this error in recvfrom ()\n");
    return ERROR;
  }
  return udpRecvFrom(sockets[sockfd].pSockCb,buf,len,flags,
                                     (struct sockaddr_in *)sadd,addrLen);
}
/*****************************************************************************
* Function Name : recv 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpRecvfrom or tcpRead and pass the
*   control block pointer or index , buffer pointer,length of the
*   buffer.
* Parameters :
*   input    : socket table index
*            : buffer pointer
*            : length of the buffer.
*            : flags
* Returns : length of the buffer it received  or error
*****************************************************************************/
int recv(int sockfd, char *buf,  int len, int flags)
{
  int temp;

  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
    return ERROR;
  if(sockets[sockfd].sockType == SOCK_DGRAM)
  {
    return udpRecvFrom(sockets[sockfd].pSockCb, buf, len, flags,0,0);
  }
  else if(sockets[sockfd].sockType == SOCK_STREAM)
  {
     
    // temp =  tcpRead(sockets[sockfd].pSockCb, buf, len); 
    // return temp;                         
  }
  else
  {
    return ERROR;
  }
  
}

/*****************************************************************************
* Function Name : close 
* Description :
*   Based on the index it get socket structure.
*   Based on protocol field it calls the udpClose or tcpClose and pass the
*   control block pointer or index.
* Parameters :
*   input    : socket table index
*            : buffer pointer
*            : length of the buffer.
*            : flags
* Returns : success  or error
*****************************************************************************/
int socketClose(int sockfd)
{
  int stat;
  if((sockfd >= MAX_SOCKETS) || (sockets[sockfd].status  == FREE) || 
                               (sockets[sockfd].pSockCb == NULL))
  {
    printf("error in closing socket\n");
    return ERROR;
  }
  if( sockets[sockfd].sockType == SOCK_DGRAM )
    stat = udpclose(sockets[sockfd].pSockCb);
  else if( sockets[sockfd].sockType == SOCK_STREAM )
  {
    //  stat = tcpClose(sockets[sockfd].pSockCb);
  }
  else
   {
     /*********Other Protocol*********/
   }
 

  sockets[sockfd].status = FREE;
  sockets[sockfd].sockType = 0;
  sockets[sockfd].pSockCb = NULL;
  return stat;
}
/******************************************************************************
* displaysocket()
******************************************************************************/
int displaysocket()
{
  int ii;

  for(ii = 0; ii<MAX_SOCKETS; ii++)
  {
    if(sockets[ii].status == USED)
      printf("sockfd = %d,\n ",ii);
  }
}

