/********************************************************************
	         	Operations on files 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>

/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/
/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
main(void)
{
  int fd, fd1, fd2, fd3;
  
  fd = open("myDupTest", O_WRONLY | O_CREAT, 0744);
  if( fd < 0 )
  {
    printf("unable to open file...\n");
    exit(1);
  }
  printf("fd = %d\n", fd);
  fd1 = dup(fd);
  printf("fd1 = %d\n", fd1);
  fd2 = dup(fd);
  printf("fd2 = %d\n", fd2);
  fd3 = dup(fd);
  printf("fd3 = %d\n", fd3);
  
  write(fd1, "Hi", 2);
  write(fd2, "venu", 4);
  write(fd3, "gopal", 5);
  close(fd1);
}
    
  
     

