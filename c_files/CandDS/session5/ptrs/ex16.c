
#include<stdio.h>

/*********global variables*********/

/*********function prototypes*********/
 

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 int ii, *p;
 
 p = malloc(10*sizeof(int));

 for(ii = 0; ii < 10; ii++)
   p[ii] = ii+10;

 for(ii = 0; ii < 10; ii++)
  printf("p[%d] = %d\n", ii, *(p+ii));
}
 
