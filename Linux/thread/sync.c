#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>

#define MAX_MSG_LEN 256
sem_t sem1;
char msg1[MAX_MSG_LEN]="1";
char msg2[MAX_MSG_LEN]="2";
sem_t sem2;

void * thrdFun1(void *arg);
void * thrdFun2(void *arg);
void toggleCase(char *buf);
int main()
{
  pthread_t thrd1;
  char       argmsg1[]="Thread1: ";
  int        res;
  int        thNum;

  res=sem_init(&sem1,0,0);
  res=sem_init(&sem2,0,0);
  res=pthread_create(&thrd1,NULL,thrdFun1,argmsg1);

  while(1)
  {
    printf("Enter message to send to thread\n");
    fgets(msg1,MAX_MSG_LEN,stdin);
    sem_post(&sem1);
    /** wait for response **/
    sem_wait(&sem2);
    printf("resp msg : %s\n",msg2);
  }
}

void * thrdFun1(void *arg)
{
  printf("I am %s\n",arg);
  while(1)
  {
    sem_wait(&sem1);
    strcpy(msg2,msg1);
    toggleCase(msg2);
    sem_post(&sem2);
  }
}

void toggleCase(char *str)
{
  while(*str)
  {
    if(isupper(*str))
    *str=tolower(*str);
    else if(islower(*str))
     *str=toupper(*str);
    str++;
  }
}


