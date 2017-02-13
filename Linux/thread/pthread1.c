#include<pthread.h>
#include<stdio.h>
int cnt;;;
pthread_t th;
void *mythfun(void *arg);
int main()
{
  char ch;
  int exitstat;
  void *retptr;
  printf("I am in main thread,going t create new thread\n");
  pthread_create(&th,NULL,mythfun,NULL);
  while(1)
  {
    printf("I am main thread\n");
    ch=getchar();
    if(ch=='c')
      printf("cnt=%d\n",cnt);
    if(ch=='x')
      exit(2);
    if(ch=='r')
    {
      printf("I am going wait till my child thread is terminated\n");
      pthread_join(th,&retptr);
      printf("my child terminated,the pointer retured is %d\n",retptr);
    }
  }
}
void *mythfun(void *arg)
{
  while(1)
  {
    printf("I am new thead\n");
    sleep(10);
    cnt++;
    if(cnt==10)
      return (void *)25;
  }
}

