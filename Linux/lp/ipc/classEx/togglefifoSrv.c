
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
void toggleCase(char *buf, int cnt);

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
  
  srvFd = open("srvFifo", O_RDONLY);

  if(srvFd < 0)
  {
    if(mkfifo("srvFifo", 0600) < 0)  
    {
      printf("Error in creating fifo\n");
      return(1);
    }
    else
    {
      printf("Created FIfo\n");
      srvFd = open("srvFifo", O_RDONLY);
    }
   }
  
  do
  {
   cnt =  read(srvFd, buf, BUF_LEN);
   if(cnt)
   {
     printf("Recieved Msg\n");
     toggleCase(buf, cnt);

     cliFd = open("cliFifo", O_WRONLY);

     if(cliFd)
     {
       if(write(cliFd, buf, cnt) == cnt)
       {
         printf("Sent response\n");
         close(cliFd);
       }
       else
        printf("Error in writing response to Client\n");
     }
     else
       printf("Could not open client fifo\n");
    }
    else
    {
     //perror(errMsg);
     //printf("%s\n", errMsg);
    }
   //}while(cnt);
   }while(1);
   close(srvFd);      
 } 

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
void toggleCase(char *buf, int cnt)
{
  short ii;

  for(ii = 0; ii <= cnt ; ii++)
  {    
     if(buf[ii] >= 'a' && buf[ii] <= 'z')
      buf[ii] -= 32;
     else if(buf[ii] >= 'A' && buf[ii] <= 'Z')
      buf[ii] += 32;
  }
  printf(" IN TOGGLE CASE\n");
}
