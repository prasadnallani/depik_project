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
 
  fifoFd = open("fifor", O_RDONLY);

  if(fifoFd < 0)
  {
    if(mkfifo("fifor", 0600) < 0)
    {
       printf("Error in creating Fifo\n");
       return(1);
    }
    else
    {
      printf("Created a fifor\n");
      fifoFd = open("fifor", O_RDONLY);
    }  
   }
}


    
