/********************************************************************
			Operations on Signals
**********************************************************************/

/********* Header Files *********/
#include<signal.h>
#include<sys/types.h>

/*********Global Variables*******/
/********* Function prototypes *****/

/**********************************************************************
* Name	: main(void)
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
main(void)
{
  pid_t pid;
  int sigNo;

  printf("Enter Process Id: \n");
  scanf("%d", &pid);
  
  printf("Enter Sig No: \n");
  scanf("%d", &sigNo);

  kill(pid, sigNo);
}

