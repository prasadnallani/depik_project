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
  //int signo;

  act.sa_handler = sigHandler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  if( sigaction( SIGUSR1, &act, &oact) < 0)
    printf("Can't catch SIGUSR1\n");
  if( sigaction( SIGUSR2, &act, &oact) < 0)
    printf("Can't catch SIGUSR2\n");
  if( sigaction( SIGQUIT, &act, &oact) < 0)
    printf("Can't catch SIGQUIT\n");
  if( sigaction(SIGINT, &act, &oact) < 0)
    printf("Can't catch SIGINT\n");
  
  

  for( ; ; )
/*  {
   printf("Enter signal\n");
   scanf("%d", &signo);
   raise(signo);
  }
*/
  pause();

}
/**********************************************************************
* Name	: main(void)
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
void sigHandler(int sigNo)
{
  if(sigNo == SIGUSR1)
   printf("Recieved signal SIGUSR1\n");
  else if(sigNo == SIGUSR2)
   printf("Recieved signal SIGUSR2\n");
  else if(sigNo == SIGQUIT)
   printf("Recieved signal SIGQUIT\n");
  else if(sigNo == SIGINT)
   printf("Recieved signal SIGINT\n");
  else
   printf("recieved signal %d\n", sigNo);
}
