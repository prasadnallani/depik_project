/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>


/*********Macros*******/
#define		MY_KEY		19920809
#define		MY_KEY1		19920808
#define		SHM_SIZE	1024
#define		MSG_LEN		256



/*********Global Variables*******/
/********* Function prototypes *****/

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

  if((semId = semget((key_t)MY_KEY, 2, 0660)) < 0)   
  {
    printf("Client:could not open semphore array\n");
    return(1);
  }
  else
    printf("Client:opened semphore array with ID =  %d\n", semId);

  if((shmId = shmget((key_t)MY_KEY1, SHM_SIZE, 0660)) < 0) 
  {
    printf("Client:could not open shared memory\n");
    return(2);
  }
  else
    printf("Client:opened shared memory with ID =  %d\n", shmId);
  
   pShm = shmat(shmId, NULL, 0);
   if(!pShm)
   {
     printf("Could not attach shared mem segment\n");
     return(3);
   } 
   
   printf("Enter some request message to send to server\n");
   fgets(pShm, MSG_LEN, stdin);

   smop.sem_num = 0;
   smop.sem_op = 1;
   smop.sem_flg = 0;
   
   semop(semId, &smop, 1);
   
   smop.sem_num = 1;
   smop.sem_op = -1;
   smop.sem_flg = 0;

   semop(semId, &smop, 1);
   puts(pShm+256); 
}

 
  
