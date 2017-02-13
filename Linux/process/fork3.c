#include <sys/types.h>

int main()
{
  pid_t chpid, child1, child2;
  int ii,stat;

  printf("\nI am a process my process id is %d\n", getpid());
  printf("I am going to create two child proceses & make them run some code\n");

  child1 = fork();
  if(child1==0)
  {
    printf("I am first child, my pid is %d\n",getpid());
    printf("I first child going to execute following loop for 6 times\n");
    for(ii=0; ii<6; ii++)
    { 
      printf("\nI am child 1, this is iteration %d of loop \n",ii+1); 
      printf("I am tired, sleeping for 10 seconds\n\n");
      sleep(10);
    }
    exit(2);
  }

  child2 = fork();
  if(child2==0)
  {
    printf("I am second child, my pid is %d\n",getpid());
    printf("I second child going to execute following loop for 8 times\n");
    for(ii=0; ii<8; ii++)
    { 
      printf("\nI am child 2, this is iteration %d of loop \n",ii+1); 
      printf("I am tired, sleeping for 5 seconds\n\n");
      sleep(5);
    }
    exit(3);
  }

  printf("I am parent, my children are working & sleeping, i wait for them\n");
  chpid = wait(&stat);
  if(chpid == child1)
    printf("My first child terminated with status %d\n",stat); 
  if(chpid == child2)
    printf("My second child terminated with status %d\n",stat); 

  chpid = wait(&stat);
  if(chpid == child1)
    printf("My first child terminated with status %d\n",stat); 
  if(chpid == child2)
    printf("My second child terminated with status %d\n",stat); 
 
  printf("\nBoth children got terminated, now i will do the same\n\n"); 
}

