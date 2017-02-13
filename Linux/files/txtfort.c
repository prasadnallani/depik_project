#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
  int fd;
  unsigned char buf[256];

    if(argc < 2)
    {
      printf("\n File name is missing\n");
      exit(1);
    }
  fd=open(argv[1],O_RDWR | O_CREAT | O_TRUNC,0660);
  if(fd < 0)
  {
    printf("Could Not open file\n");
    exit(2);
  }
  printf("\n\nSimple text file creator\n");
  printf("Enter few lines ,when finished press control-D to quit\n");
  while(fgets(buf,256,stdin))
  {
    write (fd,buf,strlen(buf));
  }
  close(fd);
}

