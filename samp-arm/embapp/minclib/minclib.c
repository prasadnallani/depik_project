/**************************************************************************
BCOPY
**************************************************************************/
bcopy(char *s, char *d, int n)
{
  while ((n--) > 0) 
  {
    *(d++) = *(s++);
  }
}

/**************************************************************************
PRINTF and friends

  Formats:
    %X  - 4 byte ASCII (8 hex digits)
    %x  - 2 byte ASCII (4 hex digits)
    %b  - 1 byte ASCII (2 hex digits)
    %d  - decimal
    %c  - ASCII char
    %s  - ASCII string
    %I  - Internet address in x.x.x.x notation
    %L  - Binary long
    %S  - String (multiple of 4 bytes) preceded with 4 byte
        binary length
    %M  - Copy memory.  Takes two args, len and ptr
**************************************************************************/
static char hex[]="0123456789ABCDEF";

char *do_printf( char *buf, char *fmt, int  *dp)
{
  register char *p;
  char tmp[16];
  while (*fmt) 
  {
    if (*fmt == '%') 
    {  /* switch() uses more space */
      fmt++;
      if (*fmt == 'L') 
      {
        register int h = *(dp++);
        *(buf++) = h>>24;
        *(buf++) = h>>16;
        *(buf++) = h>>8;
        *(buf++) = h;
      }
      if (*fmt == 'S') 
      {
        register int len = 0;
        char *lenptr = buf;
        p = (char *)*dp++;
        buf += 4;
        while (*p) 
        {
          *(buf++) = *p++;
          len ++;
        }
        *(lenptr++) = len>>24;
        *(lenptr++) = len>>16;
        *(lenptr++) = len>>8;
        *lenptr = len;
        while (len & 3) {
          *(buf++) = 0;
          len ++;
        }
      }
      if (*fmt == 'M') 
      {
        register int len = *(dp++);
        bcopy((char *)*dp++, buf, len);
        buf += len;
      }
      if (*fmt == 'X') 
      {
        register int h = *(dp++);
        *(buf++) = hex[(h>>28)& 0x0F];
        *(buf++) = hex[(h>>24)& 0x0F];
        *(buf++) = hex[(h>>20)& 0x0F];
        *(buf++) = hex[(h>>16)& 0x0F];
        *(buf++) = hex[(h>>12)& 0x0F];
        *(buf++) = hex[(h>>8)& 0x0F];
        *(buf++) = hex[(h>>4)& 0x0F];
        *(buf++) = hex[h& 0x0F];
      }
      if (*fmt == 'x') 
      {
        register int h = *(dp++);
        *(buf++) = hex[(h>>12)& 0x0F];
        *(buf++) = hex[(h>>8)& 0x0F];
        *(buf++) = hex[(h>>4)& 0x0F];
        *(buf++) = hex[h& 0x0F];
      }
      if (*fmt == 'b') 
      {
        register int h = *(dp++);
        *(buf++) = hex[(h>>4)& 0x0F];
        *(buf++) = hex[h& 0x0F];
      }
      if (*fmt == 'd') 
      {
        register int dec = *(dp++);
        p = tmp;
        if (dec < 0) {
          *(buf++) = '-';
          dec = -dec;
        }
        do 
        {
          *(p++) = '0' + (dec%10);
          dec = dec/10;
        } while(dec);
        while ((--p) >= tmp) *(buf++) = *p;
      }
      if (*fmt == 'I') 
      {
        buf = sprintf(buf,"%d.%d.%d.%d",
          (*(dp)>>24) & 0x00FF,
          (*(dp)>>16) & 0x00FF,
          (*(dp)>>8) & 0x00FF,
          *dp & 0x00FF);
        dp++;
      }
      if (*fmt == 'c')
        *(buf++) = *(dp++);
      if (*fmt == 's') 
      {
        p = (char *)*dp++;
        while (*p) *(buf++) = *p++;
      }
    } 
    else 
    {
      *(buf++) = *fmt;
    }
    fmt++;
  }
  *buf = 0;
  return(buf);
}

char *sprintf(buf, fmt, data)
  char *fmt, *buf;
  int data;
{
  return(do_printf(buf,fmt, &data));
}

printf(char *fmt, int data)
{
  char buf[1024],*p;
  p = buf;
  do_printf(buf,fmt,&data);
  while (*p) 
  {
    if (*p=='\n') putchar('\r');
      putchar(*p++);
  }
}


