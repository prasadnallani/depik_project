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
    close(fds[0]);
    while(1)
    {
      __fpurge(stdin);
      fgets(buff, sizeof(buff), stdin); 
      write(fds[1], buff, sizeof(buff));
    }
  }
  else
  {
    close(fds[1]); 
    //sleep(2);
    while(1)
    {
      read(fds[0], buff, sizeof(buff));
      __fpurge(stdout);
      printf("In Read in Parent = ");
      puts(buff);
    }
    printf("fd1 = %d   fd2 = %d\n", fds[0],fds[1]);
  }
}
