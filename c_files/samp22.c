#include<stdio.h>
int main()
{
#ifdef DEBUG 
  printf("this is for debug purpose only\n");
 #endif
  printf("hello world\n");
 }

