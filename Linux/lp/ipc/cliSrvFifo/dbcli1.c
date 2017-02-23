/********************************************************************
		operations on Binary database using FIFos
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>
//#include"dbsrv.c"

/********** macros ****************/
#define 	MAX_RECS 100
#define 	BUF_LEN  120
#define 	ADD	 1
#define 	DEL	 2
#define 	GET	 3
#define 	MOD 	 4
#define 	EXIT 	 5
#define 	SUCCESS  0
#define 	NOSPACE  1
#define 	NOTFOUND 2

#define 	CLI1_FIFO "cli1Fifo"
#define 	SRV_FIFO  "srvFifo"


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

int empId;
//int indx = 0;


/********** function prototypes *********/
extern void parseMsg(Uchar *msgBuff, empRec_t *pRec);
int processDbCmdmsg(Uchar *pCmdMsg, Uchar *pRespMsg);
void userInterface(char* userReq);
void getEmpDetails4mClient(empRec_t *rec);
void frameMessage(char cmd, void *rec, Uchar *pCmdMsg);
void frameMessage1(char cmd, int *empId, Uchar *pCmdMsg);
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
  Uchar pCmdMsg[BUF_LEN], pRespMsg[BUF_LEN];
  char userReq;
  empRec_t *rec;
  
  int cli1Fd, srvFd;
  
  rec = allocateMemToRec();

  while(1)
  {
    userInterface(&userReq);  
    switch(userReq)
    {
      case ADD:
		getEmpDetails4mClient(rec);
                frameMessage(ADD, (void*)rec, pCmdMsg);
	        processDbCmdmsg(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record Added successfully..\n");
 		else
		  printf("No space to add record\n");
                break;

	case MOD:
		getEmpDetails4mClient(rec);
                frameMessage(MOD, (void*)rec, pCmdMsg);
	        processDbCmdmsg(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record modified successfully..\n");
 		else
		  printf("Record not found\n");
                break;
	case DEL:
		printf("Enter empId to be deleted\n");
		scanf("%d", &empId);
                frameMessage(DEL, (void*)&empId, pCmdMsg);
	        processDbCmdmsg(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
		  printf("Record deleted successfully..\n");
 		else
		  printf("Record not found\n");
                break;
		
	case GET:
		printf("Enter empId to Get the details\n");
		scanf("%d", &empId);
                frameMessage(GET, (void*)&empId, pCmdMsg);
	        processDbCmdmsg(pCmdMsg, pRespMsg);
                if(pRespMsg[0] == SUCCESS)
                {
                  parseMsg(pRespMsg, rec);
                  printRecDetails(rec);
                }
 		else
		  printf("Record not found\n");
                break;
	case EXIT:
		 close(srvFd);
		 close(cli1Fd);
		 return 1;
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
int processDbCmdmsg(Uchar *pCmdMsg, Uchar *pRespMsg)
{
  int cliFd, srvFd;
  int cnt;
  
  srvFd = open(SRV_FIFO, O_WRONLY);
  
  if(srvFd < 0)
  {
    printf("Could not open Server fifo\n");
    exit(1);
  }
  else
  {
    printf("Connected to Server\n"); 
    cnt = write(srvFd, pCmdMsg, BUF_LEN);

    if( cnt != BUF_LEN)
    {
      printf("Error in writing to Server FIFO\n");
      exit(1);
    }
    else
      printf("Sent given message to Server\n");
   }
      
   cliFd = open( CLI1_FIFO, O_RDONLY);

   if(cliFd < 0)
   {
     if(mkfifo( CLI1_FIFO, 0666) < 0)
     {
       printf("Error in creating Client FIFO\n");
       exit(1);
     }
     else
     {
       printf("Client FIFO created\n");
       cliFd = open(CLI1_FIFO, O_RDONLY);
     }
   }
   cnt = read( cliFd, pRespMsg, BUF_LEN);

   if(!cnt)
   {
     printf("Error in Reading response from Client FIFO\n");
     exit(1);
   }
   else
   {
     close(srvFd);
     close(cliFd);
     return 1;
   }
   
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

  printf("\n\n**** CLIENT/SERVER DATABASE PROCESSING USING FIFOs ****\n");
 printf("1.Add Employee\n");
 printf("2.Delete Employee\n");
 printf("3.Get Employee Details\n");
 printf("4.Modify Employee Details\n");
 printf("5.Exit\n");
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

    indx += sizeof(int);
  }
  memcpy((pCmdMsg + indx), CLI1_FIFO, strlen(CLI1_FIFO) + 1);

  indx += strlen(CLI1_FIFO) + 1;

}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void parseMsg(Uchar *msgBuff, empRec_t *pRec)
{
   int index = 1;
   
   memcpy((Uchar*)&pRec->id, (msgBuff+index), sizeof(int));

   index += sizeof(int); 	
   strcpy(pRec->name, msgBuff+index);

   index += strlen(pRec->name) + 1;
   memcpy((Uchar*)&pRec->salary, (msgBuff+index), sizeof(int));
 
   index += sizeof(int);
   memcpy((Uchar*)&pRec->phNum, (msgBuff+index), sizeof(int));
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      :  not completed 
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
 
 
 

    



