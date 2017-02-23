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
void *threadFun2( void *arg);
void *threadFun3( void *arg);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main()
{
 pthread_t th1, th2, th3,th4;
 int ii, res, num;

 sem_init(&sem1, 0 , 0);
 res = pthread_create(&th1, NULL, &threadFun1, (int*)0);
 if(res != 0)
 {
   printf("creation of thread1 failed\n");
   exit(1);
  }
 res = pthread_create(&th2, NULL, &threadFun2, (int*)1);
 if(res != 0)
 {
   printf("creation of thread2 failed\n");
   exit(1);
  }
 res = pthread_create(&th3, NULL, &threadFun3, (int*)2);
 if(res != 0)
 {
   printf("creation of thread3 failed\n");
   exit(1);
  }
 
  {
    printf("Enter a string \n");
    fgets(msgBuff, MSG_LEN, stdin);
    sem_post(&sem1);
  }
  while(1);
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun1(void *arg)
{
   char buff[MSG_LEN];
   
    sem_wait(&sem1);
    printf("Thread%d :\n", arg);
    printf("Enter line1\n");
    fgets(buff, MSG_LEN, stdin);
    printf("%s\n", buff);
    printf("Enter line2\n");
    fgets(buff, MSG_LEN, stdin);
    printf("%s\n", buff);
    sem_post(&sem1);
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun2(void *arg)
{
  char buff2[MSG_LEN];
    sem_wait(&sem1);
    printf("Thread%d \n:", arg);
    printf("Enter line1\n");
    fgets(buff2, MSG_LEN, stdin);
    printf("%s\n", buff2);
    printf("Enter line2\n");
    fgets(buff2, MSG_LEN, stdin);
    printf("%s\n", buff2);
    sem_post(&sem1);
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun3(void *arg)
{
  char buff2[MSG_LEN];
    sem_wait(&sem1);
    printf("Thread%d :\n", arg);
    printf("Enter line1\n");
    fgets(buff2, MSG_LEN, stdin);
    printf("%s\n", buff2);
    printf("Enter line2\n");
    fgets(buff2, MSG_LEN, stdin);
    printf("%s\n", buff2);
    sem_post(&sem1);
}
