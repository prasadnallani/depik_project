#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

pthread_mutex_t  mlock;
pthread_t         th1;
void * th1fun(void * arg);
int main()
{
  char str1[80];
  char str2[40];
  if(pthread_mutex_init(&mlock,NULL) !=0)
  {
    printf("Mutex creation failed\n");
    exit(1);
  }
  pthread_create(&th1,NULL,th1fun,NULL);
  while(1)
  {
    pthread_mutex_lock(&mlock);
    printf("main thread:Enter two strings \n");
    fgets(str1,40,stdin);
    fgets(str2,40,stdin);
    strcat(str1,str2);
    printf("Combined string:%s\n",str1);
    pthread_mutex_unlock(&mlock);
  }
}
void * th1fun(void * arg)
{
  char str1[80];
  char  str2[40];
//  printf("i am in thread 1");
  while(1)
  {
    pthread_mutex_lock(&mlock);
    printf("Thread1 fun: enter two strings");
    fgets(str1,40,stdin);
    fgets(str2,40,stdin);
    strcat(str1,str2);
    printf("Combined string:%s\n",str1);
    pthread_mutex_unlock(&mlock);
  }
}


