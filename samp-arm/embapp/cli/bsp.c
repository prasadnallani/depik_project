#include "board.h"


int console_init(void)
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

int kbhit(void)
{
  return (inl(USTAT0) & 0x20);
}

