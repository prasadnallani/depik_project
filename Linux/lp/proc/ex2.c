/********************************************************************
			Operations on processes
**********************************************************************/

/****************** Header Files ****************/
 
/******************Global Variables**************/

/**************** Function prototypes ************/
/**********************************************************************
* Name	:
* Description :
* Inputs :
* outputs :
*********************************************************************/
main(void)
{
  int pid;

  printf("Process id  = %d\n",getpid());
  printf("process id of parent= %d\n",getppid());
  printf("user id  = %d\n",getuid());
  printf("Group id  = %d\n",getgid());
  printf("Effective user id  = %d\n",geteuid());
  printf("Effective Group id  = %d\n",getegid());
} 
