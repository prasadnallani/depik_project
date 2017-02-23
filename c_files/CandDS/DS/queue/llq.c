

/********************************************************************
         	Operations on Queue 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define 	MAX_Q_SIZE 	5
#define 	SUCESS 		0
#define 	Q_FULL_ERR	1
#define 	Q_UNDERFLOW_ERR	2

/********* global variables ***********/

typedef struct
{

  int empNo;
  int salary;

}element_t;


typedef struct llq
{
 
 element_t   Elm; 
 struct llq *qNxtNode;

}llq_t;
 
llq_t *qHead;
int   noOfElms;



/********* function prototypes ***********/
int addElementToQ(const element_t *pElm);
int getElementFromQ(element_t *pElm);
void displayQueue(void);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int addElementToQ(const element_t *Elm)
{
  llq_t *new, *tmp;
 
  if( (new = (llq_t*) malloc(sizeof(llq_t)) ) == NULL)
  {
   printf("memory not allocated for new element\n");
   exit(1);
  }

  new->Elm = *Elm;

  if(noOfElms == MAX_Q_SIZE)
     return Q_FULL_ERR;

  if(!qHead)
  {
     qHead = new;
     qHead->qNxtNode = NULL;
     noOfElms++;
     return SUCESS;
  }
   tmp = qHead;

   while(tmp->qNxtNode)
    tmp = tmp->qNxtNode;

   tmp ->qNxtNode = new;
   tmp->qNxtNode->qNxtNode = NULL;

   noOfElms++;
   return SUCESS;
}
   
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int getElementFromQ(element_t *qElm)
{
  if(noOfElms == 0)
    return Q_UNDERFLOW_ERR;
  
  *qElm = qHead->Elm;
  free(qHead); 
  qHead = qHead->qNxtNode;
  
  noOfElms--;
  return SUCESS;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void displayQueue(void)
{
  llq_t *tmp;

  if(!qHead)
  {
    printf("No elements to display\n");
    return;
  }
  tmp = qHead;
  
  while(tmp)
  {
    printf("empNo = %d\n", tmp->Elm.empNo);
    printf("salary = %d\n", tmp->Elm.salary);
    tmp = tmp->qNxtNode;
  }
  return;
}
   
  

 
     
  

