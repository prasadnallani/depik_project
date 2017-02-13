#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd,jj,ii=0;
  unsigned char ch;
  int offset = 0;
  unsigned char buf[16];

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

    buf[ii++] = ch;
    if(ii==16)
    {
      printf("  ");
      for(jj=0; jj<16; jj++)
      {
        if((buf[jj] >= 0x20) && (buf[jj] < 0x80))
          putchar(buf[jj]);
        else
          putchar('.');
      }
      ii=0;
    }
  }
  for(jj=ii;jj<16;jj++)
    printf("   ");

  printf("  ");
  for(jj=0; jj<ii; jj++)
  {
    if((buf[jj] >= 0x20) && (buf[jj] < 0x80))
      putchar(buf[jj]);
    else
      putchar('.');
  }

  printf("\n");
  close(fd);
}

