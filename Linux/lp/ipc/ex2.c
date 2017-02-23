/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

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
  int fd1[2], fd2[2];
  char buff[100];
  pid_t pid;

  if(pipe(fd1) < 0)
   printf("pipe1 Error\n");
  if(pipe(fd2) < 0)
   printf("pipe2 Error\n");

   if(pid = (fork() < 0))
     printf(" fork error\n");
  
  if(pid > 0)
  {
    printf("In Parent\n");
    while(1)
    {
    printf("In Parent\n");
    __fpurge(stdin);
    scanf("%s", buff); 
    write(fd1[1], buff, sizeof(buff));
   }
  }
  else
  {
    printf("In Child\n");
   //sleep(4);
    fd1[0] = dup2(fd1[0], 0);
    fd2[1] = dup2(fd2[1], 1);
    while(1)
    {
    printf("In Child\n");
    execlp("./togglecase", "togglecase", 0);
    read(fd1[1], buff, sizeof(buff));
    puts(buff);
    }
   }

}
    
