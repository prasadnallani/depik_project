#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int cnt;

int main()
{
  char ch;
  int exitstat;
  int retval;

  printf("I am parent,my PID is %d\n",getpid());
  
  if(fork()==0)
  {
    while(1)
    {
      printf("I am child: my PID and PPID are %d and %d\n",getpid(),getppid());
      sleep(10);
      cnt++;
      if(cnt == 5)
        exit(25);
    }
  }

  else
  {
    while(1)
    {
      ch = getchar();
      if(ch=='c')
        printf("cnt = %d\n",cnt);
      if(ch=='x')
        exit(2);
      if(ch=='r')
      {
        retval = wait(&exitstat);
        printf("exit status = %d\n", WEXITSTATUS(exitstat));
        printf("retval, that is PID of child = %d\n", retval);
      }
    }
  }
}


