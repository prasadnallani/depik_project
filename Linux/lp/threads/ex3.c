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
#define MSG_LEN		200

/*********Global Variables*******/
sem_t sem1;
char msgBuff[MSG_LEN];

/********* Function prototypes *****/
void *threadFun1( void *arg);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main()
{
 pthread_t th1;
 int  res, num;

 sem_init(&sem1, 0 , 0);

 res = pthread_create(&th1, NULL, &threadFun1, "Thread");
 if(res != 0)
 {
  printf("creation of thread failed\n");
  exit(1);
 }
 
  while(1)
  {
    printf("Enter a string \n");
    fgets(msgBuff, MSG_LEN, stdin);
    sem_post(&sem1);
    sleep(1);
  }
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun1(void *arg)
{
  while(1)
  {
    sem_wait(&sem1);
    printf("msg  : %s", msgBuff);
  }
}
