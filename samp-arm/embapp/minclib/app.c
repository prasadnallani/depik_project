#include "board.h"

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

  puts("\r\nSample printf function demo program \r\n");

  while(1)
  {
    ch = getchar();
    printf("You entered character         : %c\r\n",ch);
    printf("Its ASCII code in hex is      : %x\r\n",ch);
    printf("Its ASCII code in decimal is  : %d\r\n",ch);
  }

  return 0;
}



