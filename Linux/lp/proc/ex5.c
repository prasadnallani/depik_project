/********************************************************************
			Operations on processes
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
  char str[20], str1[20];
  int chldStatus;
  pid_t childPid;
  char *cPtr[3];
  
  pid_t pid, piv;
  
  childPid = fork();
  
  if(!childPid)
  {
    printf("Enter source file name\n");
    scanf("%s", str);
/*
     printf("Enter dest file name\n");
     scanf("%s", str1);
*/
     cPtr[0] = "ls";	
     cPtr[1] = str;	
//     cPtr[2] = str1;

     execv("/bin/ls",cPtr);
   }
   else
   {
     wait(&chldStatus);
     printf("Exit status of child process = %d\n", chldStatus);
   }
 
} 
    
