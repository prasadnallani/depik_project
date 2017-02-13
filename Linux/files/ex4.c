#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char buf[128];

  if(argc < 2)
  {
    printf("Filename is missing\n");
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if(fp==0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  while(fgets(buf,128,fp))
  {
    printf("%s",buf);
  }
}

