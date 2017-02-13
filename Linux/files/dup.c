#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd;
  unsigned char buf[256];


  fd = open("dupdemo.txt", O_RDWR | O_CREAT | O_TRUNC,0660);
  if(fd < 0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  dup2(fd,1);
  printf("Sample string one\n");
  printf("Sample string two\n");
  printf("Sample string three\n");
}

