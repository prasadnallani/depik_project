#include "board.h"

extern unsigned int vectors_start[];
extern unsigned int vectors_end[];

unsigned int isrcnt = 0; 

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
}

void initInterrupts()
{
  outl(0x01ffbff,INTMSK);
}

int cmnIrqHandler()
{
  unsigned int istat;

  istat = inl(INTPND);
  outl(istat,INTPND);

  isrcnt++;
  if(tflg)
  {
    tflg = 0;
    outl(0x0,IOPDATA);
  }
  else
  {
    tflg = 1;
    outl(0xf,IOPDATA);
  }
}


