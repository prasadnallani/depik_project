
/********************************************************************
         	Operations on Stack 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define 	MAX_STACK_SIZE 	5

/********* global variables ***********/

typedef struct
{

  int empNo;
  int salary;

}element_t;

element_t sBuff[MAX_STACK_SIZE];
int stackTop = MAX_STACK_SIZE;


/********* function prototypes ***********/
int pushElementToStack(const element_t *pElm);
int popElementFromStack(element_t *pElm);
void displayStack(void);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int pushElementToStack(const element_t *pElm)
{
   if(stackTop == 0)
     return 1;

   sBuff[--stackTop] = *pElm;
   return 0;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int popElementFromStack(element_t *pElm)
{
  if(stackTop == MAX_STACK_SIZE)
     return 1;

  *pElm = sBuff[stackTop++];
  return 0; 
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void displayStack(void)
{
  int ii = 0, tmp = stackTop;

  if(stackTop == MAX_STACK_SIZE)
    printf("No elelments to display\n");

  while(tmp < MAX_STACK_SIZE)
  {
    printf("%d. empNo = %d\n", ii, sBuff[tmp].empNo);
    printf("    salary = %d\n", sBuff[tmp].salary);
    tmp++;
    ii++;
  }
}


  
  
