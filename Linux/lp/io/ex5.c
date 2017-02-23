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
  
  fd = open("myDup2Test", O_WRONLY | O_CREAT, 0744);
  if( fd < 0 )
  {
    printf("unable to open file...\n");
    exit(1);
  }
  dup2(fd,1); 
  printf("\ndup2 testing\n");

  write(fd, "Hi", 2);
  write(fd, "venu", 4);
  write(fd, "gopal", 5);
  
  close(fd1);
}
    
  
     

