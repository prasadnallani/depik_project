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
  char str[100] = " Helo DEPIK jdfla;sdkfj alskhdfa lahsdfh ahsdfh";
  
  printf("sizeof str in Srv = %d\n", sizeof(str));
  //fifoFd = open("fifowN", O_WRONLY | O_NONBLOCK);
  fifoFd = open("fifowN", O_WRONLY);
  

  if(fifoFd < 0)
  {
    perror(Emsg);
    printf("%s\n", Emsg);
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
      //fifoFd  = open("fifowN", O_WRONLY | O_NONBLOCK);
      fifoFd  = open("fifowN", O_WRONLY);
    }
  } 
   if(write(fifoFd, str, sizeof(str)) != sizeof(str))
   {
     perror(Emsg);
     printf("%s\n", Emsg);
   }
   else
     printf("written msg\n");

}

