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
int main(void)
{
  int fd, noOfInts, ii = 0, jj, stInt;
  char buff[100];

  printf("Enter no of Integers to be stored\n");
  scanf("%d",&noOfInts);
  printf("Enter starting Integer\n");
  scanf("%d",&stInt);

  fd = open("intArr", O_RDWR);

  if(fd < 0)
  {
    printf("creating File\n");
    fd = open("intArr", O_RDWR | O_CREAT, 0744);
    if(fd < 0)
    {
      printf("Unable to creat file\n");
      exit(1);
    } 
  }

  while(ii < noOfInts)
  {
     for(jj = 0; (jj < 100 && jj < noOfInts); ii++, jj++)
     {
       buff[jj] = stInt++ + '0';
       if(ii == noOfInts)
       break;
     }
     write(fd, buff, --jj);
   }
     
     
  
}
  
  

