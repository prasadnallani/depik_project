#include<stdio.h>

int main()
{
  int fds[2],ii,n;
  char readbuf[100];
  char writebuf[100];

  if(pipe(fds) < 0)
  {
    perror("pipe creation failed");
    exit(1);
  }
  if(fork()==0) //child process
  {
    close(fds[1]);
    while(1)
    {
      n=read(fds[0],readbuf,100);
      for(ii=0;ii<n;ii++)
	readbuf[ii]=toupper(readbuf[ii]);
      puts(readbuf);
    }
  }
  //parent process
  close(fds[0]);
  while(1)
  {
    fgets(writebuf,100,stdin);
    write(fds[1],writebuf,strlen(writebuf)+1);
  }
}

