#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
  pid_t pid;
  int option, stat;
  char cmdbuf[80];
  char *cmdargs[4];

  while(1)
  {
    printf("myshell> ");
    gets(cmdbuf);
    cmdargs[0] = cmdbuf;   
    cmdargs[1] = 0;   

    if(strncmp(cmdbuf,"ver",3)==0)
    {
      printf("Simple shell version 1.00, Sep 25, 2008\n");
      continue; 
    }
    if(strncmp(cmdbuf,"quit",4)==0)
      exit(0); 

    if(fork()==0)
    {
      execvp(cmdbuf, cmdargs);
      exit(0);
    }

    pid = wait(&stat);
  }
}

