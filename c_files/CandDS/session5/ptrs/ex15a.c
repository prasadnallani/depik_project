
#include<stdio.h>

/*********global variables*********/
 int array[10];
 int *p = array;

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 int ii;
 printf("p = %d\n",p);
 printf("array = %d\n",array);

 for(ii = 0; ii < sizeof(array)/sizeof(array[0]); ii++)
    p[ii] = ii+101;

 for(ii = 0; ii < sizeof(array)/sizeof(array[0]); ii++)
    printf("*array[%d] = %d\n", ii, *(array+ii)); 

 for(ii = 0; ii < sizeof(array)/sizeof(array[0]); ii++)
    printf("p[%d] = %d\n", ii, *(p+ii)); 

 for(ii = 0; ii < sizeof(array)/sizeof(array[0]); ii++)
 {
    printf("*p[%d] = %d\n", ii, *p); 
    p++;
 }
 for(ii = 0; ii < sizeof(array)/sizeof(array[0]); ii++)
    printf("array[%d] = %d\n", ii, array[ii]); 
}
 
