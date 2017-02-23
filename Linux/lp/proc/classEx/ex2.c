#include<signal.h>
//#include"ourhdr.h"

static void sig_usr(int);

main(void)
{
 if( signal(SIGUSR1, sig_usr) == SIG_ERR)
   printf("can't catch SIGUSR1\n");
 if( signal(SIGUSR2, sig_usr) == SIG_ERR)
   printf("can't catch SIGUSR2\n");

 for( ; ; )
  pause();
}

static void sig_usr(int signo)
{
  if(signo == SIGUSR1)
   printf("recieved SIGUSR1\n");
  else if(signo == SIGUSR2)
   printf("recieved SIGUSR2\n");
  else
   printf("recieved signal %d\n", signo);
 return;
}

  


