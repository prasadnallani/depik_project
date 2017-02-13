#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MY_KEY  12345678
#define  MSG_LEN  256
#define SRV_MSG_TYPE  1

void toggleCase(char *buf,int cnt);

int main()
{
  int mqId;
  int msgLen;
  char rxmsg[MSG_LEN];
  char txmsg[MSG_LEN];

  mqId=msgget(MY_KEY,0660 | IPC_CREAT);
  if(mqId < 0)
  {
    printf("Could not create message queue\n");
    return(1);
  }
  else
    printf("Opend message queue.Id is %d\n",mqId);
  while(1)
  {
    printf("Server:waiting for message \n");
    msgLen=msgrcv(mqId,rxmsg,MSG_LEN,SRV_MSG_TYPE,0);
    if(msgLen == -1)
    {
      perror("msgrcv");
      return 1;
    }
    printf("Received Message of size %d from client \n",msgLen);
   toggleCase(rxmsg+8,msgLen - 4);
    memcpy(txmsg,rxmsg+4,msgLen);
    msgsnd(mqId,txmsg,msgLen-4,0);
    printf("sent processed message to client\n");
  }
}


//void toggleCase(char *buf,int cnt);
//{
  


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
