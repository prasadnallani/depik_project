#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
  pid_t pid;
  int option, stat;

  while(1)
  {
    printf("\nEnter 1 to exec 'ls' program in child process and 0 to exit\n");
    scanf("%d",&option);
    if(!option)
      exit(0);
   
    printf("\n"); 
    if(fork()==0)
      execl("/bin/ls", "ls", 0);

    pid = wait(&stat);
    printf("\nChild with pid %d is terminated with exit status %d\n",pid,
                                                    WEXITSTATUS(stat));
  }
}

