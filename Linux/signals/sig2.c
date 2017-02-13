#include <stdio.h>
#include <signal.h>

int sgint, sgusr1, sgusr2, sgalrm, sgothers;

void sigIntHandler(int signo)
{
  sgint++;
}

void genericHandler(int signo)
{
  switch(signo)
  {
    case SIGUSR1:
      sgusr1++;
      break;
    case SIGUSR2:
      sgusr2++;
      break;
    default:
      sgothers++;
      break;
  }
}

void sigAlarmHandler(int signo)
{
  sgalrm++;
  alarm(5);
}

int main()
{

  signal(SIGINT, sigIntHandler);
  signal(SIGUSR1, genericHandler);
  signal(SIGUSR2, genericHandler);
  signal(SIGALRM, sigAlarmHandler);

  alarm(5);
  while(1)
  {
    pause();
    printf("INT, USR1, USR2, ALARM, OTHER : %d, %d, %d, %d, %d\n", 
            sgint,sgusr1,sgusr2,sgalrm,sgothers);
  }
}


