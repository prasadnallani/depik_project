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
  
  fifoFd = open("fiforN", O_RDONLY | O_NONBLOCK);

  if(fifoFd < 0)
  {
    if(mkfifo("fiforN", 0600) < 0 )
    {
      printf("Error in Creating fifo\n");
      return(1);
    }
    else
    {
      printf("Created fiforN\n");
      fifoFd = open("fiforN", O_RDONLY | O_NONBLOCK);
    }
   }
 }

