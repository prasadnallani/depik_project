
/********* Header files *********/
#include<stdio.h>

/************ macros ************/
/********* global variables ***********/

/********* function prototypes ***********/
void getSumDifAndProduct(int a, int b, int *buff);

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void getSumDifAndProduct(int a, int b, int *buff)
{
  *buff++ = a+b;
  *buff++ = a-b;
  *buff = a*b;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
 int x,y, buff[3];
 printf("enter two integers\n");
 scanf("%d %d", &x,&y);
 getSumDifAndProduct(x, y, buff);
 printf("sum  = %d\n", buff[0]);
 printf("Dif  = %d\n", buff[1]);
 printf("product  = %d\n", buff[2]);
}
