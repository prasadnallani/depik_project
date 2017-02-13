#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  int num;

  if(argc < 2)
  {
    printf("Filename is missing\n");
    exit(1);
  }

  fp = fopen(argv[1], "w");
  if(fp==0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  printf("\nEnter integers to store in file\n");
  printf("Enter 0 to exit\n\n");
  while(1)
  {
    scanf("%d",&num);
    if(num==0)
      break;
    fwrite(&num,sizeof(int), 1, fp); 
  }
  fclose(fp);
}

