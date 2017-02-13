
#include "board.h"

int digi_init()
{
  outl(0x3ff0f,IOPMOD);
  outl(0x0,IOPCON);
  outl(0xe,IOPDATA);
}

int app_main()
{
  unsigned int val;

  while(1)
  {
    val = inl(IOPDATA);
    val = (val >> 4) & 0xf;
    outl(val,IOPDATA);
  }
}



