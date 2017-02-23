/********************************************************************
			Operations on Signals
**********************************************************************/

/********* Header Files *********/
#include<signal.h>

/*********Global Variables*******/
/********* Function prototypes *****/
void sigHandler(int);

/**********************************************************************
* Name	: main(void)
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
main(void)
{
 struct sigaction act, oact;
 int time;
 
 act.sa_handler = sigHandler;
 sigemptyset(&act.sa_mask);
 act.sa_flags = 0;

 if( sigaction(SIGALRM, &act, &oact) < 0)
   printf("Can't catch signal SIGALRM\n");

 printf("Eneter time in seconds\n");
 scanf("%d", &time);
 alarm(time);
 pause();
}

/**********************************************************************
* Name	: 
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
void sigHandler(int sigNo)
{
 printf("Recieved signal alarm\n");
 exit(1);
}
