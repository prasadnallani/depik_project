#include "board.h"

extern unsigned int isrcnt; 

void loadIntVectors();
void initInterrupts();
void timer0Start();


int serialInit2(void)
{
  outl(0x03, ULCON1);
  outl(0x09, UCON1);
  outl(0x500, UBRDIV1);
  return 0;
}

int putchar2(int ch)
{
  while (!(inl(USTAT1) & 0x40));
  outl(ch, UTXBUF1);
  return 0;
}

int getchar2(void)
{
  while (!(inl(USTAT1) & 0x20));
  return (int)inl(URXBUF1);
}

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
  char ch;

  serialInit();
  serialInit2();

  puts("\r\nTimer Interrupt Demo Program \r\n");

  loadIntVectors();
  initInterrupts();
  enableInt();
  timer0Start();

  while(1)
  {
    ch = getchar();
    putchar(ch);
  }
  return 0;
}



