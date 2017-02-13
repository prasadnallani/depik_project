#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

int mysem_init(int key)
{
  return semget(key,1,IPC_CREAT |0660);
}
int mysem_open(int key)
{
  return semget(key,1,0);
}
int mysem_post(int semid)
{
  struct sembuf sb;
  sb.sem_num=0;
  sb.sem_op=1;
  sb.sem_flg=0;

  return semop(semid,&sb,1);
}
int mysem_wait(int semid)
{
  struct sembuf sb;
  sb.sem_num=0;
  sb.sem_op=-1;
  sb.sem_flg=0;
  return semop(semid,&sb,1);
}
int mysem_destroy(int semid)
{
  semctl(semid,0,IPC_RMID,0);
}

int main()
{
  int semid;
  char buf[100];

  semid=mysem_open(1234);
  if(semid < 0)
  {
    perror("sem open failed ");
    exit(1);
  }
  printf("semid= %d\n",semid);
  while(1)
  {
    printf("press enter key to send semaphore\n");
    fgets(buf,100,stdin);
    mysem_post(semid);
  }
}

