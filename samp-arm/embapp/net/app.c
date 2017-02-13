
#define SUCCESS      0x0

#define TRUE         0x1
#define FALSE        0x0

#define SPACE        0x20
#define BACK_SPACE   0x08
#define DELETE       0x7f

unsigned char hexascii[17]="0123456789abcdef";
int xit;
char cmdbuf[80];
int  cix;
char ethpkt[1600];

int s3c4510_eth_rcv(unsigned char *data, int *len);

void puts(unsigned char* buff) 
{
  while(*buff) 
    putchar(*buff++);
}

unsigned char* gets(unsigned char* buff)
{
  unsigned char ch;
  unsigned int ii = 0x0;

  while(ii<(80-1))
  {
    ch = getchar();
    if(ch >= 0x20 && ch < 127)
    {
      buff[ii++] = ch;
      putchar(ch);
    }
    else if((ch == '\n') || (ch == '\r'))
    {
      newline();
      break;
    }
    else if((ch==DELETE) || (ch == '\b'))
    {
      if(ii)
      {
        ii--;
        putchar(BACK_SPACE);
        putchar(SPACE);
        putchar(BACK_SPACE);
      }
    }
  }
  buff[ii] = '\0';
  return buff;
}

newline()
{
  puts("\r\n");
}

print_byte(unsigned char ch)
{
  putchar(hexascii[ch>>4]);
  putchar(hexascii[ch&0xf]);
}

print_hword(unsigned short s)
{
  print_byte((unsigned char) (s>>8));
  print_byte((unsigned char) (s&0xff));
}

print_word(unsigned int u)
{
  print_hword((unsigned short) (u>>16));
  print_hword((unsigned short) (u&0xffff));
}

print_bytes(unsigned char *p, int len)
{
  int ii,kk;
  int jj=0;
  char lbuf[16];

  for(ii=0; ii<len; ii++)
  {
    if((ii&0xf)==0)
    {
      print_word((unsigned int)p+ii);
      puts(": ");
    }
    print_byte(p[ii]);
    lbuf[jj++] = p[ii];
    putchar(' ');
    if((ii&0xf)==0xf)
    {
      putchar(' ');
      for(kk=0; kk<16; kk++)
      {
        if( (lbuf[kk] >= 0x20) && (lbuf[kk] < 0x80))
          putchar(lbuf[kk]);
        else
          putchar('.');
      }
      jj=0;
      newline(); 
    }
  }
  newline(); 
}

int ishexdigit(unsigned char ch)
{
  if ( ((ch >= '0') && (ch <= '9')) ||  
       ((ch >= 'a') && (ch <= 'f')) ||
       ((ch >= 'A') && (ch <= 'F')) ) 
    return TRUE;
  else
    return FALSE;
}

int hexascii2bin(unsigned char ch)
{
  if ((ch >= '0') && (ch <= '9'))  
    return (ch - '0');
  if ((ch >= 'a') && (ch <= 'f'))  
    return (ch - 'a' + 10);
  if ((ch >= 'A') && (ch <= 'F'))  
    return (ch - 'A' + 10);

  //We should not come here, any how return zero
  return 0;
}

int scan_hexnum(unsigned int *pu)
{
  unsigned int uval = 0;

  while((cmdbuf[cix] == ' ') || (cmdbuf[cix] == '\t'))
    cix++;
  if(!ishexdigit(cmdbuf[cix]))
    return 1;
  while(ishexdigit(cmdbuf[cix]))
  {
    uval = (uval * 16) + hexascii2bin(cmdbuf[cix]);
    cix++;
  }
  *pu = uval;
   return SUCCESS;
}

void print_help()
{
  puts("f <adrs> <len> <val>: fill memory\r\n");
  puts("d <adrs> [<len>]    : display memory\r\n");
  puts("x <adrs>            : xmodem load\r\n");
  puts("r                   : readioreg\r\n");
  puts("w                   : writeioreg\r\n");
  puts("n                   : net receive\r\n");
}

void read_ioreg()
{
  unsigned int *p;
  if(scan_hexnum((unsigned *)&p) == SUCCESS)
  {
    print_word((unsigned)p);
    putchar(':');
    print_word(*p);
  }
  else
   puts("Invalid arguments\r\n");
}

void write_ioreg()
{
  unsigned int *p;
  unsigned int  v;
  if(scan_hexnum((unsigned *)&p) == SUCCESS)
  {
    if(scan_hexnum(&v) == SUCCESS)
    {
      *p = v;
      puts("Written ");
      print_word(v);
      puts(" at ");
      print_word((unsigned)p);
      newline();
      return;
    }
  }
   puts("Invalid arguments\n");
}

void disp_mem()
{
  unsigned char *p;
  unsigned int  len;
  if(scan_hexnum((unsigned *)&p) == SUCCESS)
  {
    if(scan_hexnum(&len) != SUCCESS)
      len = 0x100;
    print_bytes(p,len);
    return;
  }
   puts("Invalid arguments\n");
}

void fill_mem()
{
  unsigned char *p;
  unsigned int  len;
  unsigned int  val;
  int ii;

  if(scan_hexnum((unsigned *)&p) == SUCCESS)
  {
    if(scan_hexnum(&len) == SUCCESS)
    {
      if(scan_hexnum(&val) == SUCCESS)
      {
        for(ii=0; ii<len; ii++)
        {
          p[ii] = (unsigned char) val;
        }
        return;
      }
    }
  }
  puts("Invalid arguments\n");
}


int netrecv()
{
  int ethpktlen;

  s3c4510_eth_init();
  while(1)
  { 
    if(s3c4510_eth_rcv(ethpkt, &ethpktlen) == 0)
    {
      print_bytes(ethpkt, ethpktlen);
    }

  }
}

int cmdproc(unsigned char *cmdbuf)
{
  unsigned int arg;

  cix = 0;
  switch(cmdbuf[cix++])
  {
    case 'f':
      fill_mem();
      break;
    case 'd':
      disp_mem();
      break;
    case 'r':
      read_ioreg();
      break;
    case 'w':
      write_ioreg();
      break;

    case 'n':
      netrecv();
    case 'x':
      if(scan_hexnum(&arg) != SUCCESS)
        arg = 0x3fe0000;
      loadintoRam(arg);
      break;

    case '?':
    case 'h':
      print_help();
      break;

    default:
      puts("Invalid command. Enter ? for help\r\n");
  }
}

int app_main()
{
  char ch;
  console_init();
  timer0Init();
  puts("\r\nDEPIK's Samsung ARM7 Application V1.00\r\n");

  while(1)
  {
    puts("\n\rapBoot> ");
    gets(cmdbuf);
    cmdproc(cmdbuf);
  }
  puts("exiting\n\r"); 
  return 0;
}



