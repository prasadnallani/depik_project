
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
#define	MAX_MSG_LEN	256

/*********Global Variables*******/
int serfd;

/********* Function prototypes *****/
void* threadFun1(void *arg);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
 pthread_t thrd;
 char ch;
 int res;
 struct termios newset, cuset;
  
 serfd = open("/dev/ttys0", O_RDWR);
 if(serfd < 0)
 {
   printf("could not open serial device\n");
   exit(1);
 }
  
  /******* Disable echo and canonical mode of processing *****/
 tcgetattr(0,&cuset);
 newset = cuset;
 newset.c_lflag &= ~ICANON;
 newset.c_lflag &= ~ECHO;
 tcsetattr(0, TCSANOW, &newset);

 res = pthread_create(&thrd, NULL, threadFun1, "thread");
 if(res)
 {
  printf("Error in creating thread\n"); 
  exit(1);
 }

 while(1)
 {
  /**** read from std input *****/
  read(0, &ch, 1);

  /**** write to serial device *****/
  write(serfd, &ch, 1);
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
  char ch;
  printf("I am %s:\n", arg);
  while(1)
  {
   /****** read from serial device *****/
   read(serfd , &ch, 1);
  
   /******** write to std output ****/
   write(1, &ch, 1);

  }
}
