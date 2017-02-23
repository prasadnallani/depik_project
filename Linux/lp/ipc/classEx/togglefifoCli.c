/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

/*********Macros*******/
#define	BUF_LEN	256

/*********Global Variables*******/
/********* Function prototypes *****/

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
  int srvFd, cliFd, cnt;
  char errMsg[BUF_LEN];
  char buf[BUF_LEN];
  
  srvFd = open("srvFifo", O_WRONLY);

  if(srvFd < 0)
  {
    printf("Error in opening  server fifo\n");
    return(1);
  }
  printf("Connected to server\n");
  printf("enter some msg to send to server\n");
  fgets(buf, BUF_LEN, stdin);

  if(write(srvFd, buf, strlen(buf)+1) == strlen(buf) + 1)
   printf("sent given msg to server\n");

  cliFd = open("cliFifo", O_RDONLY);

  if(cliFd < 0)
  {
    if(mkfifo("cliFifo", 0600) < 0)
    {
     printf("Eror in creaating client fifo\n");
     return(1);
    }
    else
    {
     printf("created client fifo\n");
     cliFd = open("cliFifo", O_RDONLY);
    }
   }
   printf("Waiting for response message from servr\n");

   cnt = read(cliFd, buf, BUF_LEN);
   if(cnt)
   {
     printf("Respaone from client = %s\n", buf);
     close(srvFd);
     close(cliFd);
   }
   else
   {
     printf("Error in reading from clent\n");
     return(1);
   }
}
   
    

  
  

