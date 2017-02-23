/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/sem.h>
#include<sys/shm.h>

/*********Macros*******/
#define		MY_KEY		19920809
#define		MY_KEY1		19920808
#define		SHM_SIZE	1024
//#define		SRV_MSG_TYPE	1



/*********Global Variables*******/
/********* Function prototypes *****/
void toggleCase(char *buf, int cnt);

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
  int semId, shmId;
  char *pShm;
  struct sembuf smop;

  if((semId = semget(MY_KEY, 2, 0660 | IPC_CREAT))< 0)
  {
   perror("semget");
   exit(1);
  }
  else
    printf("Opened semaphore with ID %d\n", semId);

  semctl(semId, 0, SETVAL, 0);
  semctl(semId, 1, SETVAL, 0);

  if((shmId = shmget((key_t)MY_KEY1, SHM_SIZE, 0660 | IPC_CREAT)) < 0)
  {
    perror("shmget");
    exit(1);
  }
  else
    printf("Created shared Memory with ID %d\n", shmId);
  
   pShm = shmat(shmId, NULL, 0); 
   if(!pShm)
   {
     printf("Could not attach shared memory segment\n");
     exit(1);
   }
   
   while(1)
   {
     smop.sem_num = 0;
     smop.sem_op = -1;
     smop.sem_flg = 0;
     printf("I am here \n");

     semop(semId, &smop, 1);

     printf("Got the semaphore \n");
     strcpy(pShm+256, pShm);
     toggleCase(pShm+256, strlen(pShm+256));
      
     smop.sem_num = 1;
     smop.sem_op = 1;
     smop.sem_flg = 0;

     semop(semId, &smop, 1);
   }
}
 
/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
void toggleCase(char *buf, int cnt)
{
  short ii;

  for(ii = 0; ii <= cnt ; ii++)
  {    
     if(buf[ii] >= 'a' && buf[ii] <= 'z')
      buf[ii] -= 32;
     else if(buf[ii] >= 'A' && buf[ii] <= 'Z')
      buf[ii] += 32;
  }
  printf(" IN TOGGLE CASE\n");
}
  
