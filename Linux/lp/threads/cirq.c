/********************************************************************
         	Operations on circular Queue 
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

typedef struct 
{

  int 		rdIndx;
  int 		wrIndx;
  int 		noOfElms;
  element_t	qBuff[MAX_Q_SIZE];

} crq_t;

 crq_t cq;


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
***********************************************************************/
int addElementToQ(const element_t *pElm)
{
  if(cq.noOfElms >= MAX_Q_SIZE)
    return Q_FULL_ERR;

  cq.qBuff[cq.wrIndx] = *pElm;

  cq.wrIndx++;

  if(cq.wrIndx == MAX_Q_SIZE)
    cq.wrIndx = 0;
 
  cq.noOfElms++;
  printf("cq.noOfElms = %d\n", cq.noOfElms);

  return SUCESS;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int getElementFromQ(element_t *pElm)
{
  if(cq.noOfElms == 0)
    return Q_UNDERFLOW_ERR;

  *pElm =  cq.qBuff[cq.rdIndx];

  cq.rdIndx++;

  if(cq.rdIndx == MAX_Q_SIZE)
    cq.rdIndx = 0;

  cq.noOfElms--;

  return SUCESS;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void displayQueue(void)
{
  int ii, tmp;

  tmp = cq.rdIndx; 
  printf("noOfElms = %d\n", cq.noOfElms);
  for(ii = 0 ; ii < cq.noOfElms; ii++)
  {
     if(tmp == MAX_Q_SIZE) 
        tmp = 0;

      printf("\n%d.empNo = %d\n", ii, cq.qBuff[tmp].empNo);
      printf("   salary= %d\n", cq.qBuff[tmp].salary);
      tmp++;
  }
}

  
