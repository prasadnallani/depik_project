#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUF_LEN  256

int main()
{
  int srvFd;
  int cliFd;
  char txmsg[BUF_LEN];
  char rxmsg[BUF_LEN];
  int cnt;
  srvFd=open("srvfifo",O_WRONLY);
  if(!srvFd)
  {
    printf("error in opening server fifo\n");
    return(1);
  }
  printf("connected to server\n");
  printf("enter some message to send to servor\n");
  fgets(txmsg,BUF_LEN,stdin);

  write(srvFd,txmsg,strlen(txmsg)+1);
  printf("sent given message to server\n");
  
  cliFd=open("clififo",O_RDONLY);
  if(cliFd < 0)
  {
    if(mkfifo("clififo",0600) < 0)
    {
      printf("enter in creating client fifo\n");
      return(1);
    }
    else
    {
      cliFd=open("clififo",O_RDONLY);
      printf("created client fifo\n");
    }
  }
  printf("waiting for response message from servor\n");
  cnt=read(cliFd,rxmsg,BUF_LEN);
  puts(rxmsg);
  close(srvFd);
  close(cliFd);
}
    
