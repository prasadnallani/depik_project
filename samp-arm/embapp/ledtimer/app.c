
#include "board.h"

int digi_init()
{
  outl(0x3ff0f,IOPMOD);
  outl(0x0,IOPCON);
  outl(0xe,IOPDATA);
}

int msecDelay(int msecs)
{
  unsigned int bottom;

  if (msecs > 1000)
    return 1;

  bottom = 0x10000000 - (msecs * 50000);
  outl(0x10000000,TDATA0);
  outl(1,TMOD);
  while( inl(TCNT0) > bottom);
  outl(0,TMOD);
}

int app_main()
{
  int ii;

  digi_init();

  while(1)
  {
    outl(0x0,IOPDATA);
    msecDelay(100);
    outl(0xf,IOPDATA);
    msecDelay(900);
  }
}



