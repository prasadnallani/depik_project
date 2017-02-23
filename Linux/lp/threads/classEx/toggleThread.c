
/********************************************************************
	                        Threads	
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

/*********Macros*******/
#define	MAX_MSG_LEN	256

/*********Global Variables*******/
sem_t sem1;
sem_t sem2;
char msg1[MAX_MSG_LEN];
char msg2[MAX_MSG_LEN];

/********* Function prototypes *****/
void* threadFun1(void *arg);
void toggleCase(char *buf, int cnt);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
 pthread_t thrd;
 char argMsg1[] = "Thread1:";
 int res, thNum;

 res = pthread_create(&thrd, NULL, threadFun1, argMsg1);
 if(res)
  printf("Error in creating thread\n"); 
 res = sem_init(&sem1, 0 , 0);
 res = sem_init(&sem2, 0 , 0);
 while(1)
 {
   printf("Enter message to send to thread\n");
   fgets(msg1, MAX_MSG_LEN, stdin);
   sem_post(&sem1);
   
   sem_wait(&sem2);
   printf("resp msg = %s\n",msg2);
 }

} 

/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void * threadFun1(void *arg)
{
  printf("I am %s:\n", arg);
  while(1)
  {
    sem_wait(&sem1);
    strcpy(msg2, msg1);
    toggleCase(msg2, strlen(msg2));
    sem_post(&sem2);
  }
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void toggleCase(char *buf, int cnt)
{
  short ii;

  for(ii = 0; ii <= cnt ; ii++)
  {    
     if(buf[ii] >= 'a' && buf[ii] <= 'z')
      buf[ii] -= 32;
     else if(buf[ii] >= 'A' && buf[ii] <= 'Z')
      buf[ii] += 32;
  }
  printf(" IN TOGGLE CASE\n");
}
