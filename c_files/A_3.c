#include<stdio.h>
char *pc;
short *ps;
int *pi;
int main()
{
  int x=0x12345678;
  pc=&x;
  ps=&x;
  pi=&x;
  printf("\nvalue in pc=%x",*pc);
  printf("\nvalue in ps=%x",*ps);
  printf("\nvalue in pi=%x",*pi);
}

