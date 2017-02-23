
/********* Header files *********/
#include<stdio.h>

/************ macros ************/
/********* global variables ***********/
typedef struct 
{

  int sum;
  int diff;
  int product;

}OutStruct_t;

/********* function prototypes ***********/
void getSumDifAndProduct(int a, int b, OutStruct_t *pSt);

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void getSumDifAndProduct(int a, int b, OutStruct_t *pSt)
{
   pSt-> sum = a+b;
  pSt-> diff = a-b;
  pSt-> product = a*b;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
 int x,y;
 OutStruct_t sV;

 printf("enter two integers\n");
 scanf("%d %d", &x,&y);

 getSumDifAndProduct(x, y, &sV);

 printf("sum  = %d\n", sV.sum);
 printf("Dif  = %d\n", sV.diff);
 printf("product  = %d\n", sV.product);
}
