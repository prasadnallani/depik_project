/*******************************************************************************
* File Name   : timer.c
* Description :
*  This is a timer task file. This file consits of the following
   functions :
        * alarmInit
        * alarmTask
        * alarmStart
        * alarmStop
        * addAlarmList
        * deleteAlarmList

-> The alarmInit function spawns a new task alarmTask.

-> The alarmTask continuosly checks each and every alarm block in the 
   linked list wether the timer is expired or not. If the timer expires
   it will call the fucntion which is registerd in its function pointer
   with the corresponding arguments.

-> The alarmStart function allocates memory for the new alarm block 
   and adds it to the active alarm blcok linked list.

-> The alarmStop function deletes the specified alarm block from the 
   active alarm linked list and frees its memory. 
*******************************************************************************/

#include "timer.h"

alarm_t *alarmList;
SEM_ID alarmMutex;
alarm_t *alarm;
alarm_t *pHead,*pTail;

/*******************************************************************************
* Function Name: alarmInit()
* Description:
*   This function is called from the semInit Task and this function 
*   spawns a new task alarmTask.
*******************************************************************************/
INT32  alarmInit()
{
  alarmMutex = semBCreate(0,1);
  taskSpawn("timerTask", 10, 0, 0x3000,alarmTask, 0,0,0,0,0,0,0,0,0,0);
}

/*******************************************************************************
* Function Name : alarmStart()
* Description   :
*   This function is called by from ipSendPkt().
*   This function allocates memory for a alarm structure and initializes
*   the structure fileds with the function parameters.
* Parameters    :
*   Input        : timeout in milliseconds
*                  function pointer
*                  argument to the function
* Returns       :
*                  It returns the address of the timer is the timer id 
*                  to the TCP control Block.
*******************************************************************************/
UINT32 alarmStart(INT32 tmOutInMilliSecs,void(*fp)(void *arg),void *arg)
{
  alarm_t *pAlarm;

  pAlarm = (alarm_t *)malloc(sizeof(alarm_t));

  //Initializing the structure
  //printf("\nalarm started.....\n");
  pAlarm->tmOutInMilliSecs = tmOutInMilliSecs;
  pAlarm->startTick        = tmOutInMilliSecs;
  pAlarm->fp               = fp;
  pAlarm->arg              = arg;

  //Waiting for a token
  semTake(alarmMutex,WAIT_FOREVER);

  //Add this structure to double linked list
  if(addAlarmList(pAlarm)!=0)
    printf("\nalarm insertion failed");

  semGive(alarmMutex);

  //Return the address of alarm_t by typecasting as int 
  return((UINT32)pAlarm);
}

/*******************************************************************************
* Function Name : addAlarmList()
* Description   :
-> This function is called by the alarmStart().
 
-> This function will add the newly created alarm block to the head of 
   the alarm linked list.

* Parameters    :
   Input        : The address of the newly created alarm block.
* Retruns       : 
-> It returns SUCCESS or UNSUCCESS 
*******************************************************************************/
INT32 addAlarmList(alarm_t *pnode)
{
  if(pHead == NULL)
  {
    pHead = pTail = pnode;
    pnode->pnxt = NULL;
    pnode->pprv = NULL;
    return SUCCESS;
  }
  else
  {
    pnode->pnxt = pHead;
    pHead->pprv = pnode;
    pnode->pprv = NULL;
    pHead = pnode;
    return SUCCESS;
  }
  return UNSUCCESS;
}

/*******************************************************************************
* Function Name : alarmStop()
* Description   :
-> This function will stop the alarm and delets this alarm block from
   the linked list.
-> This function will return the Round Trip Time or time out to the 
   TCB Control Block.
* Parameters    :
    Input       : The timerId(address of the timer block) which is to
                  be deleted.
* Returns       :
-> This will return the Round Trip Time to the TCP Controld Block.
*******************************************************************************/
INT32 alarmStop(UINT32 alarmId)
{
  alarm_t *pAlarm;
  pAlarm = (alarm_t *)alarmId;

  //printf("\nstoping timer id = %x\n",pAlarm);
  taskSafe();
   
  //typecast alarmId to pointer to alarm_t
  //take a token from alarm mutex semphore
  semTake(alarmMutex,WAIT_FOREVER);
  //get current system tick and subtract current from start tick, this  will gives elapsed time 

  //printf("\ntmout in alarm stop = %d\n",pAlarm -> tmOutInMilliSecs);
    
  pAlarm -> tmOutInMilliSecs = pAlarm->startTick - pAlarm->tmOutInMilliSecs;
  //printf("Round Trip Time in Alarm Stop = %d\n",pAlarm->tmOutInMilliSecs);
  //remove structure from double linked list aaand free it
  if(deleteAlarmList((alarm_t *)alarmId) != SUCCESS)
    printf("\ndeletion of alarm list failed");
  
  else 
//    printf("\nalarm block deleted successfully....\n");
  semGive(alarmMutex);
  taskUnsafe();
  return(pAlarm -> tmOutInMilliSecs);
}

/*******************************************************************************
* Function Name : deleteAlarmList()
* Description   : 
-> This function deletes an alarm block from the active alarm block 
   linked list.
-> This function returns SUCCESS or UNSUCCESS.
* Parameters    :
    Input       : The address of the alarm block whick is to be delete.
* Retruns       :
-> This function returns SUCCESS or UNSUCCESS.
*******************************************************************************/
INT32 deleteAlarmList(alarm_t *pnode)
{
  alarm_t *temp;
  temp = pnode;

  if((pnode->pnxt == NULL) && (pnode->pprv == NULL))
  {
    pHead = NULL;
    pTail = NULL;
    free(temp);
    return SUCCESS;
  }
  else if(pnode->pnxt == NULL)   //Tail
  {
    pTail = pnode->pprv;
    pTail->pnxt = NULL;
    free(temp);
    return SUCCESS;
  }
  else if(pnode->pprv == NULL)   //Head
  {
    pHead = pnode->pnxt;
    pHead->pprv = NULL;
    free(temp);
    return SUCCESS;
  }
  else                                 //Middle
  {
    pnode->pprv->pnxt = pnode->pnxt;
    pnode->pnxt->pprv = pnode->pprv;
    free(temp);
    return SUCCESS;
  }
}

/*******************************************************************************
* Function Name : alarmTask()
* Description   :
-> This is a task spawned by the alarmInit() function.
-> This task is in while(1) loop and continuously checks each and every
   alarm block whether the timer expires or not. If the timer expires
   it calls the fucntion which is registered in the function pointer of
   the structure field with the argument.
* Parameters    : No I/P parameters.
*******************************************************************************/
void alarmTask()
{
  alarm_t *temp;

  while(1)
  {
    taskDelay(1);

    semTake(alarmMutex,WAIT_FOREVER);
    temp = pHead;
    //printf("temp -> tmOutInMilliSecs = %d\n",temp -> tmOutInMilliSecs);
    while(temp != NULL)
    { 
      //printf("time out val = %d\n",temp->tmOutInMilliSecs);
      //printf("task time = %d\n",temp->tmOutInMilliSecs);
      if(temp -> tmOutInMilliSecs == 0)
      {
        printf("TIME OUTTTTTTTTTTTTTTTTTTTTTTT\n\n");
        semGive(alarmMutex);
        temp->fp(temp->arg);
        semTake(alarmMutex,WAIT_FOREVER);

        if(deleteAlarmList(temp) != SUCCESS)
          printf("\ndeletion from alarm list failed...\n");
      }
      if(temp->tmOutInMilliSecs > 0)
        temp -> tmOutInMilliSecs -= 10;
      temp = temp->pnxt;
    }  
    semGive(alarmMutex);
  }
}

