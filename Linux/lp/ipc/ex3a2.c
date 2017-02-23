/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

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
  int fifoFd;
  char ch;
 
  fifoFd = open("fifow", O_WRONLY);

  if(fifoFd < 0)
  {
    if(mkfifo("fifow", 0600) < 0)
    {
       printf("Error in creating Fifo\n");
       return(1);
    }
    else
    {
      printf("Created a fifo\n");
      fifoFd = open("fifow", O_WRONLY);
    }  
   }
}


    
