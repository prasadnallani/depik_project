/********************************************************************
			Operations on processes
**********************************************************************/

/********* Header Files *********/
#include<sys/types.h>

 
/*********Global Variables*******/

/********* Function prototypes *****/
/**********************************************************************
* Name	:
* Description :
* Inputs :
* outputs :
*********************************************************************/
main(void)
{
 pid_t pid, piv;
  int status;

  pid = fork();

  if(pid == 0)
  {
    printf(" i am child\n");
    execl("/bin/ls", "ls", 0);
  }
  else
  {
    printf(" i am parent");
    piv = waitpid(pid, &status, 0); // == childpid)
    printf(" The exit status of child = %d\n", piv);
  }
}
  
    
