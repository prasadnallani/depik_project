#include "board.h"

extern unsigned int vectors_start[];
extern unsigned int vectors_end[];

unsigned char seconds = 0; 
unsigned char minutes = 0; 
unsigned char hours = 0; 

int tflg = 1;

void loadIntVectors()
{
  unsigned int *src = vectors_start;
  unsigned int *dst = (unsigned int *)4;;

  while(src < vectors_end)
    *dst++ = *src++;
}

void timer0Start()
{
  outl(50000000,TDATA0);
  outl(1,TMOD);
  seconds = 0;
  minutes = 0;
  hours = 0;
}

void initInterrupts()
{
  outl(0x01ffbff,INTMSK);
}

void printByte(unsigned char c)
{
  putchar2( (c/10) + '0');
  putchar2( (c%10) + '0');
}

int cmnIrqHandler()
{
  unsigned int istat;

  istat = inl(INTPND);
  outl(istat,INTPND);

  seconds++;
  if(seconds >= 60)
  {
    seconds = 0;
    minutes++;
    if(minutes == 60)
    {
      minutes = 0;
      hours++;
      if(hours == 24)
        hours = 0;
    }
  }
  printByte(hours);
  putchar2(':');
  printByte(minutes);
  putchar2(':');
  printByte(seconds);
  putchar2('\r');
  outl(~seconds,IOPDATA);
}


