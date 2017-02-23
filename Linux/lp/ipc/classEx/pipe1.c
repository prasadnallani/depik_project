/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<sys/types.h>

/*********Global Variables*******/
/********* Function prototypes *****/

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
  int fds[2];
  
  pipe(fds);
  printf("fd1 = %d   fd2 = %d\n", fds[0],fds[1]);

}


    
