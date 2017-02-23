/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<sys/types.h>
#include<stdio.h>

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
  char buff[100], ch, ch1;
  int fds[2];
  
  pipe(fds);
  
  if(fork() == 0)
  {
    //close(fds[0]);
    dup2(fds[1], 0);
    dup2(fds[0], 1);
    while(1)
    {
      execlp("./toggleBuff", "toggleBuff", 0);
      read(fds[1], buff, sizeof(buff));
      __fpurge(stdout);
      printf("In Read in Parent = ");
      puts(buff);
    }
  }
  else
  {
    //close(fds[1]); 
    sleep(10);
    while(1)
    {
      __fpurge(stdin);
      fgets(buff, sizeof(buff), stdin); 
      write(fds[0], buff, sizeof(buff));
    }
    printf("fd1 = %d   fd2 = %d\n", fds[0],fds[1]);
  }
dup2(fds[1], 0);
}
