
#include "board.h"

int digi_init()
{
  outl(0x3ff0f,IOPMOD);
  outl(0x0,IOPCON);
  outl(0xe,IOPDATA);
}

int app_main()
{
  int ii;

  digi_init();

  while(1)
  {
    outl(0x0,IOPDATA);
    for(ii=0; ii<1000000; ii++);
    outl(0xf,IOPDATA);
    for(ii=0; ii<1000000; ii++);
  }
}



