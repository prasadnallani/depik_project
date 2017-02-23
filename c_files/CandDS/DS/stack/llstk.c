
/********************************************************************
         	Operations on Stack  using linked lists
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

typedef struct llstack
{
  element_t Elm;
  struct llstack *pNxtNode;
}llstack_t;

struct llstack *sHead;
int   stackTop = 0;


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
   llstack_t *tmp;

  if(stackTop == MAX_STACK_SIZE)
     return 1;

   if ((tmp = malloc(sizeof(llstack_t)))  == NULL )
   {
     printf("Memory not allocated for new elememt\n");
     exit(1);
   }
   tmp->Elm = *pElm;
 
   if(sHead == 0)
   {
     sHead = tmp;
     sHead -> pNxtNode = NULL;
     return 0;
   }
   tmp->pNxtNode = sHead;
   sHead = tmp;
   stackTop++;
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
  llstack_t *tmp;

  if(stackTop == 0)
    return 1;

   *pElm = sHead->Elm;
    tmp = sHead;
    sHead = sHead->pNxtNode;

    free(tmp);
    stackTop--;
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
  int ii = 0;
  llstack_t *tmp;
   
  if(stackTop == 0)
    printf("No elements to display\n");
  
  tmp = sHead;

  while(tmp)
  {
    printf("%d.empNo = %d\n", ii, tmp->Elm.empNo);
    printf("  salary = %d\n", tmp->Elm.salary);
    tmp = tmp->pNxtNode;
    ii++;
  }
}
   
  
