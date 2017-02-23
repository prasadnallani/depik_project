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

/*********Global Variables*******/

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
 pthread_t th1, th2, th3;
 int res, num;

 res = pthread_create(&th1, NULL, &threadFun1, "Thread1");
 if(res != 0)
 {
   printf("creation of thread1 failed\n");
   exit(1);
  }
 
 res = pthread_create(&th2, NULL, &threadFun2, "Thread2");
 if(res != 0)
 {
   printf("creation of thread1 failed\n");
   exit(1);
  }

 res = pthread_create(&th3, NULL, &threadFun3, "Thread3");
 if(res != 0)
 {
   printf("creation of thread1 failed\n");
   exit(1);
  }
  while(1)
  {
    printf("Enter a number \n");
    scanf("%d\n", &num);
    if(num == 100)
      return;
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
    sleep(5);
    printf(" %s\n", arg);
  }
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun2(void *arg)
{
  while(1)
  {
    sleep(10);
    printf(" %s\n", arg);
  }
}
/**********************************************************************
* Name	      : 
* Description :
* Inputs      :  
* outputs     : 
*********************************************************************/
void *threadFun3(void *arg)
{
  while(1)
  {
    sleep(15);
    printf(" %s\n", arg);
  }
}
