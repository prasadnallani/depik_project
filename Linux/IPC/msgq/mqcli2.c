#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MY_KEY 12345678
#define  MSG_LEN  256
#define  SRV_MSG_TYPE 1

int main()
{
  int mqId;
  int msgLen,cliMsgType;
  char rxmsg[MSG_LEN];
  char txmsg[MSG_LEN];
  int *msgHdr = (int *)txmsg;
  int txlen;

  mqId=msgget(MY_KEY,0);
  if(mqId < 0)
  {
    printf("Could not open the msessage queue\n");
    return(1);
  }
  printf("Client: Enter some request message to send to server\n");
  fgets(txmsg+8,MSG_LEN,stdin);
  msgHdr[0]=SRV_MSG_TYPE;
  /** USE PROCEESS ID AS CLIENT MESSAGETYYPE**/
  cliMsgType=getpid();
  msgHdr[1]=cliMsgType;
  msgsnd(mqId,txmsg,strlen(txmsg+8)+5,0);
 //printf("txt length%d\n",txlen);

  printf("Client: sent given request message to servor\n");
  msgLen=msgrcv(mqId,rxmsg,MSG_LEN,cliMsgType,0);
  printf("Client:following is the response message from servor\n");
  puts(rxmsg+4);
}

