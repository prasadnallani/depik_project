#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
  struct stat name;
  stat("dup.c",&name);
  printf("st_block size %ld",name.st_blocks);
   // printf("i node no:%d",name.st_mode);
}
