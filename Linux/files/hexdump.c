#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd;
  char ch;
  int offset = 0;

  if(argc < 2)
  {
    printf("Filename is missing\n");
    exit(1);
  }

  fd = open(argv[1],O_RDONLY);
  if(fd < 0)
  {
    printf("Could not open file\n");
    exit(2);
  }

  while(read(fd,&ch,1)==1)
  {
    if((offset % 16) ==0)
      printf("\n%08x  ", offset);
    printf("%02x ", ch);
    offset++;
  }
  printf("\n");
  close(fd);
}

