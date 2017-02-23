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
  if( signal( SIGUSR1, sigHandler) == SIG_ERR)
    printf("Can't catch SIGUSR1\n");
  if( signal( SIGUSR2, sigHandler) == SIG_ERR)
    printf("Can't catch SIGUSR2\n");
  if( signal( SIGQUIT, sigHandler) == SIG_ERR)
    printf("Can't catch SIGQUIT\n");
  if( signal( SIGINT, sigHandler) == SIG_ERR)
    printf("Can't catch SIGINT\n");

  for( ; ; )
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
   
