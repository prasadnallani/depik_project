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

  fp = fopen(argv[1], "r");
  if(fp==0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  printf("\nFollowing are the numbers stored in file in text form\n\n");
  while(fscanf(fp,"%d",&num)==1) 
  {
    printf("%d\n",num); 
  }
  printf("\n");
  fclose(fp);
}

