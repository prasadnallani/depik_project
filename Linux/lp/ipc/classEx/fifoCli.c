
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
  char str[100];
  
  fifoFd = open("fifowN", O_RDONLY);
  

  if(fifoFd < 0)
  {
    if(mkfifo("fifowN", 0600) < 0)
    {
      printf("Error in creating fifo\n");
      return(1);
    }
    else
    {
      printf("Created fifowN\n");
      fifoFd  = open("fifowN", O_RDONLY);
    }
  } 
   if(read(fifoFd, str, sizeof(str)) != sizeof(str))
   {
     perror(Emsg);
     printf("%s\n", Emsg);
   }
   else
     printf("Recieved msg = %s\n", str);

}

