#include "board.h"

extern unsigned int isrcnt; 

void loadIntVectors();
void initInterrupts();
void timer0Start();

int serialInit(void)
{
  outl(0x03, ULCON0);
  outl(0x09, UCON0);
  outl(0x500, UBRDIV0);
  return 0;
}

int putchar(int ch)
{
  while (!(inl(USTAT0) & 0x40));
  outl(ch, UTXBUF0);
  return 0;
}

int getchar(void)
{
  while (!(inl(USTAT0) & 0x20));
  return (int)inl(URXBUF0);
}

void puts(unsigned char* buff) 
{
  while(*buff) 
    putchar(*buff++);
}

int app_main()
{

  serialInit();

  puts("\r\nTimer Interrupt Demo Program \r\n");

  loadIntVectors();
  initInterrupts();
  enableInt();
  timer0Start();

  isrcnt = 0;
  while(1)
  {
    getchar();
    printf("isrcnt : %d\r\n",isrcnt);
  }
  return 0;
}



