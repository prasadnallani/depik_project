#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

#define MY_KEY 12345678
#define SHM_SIZE  0X1000

void toggleCase(char *buf,int cnt);
int main()
{
  int semId,shmId;
  char *pShm;
  struct sembuf smop;
  /** create a semaphore set,containing two semaphores**/
  semId=semget(MY_KEY,2,0660|IPC_CREAT);
  if(semId < 0)
  {
    printf("could not create semaphore\n");
    return(1);
  }
  else
    printf("opened  semaphore.Id is %d\n",semId);

  /** set initial token count of both semaphores tozeos**/
  semctl(semId,0,SETVAL,0);
  semctl(semId,1,SETVAL,0);
  /**CREATE shared memory segment **/
  shmId=shmget(MY_KEY,SHM_SIZE,0660|IPC_CREAT);
  if(shmId < 0)
  {
    printf("could not create shared memory segment \n");
    return(2);
  }

  /*** Attach shaed memory segment to proces addess space **/
  pShm=shmat(shmId,NULL,0);
  if(!pShm)
  {
    printf("could not attachshard memory segment\n");
    return(3);
  }

  while(1)
  {
    /** wait for a token from semaphore 0)**/
    smop.sem_num=0;
    smop.sem_op =-1;
    smop.sem_flg=0;
    semop(semId,&smop,1);

    /** process the message available in shared memory **/
    printf("got the semaphores\n");
    strcpy(pShm+26,pShm);
    toggleCase(pShm+256,strlen(pShm+256));
    printf("processed the request message,and placed response\n");

    /** send token to semaphore 1 **/
    smop.sem_num=1;
    smop.sem_op=1;
    smop.sem_flg=0;
    semop(semId,&smop,1);
  }
}

 void toggleCase(char *str,int cnt)
{
  while(cnt>0)
  {
    if(isupper(*str))
    *str=tolower(*str);
    else if(islower(*str))
     *str=toupper(*str);
    str++;
    cnt--;
  }
}   
