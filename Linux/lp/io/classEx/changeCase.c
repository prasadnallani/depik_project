
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
  
  fd = open("myfile.txt", O_RDWR);
 
  if(fd < 0)
  {
   printf("unable to open file...\n");
   exit(1);
  }
    
  while( read(fd, &ch, 1) == 1)
  {
    if( islower(ch) )
      ch = ch - 32;

    lseek(fd, -1, SEEK_CUR);
    write(fd, &ch, 1);
  }
  close(fd);
}
    
