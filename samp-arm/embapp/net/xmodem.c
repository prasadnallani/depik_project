
// opcodes for X MODEM protocol
#define SOH     0x01
#define STX     0x02
#define EOT     0x04
#define DLE     0x10
#define ACK     0x06
#define NACK    0x15
#define CAN     0x18

/****************************************************************************

*****************************************************************************/
memcpy(unsigned char *dbuf,unsigned char *sbuf,int len)
{
int ii;
  for(ii=0;ii<len;ii++)
  {
    *dbuf = *sbuf;
     dbuf++;
     sbuf++;
  }
}
/****************************************************************************

*****************************************************************************/
strcmp(unsigned char *str1,unsigned char *str2)
{
 int ii=0;
 
 while((*(str1+ii) != '\0'))
 {
   if(*(str1 + ii) == *(str2 + ii))
    ii++;
   else
    return 0;
 }
 if(*(str1+ii)  == *(str2 + ii))
    return 1;
 else 
    return 0;
}
/****************************************************************************

*****************************************************************************/
unsigned short calcrc(unsigned char *pptr, int count)
{
  unsigned short crc,ii;

  crc = 0;
  while(--count >=0)
  {
    crc = crc ^ ((unsigned short) (*pptr++)) << 8;
    for(ii=0; ii<8; ii++)
      if(crc & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc = crc << 1;
  }
  return (crc);
}

/****************************************************************************

*****************************************************************************/
int loadintoRam(unsigned int ramAddr)
{
  int n,ii,flag;
  unsigned short crcval;
  unsigned char ch;
  unsigned char *p;
  unsigned char buff[140];
  int ix = 0,index = 0,tempindex=0,offset = 0,count=1000000;

  print_word(ramAddr);
  newline();
 
  p = (unsigned char *)&crcval;
  //Send ready character
  while(1)
  {
    putchar('C');
    while (!kbhit())
    {
      if(!(count))
      { 
         putchar('C');
         count = 1000000;
      }
      else
        count--;
    }
    ch = getchar();
    if(ch == SOH)//SOH
    {
      flag = 1;
      break;
    }
  }

  while(1) 
  {
    // Wait for SOH or EOT or CANCEL
    if(flag == 1)
      flag = 0;
    else
     ch = getchar();
    if(ch == SOH)
    {
	buff[ix++] = ch;
    }
    else if(ch == EOT)
    {
        //putchar('c');
        ch = ACK;
        putchar(ch);
        //memcpy((unsigned char *)ramAddr+index,dataBuf,index);
	//puts("EOT received\n");
	return 0;
    }
    else if(ch == CAN)
    {
      puts("CAN received\n");
      return 1;
    }
    else
    {
      //puts("received char %x while waiting for SOH \n");
      continue;
    }
  
    // Now receive the full packet
    while(ix < 133)
    {
      ch = getchar();
      buff[ix++] = ch;
    } 
    crcval = calcrc(buff+3,128);
    if((p[1] == buff[131]) && (p[0] == buff[132]))
    {
      memcpy((unsigned char *)ramAddr+index,buff+3,128);
      index = index + 128;
      ch = ACK;
      putchar(ch);
      ix = 0;
    }
    else
    {
      ch = NACK;
      putchar(ch);
      ix = 0;
    }
  }
}
