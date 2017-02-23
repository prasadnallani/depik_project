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

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main()
{
 pthread_t th1[3];
 int ii, res, num;
 for(ii = 0; ii < 3; ii++)
 {
   res = pthread_create(&th1[ii], NULL, &threadFun1, (int*)((ii+ 1)*5));
   if(res != 0)
   {
    printf("creation of thread[%d] failed\n", ii);
    exit(1);
   }
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
    sleep((int)(arg));
    printf("sleptTime = %d\n", (int)(arg));
  }
}
