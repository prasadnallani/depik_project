#include<stdio.h>
#include<signal.h>

int mysigHandler(int signo)
{
  printf("I caught the signal %d\n",signo);
}
int main()
{
  signal(SIGINT,mysigHandler);
    while(1)
    {
      sleep(15);
      printf("I slept for 15 seconds\n");
    }
}

      
