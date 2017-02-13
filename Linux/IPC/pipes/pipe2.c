#include<stdio.h>
int main()
{
  int pfds1[2],ii,n;
  int pfds2[2];
  char readbuf[100];
  char writebuf[100];
  if(pipe(pfds1) < 0)
  {
    perror("pipe creation failed");
    exit(1);
  }
  if(pipe(pfds2) < 0)
  {
    perror("pipe creation failed");
    exit(1);
  }
  if(fork()==0) //child process
  {
    close(pfds1[1]);
    close(pfds2[0]);
    while(1)
    {
      n=read(pfds1[0],readbuf,100);
      for(ii=0;ii<n;ii++)
      {
	if(isupper(readbuf[ii]))
	    readbuf[ii]=tolower(readbuf[ii]);
	 else
	 readbuf[ii]=toupper(readbuf[ii]);
      }
      write(pfds2[1],readbuf,n);
    }
  }
  //parent process
  close(pfds1[0]);
  close(pfds2[1]);	
  while(1)
  {
    fgets(writebuf,100,stdin);
    write(pfds1[1],writebuf,strlen(writebuf)+1);
    read(pfds2[0],writebuf,100);
    puts(writebuf);
  }
}
	   
