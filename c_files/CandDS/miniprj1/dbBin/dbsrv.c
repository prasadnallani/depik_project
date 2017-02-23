/********************************************************************
		operations on Binary database
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/********** macros ****************/
#define 	MAX_RECS 100
#define 	ADD	 1
#define 	DEL	 2
#define 	GET	 3
#define 	MOD 	 4
#define 	SUCCESS  0
#define 	NOSPACE  1
#define 	NOTFOUND 2



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

int empId, status;
int noOfRecords;
empRec_t *pHead;



/********** function prototypes *********/
int processDbCmdmsg(Uchar *pCmdmsg, Uchar *pRespMsg);
void parseMsg(Uchar *pCmdMsg, empRec_t *pRec);
int addEmpDetails(empRec_t *pRec);
int modifyEmpDetails(empRec_t *pRec);
int deleteEmp(int empId);
int getEmpDetails(int empId, Uchar *pOutMsg);
void fillRespMsg(Uchar *pRespMsg, char status);

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int processDbCmdmsg(Uchar *pCmdMsg, Uchar *pRespMsg)
{
  empRec_t Rec;

  if( (pCmdMsg[0] == ADD) || (pCmdMsg[0] == MOD) )
     parseMsg(pCmdMsg, &Rec);
  else
     memcpy(&empId, &pCmdMsg[1], sizeof(int));

  
  switch(pCmdMsg[0])
  {
     case ADD:
              status = addEmpDetails(&Rec);
              if(status == SUCCESS)
		fillRespMsg(pRespMsg, SUCCESS);  
              else
		fillRespMsg(pRespMsg, NOSPACE);  
   	      break;

     case MOD:
              status = modifyEmpDetails(&Rec);
              if(status == SUCCESS)
		fillRespMsg(pRespMsg, SUCCESS);  
   	      else	
		fillRespMsg(pRespMsg, NOTFOUND);  
	      break;	   	 
	     
     case DEL:
              status = deleteEmp(empId);
              if(status == SUCCESS)
		fillRespMsg(pRespMsg, SUCCESS);  
   	      else	
		fillRespMsg(pRespMsg, NOTFOUND);  
	      break;	   	 

     case GET: 
	      status = getEmpDetails(empId, pRespMsg);
              if(status == SUCCESS)
		fillRespMsg(pRespMsg, SUCCESS);  
   	      else	
		fillRespMsg(pRespMsg, NOTFOUND);  
              break;
	
     default:
	     printf("Invalid command\n");
	     break;
  }
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
***********************************************************************/
void fillRespMsg(Uchar *pRespMsg, char status)
{
  memcpy(pRespMsg, &status, sizeof(char));
}
/***********************************************************************
* Name 	      : int  addEmpDetails(empRec_t *pRec)
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int  addEmpDetails(empRec_t *pRec)
{
  empRec_t *tmp, tTmp;
  
  if(noOfRecords >= MAX_RECS)
    return NOSPACE;

  if( (tmp = malloc(sizeof(empRec_t)) ) == NULL ) 
  {
    printf("Memory not allocated for new record\n");
   //exit(1);
    return NOSPACE;
  }
   
  *tmp = *pRec;

  tmp->pNxtNode = pHead;
  pHead = tmp;
  noOfRecords++;
  return SUCCESS;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int modifyEmpDetails(empRec_t *pRec)
{
  empRec_t *tmp;
 
  if(noOfRecords == 0)
    return NOTFOUND;

  if(!pHead)
    return NOTFOUND; 
 
  tmp = pHead;
  
  while(tmp)
  {
    if(tmp->id == pRec->id)
    {
      *tmp = *pRec; 
      return SUCCESS;
    }
    tmp = tmp->pNxtNode;
  }
  return NOTFOUND;
}   
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int deleteEmp(int empId)
{
  empRec_t *tmp;
  
  if(noOfRecords == 0)
    return NOTFOUND;

  if(!pHead)
    return NOTFOUND; 

  if(pHead->id == empId)
  {
    pHead = NULL; 
    return SUCCESS;
  }
 
  tmp = pHead;
  
  while(tmp->pNxtNode)
  {
    if(tmp->pNxtNode->id == empId)
    {
      tmp->pNxtNode = tmp->pNxtNode->pNxtNode;
      noOfRecords--;
      return SUCCESS;
    }
    tmp = tmp->pNxtNode;
  }
  return NOTFOUND;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int getEmpDetails(int empId, Uchar *pOutMsg)
{
  char flag;
  int indx = 1;
  empRec_t *tmp;

  if(noOfRecords == 0)
    return NOTFOUND;
  
  if(!pHead)
    return NOTFOUND;
  
  tmp = pHead;
  while(tmp)
  {
    if(tmp->id == empId)
    {
      flag = 1;
      break;
    }
    else
      flag = 0;
    tmp = tmp->pNxtNode;
  }

  if(!flag)
    return NOTFOUND;

  memcpy(&pOutMsg[indx], (char*)&tmp->id, sizeof(tmp->id) );

  indx += sizeof(tmp->id);
  memcpy(&pOutMsg[indx], tmp->name, (strlen(tmp->name) + 1) );
  
  indx += strlen(tmp->name) + 1;
  memcpy(&pOutMsg[indx], (char*)&tmp->salary, sizeof(tmp->salary));
  
  indx += sizeof(tmp->salary);
  memcpy(&pOutMsg[indx], (char*)&tmp->phNum, sizeof(tmp->phNum));
  
  indx += sizeof(tmp->phNum);
  return SUCCESS;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************
main(void)
{
  char msg[20], msg1[20];
  processDbCmdmsg(msg, msg1);
}
*/
 
  


  
      
    
    
    

   


      
 
    
   
