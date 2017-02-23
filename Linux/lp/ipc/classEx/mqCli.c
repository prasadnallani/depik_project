/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

/*********Macros*******/
#define		MY_KEY		19920809
#define		MSG_LEN		256
#define		SRV_MSG_TYPE	1



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
  int mqId;
  int msgLen, cliMsgType;
  char rxmsg[MSG_LEN];
  char txmsg[MSG_LEN];
  int *msgHdr = (int*)txmsg;

  mqId  = msgget(MY_KEY, 0600);
  if(mqId < 0)
  {
    printf("Could not open the messae queue\n");
    return(1);
  }

  printf("Enter some request message to send to server\n");
  fgets(txmsg+8, MSG_LEN, stdin);
  
  msgHdr[0] = SRV_MSG_TYPE;
  
  /* Use process Id as client message tupe */
  cliMsgType = getpid();
  msgHdr[1] = cliMsgType;

  msgsnd(mqId, txmsg, MSG_LEN, 0);
  printf("Client: Sent given request mesage to server\n");
  
  msgLen = msgrcv(mqId, rxmsg, MSG_LEN, cliMsgType, 0);
  printf("Folowing is the response message from server\n");
  puts(rxmsg+4);
}
 
  
