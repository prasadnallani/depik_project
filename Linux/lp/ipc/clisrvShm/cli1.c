/********************************************************************
		operations on Binary database
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<sys/ipc.h>

#include<sys/sem.h>
#include<sys/shm.h>
/********** macros ****************/
#define 	MAX_RECS 100
#define 	ADD	 1
#define 	DEL	 2
#define 	GET	 3
#define 	MOD 	 4
#define 	SUCCESS  0
#define 	NOSPACE  1
#define 	NOTFOUND 2

#define 	MY_KEY		19290002
#define 	SHM_SIZE	1024
#define 	MSG_LEN		256


/********* global vars *************/
typedef unsigned char Uchar;

typedef struct empRec_s
{

  int 	id;
  char	name[30];
  int   salary;
  int	phNum;
  struct empRec_s *pNxtNode;

}empRec_t;

empRec_t *pHead;
int empId, status;


/********** function prototypes *********/
void parseMsg(Uchar *msgBuff, empRec_t *pRec);
int TxAndRxDbCmdmsgThroughShm(Uchar *pCmdMsg, Uchar *pRespMsg);
void userInterface(char* userReq);
void getEmpDetails4mClient(empRec_t *rec);
void frameMessage(char cmd, void *rec, Uchar *pCmdMsg);
empRec_t* allocateMemToRec(void);
void printRecDetails(empRec_t *rec);

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
  Uchar pCmdMsg[MSG_LEN], pRespMsg[MSG_LEN];
  char userReq;
  empRec_t *rec;
  rec = allocateMemToRec();

  while(1)
  {
     userInterface(&userReq);  
    switch(userReq)
    {
      case ADD:
		getEmpDetails4mClient(rec);
                frameMessage(ADD, (void*)rec, pCmdMsg);
	        TxAndRxDbCmdmsgThroughShm(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record Added successfully..\n");
 		else
		  printf("No space to add record\n");
                break;

	case MOD:
		getEmpDetails4mClient(rec);
                frameMessage(MOD, (void*)rec, pCmdMsg);
	        TxAndRxDbCmdmsgThroughShm(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record modified successfully..\n");
 		else
		  printf("Record not found\n");
                break;
	case DEL:
		printf("Enter empId to be deleted\n");
		scanf("%d", &empId);
                frameMessage(DEL, (void*)&empId, pCmdMsg);
	        TxAndRxDbCmdmsgThroughShm(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record deleted successfully..\n");
 		else
		  printf("Record not found\n");
                break;
		
	case GET:
		printf("Enter empId to Get the details\n");
		scanf("%d", &empId);
                frameMessage(GET, (void*)&empId, pCmdMsg);
	        TxAndRxDbCmdmsgThroughShm(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
                {
                  parseMsg(pRespMsg, rec);
                  printRecDetails(rec);
                }
 		else
		  printf("Record not found\n");
                break;
     default:
	     printf("Invalid command\n");
	     break;
    }
  }
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
int TxAndRxDbCmdmsgThroughShm(Uchar *pCmdMsg, Uchar *pRespMsg)
{
  int semId, shmId;
  char *pShm;
  struct sembuf sOp;
  
   semId = semget((key_t)MY_KEY, 2, 0666 );
   if(semId < 0)
   {
     printf("Client:Could not open semaphore array\n");
     return(1);
   }
   else
     printf("Client:opened semaphore with Id = %d\n", semId);
   
  shmId = shmget((key_t)MY_KEY, SHM_SIZE, 0666);  
  if(shmId < 0)  
  {
     printf("Client:Could not open shared memory\n");
     return(2);
  }
   else
     printf("Client:opened shared memory  with Id = %d\n", shmId);
  
  pShm = shmat(shmId, NULL, 0);
  if(!pShm)
  {
     printf("Client:Could not attach shared memory\n");
     return(3);
  }
  memcpy(pShm, pCmdMsg, MSG_LEN);
  
  sOp.sem_num = 0;
  sOp.sem_op = 1;
  sOp.sem_flg = 0;

  semop(semId, &sOp, 1);
  
  sOp.sem_num = 1;
  sOp.sem_op = -1;
  sOp.sem_flg = 0;

  semop(semId, &sOp, 1);
  memcpy(pRespMsg, pShm, MSG_LEN);
} 

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void parseMsg(Uchar *msgBuff, empRec_t *pRec)
{
   int indx = 1;
   
   memcpy((Uchar*)&pRec->id, (msgBuff+indx), sizeof(int));

   indx += sizeof(int); 	
   strcpy(pRec->name, msgBuff+indx);

   indx += strlen(pRec->name) + 1;
   memcpy((Uchar*)&pRec->salary, (msgBuff+indx), sizeof(int));
 
   indx += sizeof(int);
   memcpy((Uchar*)&pRec->phNum, (msgBuff+indx), sizeof(int));
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void userInterface(char *userReq)
{
 char ch;

  printf("\n\n********** CLIENT/SERVER DATABASE PROCESSING ***********\n");
 printf("1.Add Employee\n");
 printf("2.Delete Employee\n");
 printf("3.Get Employee Details\n");
 printf("4.Modify Employee Details\n");
 printf("Enter your choice\n");
 scanf("%d", userReq);
 return;
 
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void getEmpDetails4mClient(empRec_t *rec)
{
 printf("Enter Employee Details\n");
 printf("Id:");
 scanf("%d", &rec->id);
 printf("\nName:");
 __fpurge(stdin);
 fgets(rec->name, 20, stdin);
 __fpurge(stdin);
 printf("\nSalary:");
 scanf("%d", &rec->salary);
 printf("\nPhone Number:");
 scanf("%d", &rec->phNum);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
empRec_t* allocateMemToRec(void)
{
   empRec_t *tmp;

   if((tmp = (empRec_t*)malloc(sizeof(empRec_t))) == NULL)
   {
     printf("Memory not alocated for record\n");
     exit(1);
   }
   return tmp;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void frameMessage(char cmd, void *tmp1, Uchar *pCmdMsg)
{
  empRec_t *tmp;
  int indx = 0;
  int *iPtr;
  
  memcpy((pCmdMsg + indx), &cmd, sizeof(cmd));

  indx += sizeof(cmd);
  if( (cmd == ADD) || (cmd == MOD) )
  {
    tmp = (empRec_t*)tmp1;
    memcpy((pCmdMsg + indx), &tmp->id, sizeof(tmp->id));

    indx += sizeof(tmp->id);
    memcpy((pCmdMsg + indx), tmp->name, strlen(tmp->name) + 1);
  
    indx += strlen(tmp->name) + 1;
    memcpy((pCmdMsg + indx), &tmp->salary, sizeof(tmp->salary));

    indx += sizeof(tmp->salary);
    memcpy((pCmdMsg + indx), &tmp->phNum, sizeof(tmp->phNum));

    indx += sizeof(tmp->phNum);
  } 
  else
  {
    iPtr = (int*) tmp1;
    memcpy((pCmdMsg + indx), (char*)iPtr, sizeof(int));
  }
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      :   
* Output      : 
**********************************************************************/
void printRecDetails(empRec_t *rec)
{
  printf("Record\n");
  printf("Id : %d\n", rec->id);
  printf("Name : %s\n", rec->name);
  printf("Salary : %d\n", rec->salary);
  printf("phNum : %d\n", rec->phNum);
}
 
 
 

    



