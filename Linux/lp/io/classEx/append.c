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
main()
{
  int fd;
  unsigned char ch;
 
  fd = open("myfile.txt", O_WRONLY);

  if(fd < 0)
  {
   printf("unable to open file...\n");
   exit(1);
  }
  lseek(fd, 0, SEEK_END);
  write(fd, "text appended", 13);
  close(fd);
}
