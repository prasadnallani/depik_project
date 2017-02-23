
/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define	TRUE 1

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
 OutStruct_t *pSv;
 
 if((pSv = (OutStruct_t *)(malloc(sizeof(OutStruct_t)))) == NULL)
 {
   printf("Memory not allocated for structure\n");
   exit(TRUE);
 }

 printf("enter two integers\n");
 scanf("%d %d", &x,&y);

 getSumDifAndProduct(x, y, pSv);

 printf("sum  = %d\n", pSv->sum);
 printf("Dif  = %d\n", pSv->diff);
 printf("product  = %d\n", pSv->product);
}
