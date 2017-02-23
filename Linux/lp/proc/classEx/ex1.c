#include<signal.h>

mysighandler(int sigNo)
{
  printf("I am a signal %d handler\n", sigNo);
}

main(void)
{
 char ch; 
 signal(SIGINT, &mysighandler);
 while(1)
 {
  ch = getchar();
  putchar(ch);
}
}
  
