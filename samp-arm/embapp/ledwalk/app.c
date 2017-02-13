
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
  unsigned int led = 8;

  digi_init();

  while(1)
  {
    outl(~led,IOPDATA);
    led = led >> 1;
    if(!led) 
      led = 8;
    for(ii=0; ii<100000; ii++);
  }
}



