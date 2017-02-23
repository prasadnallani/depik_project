/********************************************************************
	                        Threads	
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<termios.h>
#include<fcntl.h>

/*********Macros*******/
#define 	MSG_LEN		200
#define 	MAX_SIZE 	5
#define 	SUCESS 		0
#define 	Q_FULL_ERR	1
#define 	Q_UNDERFLOW_ERR	2

/*********Global Variables*******/

typedef struct 
{
  char 		qBuff[MAX_Q_SIZE];
  int 		rdIndx;
  int 		wrIndx;
  int 		noOfElms;

} crq_t;

 crq_t cq;
 sem_t sem;

/********* Function prototypes *****/
int addElementToQ(const char *pElm);
int getElementFromQ(char *pElm);
void displayQueue(void);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main()
{
 pthread_t th;
 int res;

 res = pthread_create(&th, NULL, &threadFun, "thread");
 if(res != 0)
   printf("Unable to create thread\n");

 sem_init(&sem, 0 , 0);
 __fpurge(stdin);
 fgets(buff, MAX_SIZE


}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int addElementToQ(const char *pElm)
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
int getElementFromQ(char *pElm)
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

      printf("\n%d.empNo = %d\n", ii, cq.qBuff[tmp]);
      //printf("   salary= %d\n", cq.qBuff[tmp].salary);
      tmp++;
  }
}

  
