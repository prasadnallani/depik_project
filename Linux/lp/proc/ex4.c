/********************************************************************
			Operations on processes
**********************************************************************/

/********* Header Files *********/
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
  char str[20], str1[20];
  pid_t pid, piv;

  printf("Enter source file name\n");
  scanf("%s", str);

  printf("Enter dest file name\n");
  scanf("%s", str1);

  execl("/bin/cp","cp", str, str1);
  
}
  
    
