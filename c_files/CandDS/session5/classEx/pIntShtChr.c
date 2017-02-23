#include<stdio.h>
main(void)
{
  int a = 0x12345678;
  int *pi;
  short *ps;
  char *pc;
 
  pi = &a;
  ps =(short*) &a;
  pc =(char*) &a;
 
  printf("%x %x %x\n", *pi,*ps,*pc);

  *pi = 0x90abcdef;
  *ps = 0x1234;
  *pc = 0x56;

  printf("%x \n", a);

}

