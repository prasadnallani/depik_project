#include<stdio.h>

void fun1(void (*ptr)());
void fun2(void);
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void fun1(void (*ptr)())
{
 (*ptr)();
 printf("Iam in function 1\n");
}

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void fun2(void)
{
 printf("i am in fun 2\n");
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
 fun1(&fun2);
 printf("i am in main\n");
}
