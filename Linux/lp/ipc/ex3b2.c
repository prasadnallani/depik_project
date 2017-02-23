
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
  char Emsg[100];
  
  fifoFd = open("fifowN", O_WRONLY | O_NONBLOCK);
  
      perror(Emsg);
      printf("%s\n", Emsg);

  if(fifoFd < 0)
  {
    if(mkfifo("fifowN", 0600) < 0)
    {
      printf("Error in creating fifo\n");
      perror(Emsg);
      printf("%s\n", Emsg);
      //return(1);
    }
    else
    {
      printf("Created fifowN\n");
      fifoFd  = open("fifowN", O_WRONLY | O_NONBLOCK);
    }
  } 
}
