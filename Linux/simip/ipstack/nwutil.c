
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "ethdrv.h"
#include "nwstk.h"
/*******************************************************************************
* Name:
* Description:
*******************************************************************************/
void printBuf(unsigned char *buf, int len)
{
  int i;

  for(i=0; i<len; i++)
  {
    printf("%02x ", buf[i]);
    if((i & 0xf) == 0xf)
      printf("\n");
  }
  printf("\n");
}
/******************************************************************************
 * Name:
 * Description:
 * ***************************************************************************/
unsigned short ntohs(unsigned short s)
{
  return ( (s << 8)  | (s >> 8));
}
/******************************************************************************
 * Name:
 * Description:
 * ***************************************************************************/
unsigned short htons(unsigned short s)
{
  return ( (s >> 8) | (s << 8));
}
#if 0
void memset(unsigned char *dst, unsigned char setval, int count)
{
  while(count--)
    *dst++ = setval;
}

int memcmp(UINT8 *s1, UINT8 *s2, int count)
{
  int ii;

  for(ii=0; ii < count; ii++)
  {
    if(s1[ii] != s2[ii])
     return (s1[ii] - s2[ii]);
  }
  return 0;
}
#endif

/******************************************************************************
 * Name:
 * Description:
 * ***************************************************************************/
int ip2bin(char *str, UINT8 *ch)
{
  unsigned int sum=0;
  for(;(*str != '\0') &&(*str >= '0') && (*str <= '9');str++)
  {
    for(;(*str != '.') && (*str != '\0');sum = (sum*10)+((*str)-0x30),
                       str++);
    if(sum>255)
    {
      return FALSE; 
    }
    if(*str == '\0')
    {
      *ch = (char) sum;
      ch++;       
      return TRUE;
    }
         
    if(*str == '.')
    {  
      *ch = (char) sum;
      ch++;                  
      sum = 0;
    } 
  }
  return FALSE;
}
/******************************************************************************
 * Name:
 * Description:
 * ***************************************************************************/
void ntoH(unsigned char *ptr,int len)
{
  unsigned char temp[4],swap,*dst;
  int i=0,j=len-1;
  dst = ptr;

  if( len == 1 )
     return;
 
  for(;i<len/2;i++)
  {
    if( i != j)
    { 
      swap =ptr[i];
      ptr[i] = dst[j];
      dst[j] = swap;
      j--;
    } 
  }
}

/******************************************************************************
 * Name:
 * Description:
 * ***************************************************************************/
unsigned int htonl(unsigned int temp)
{
  ntoH((unsigned char *)&temp, 4);
  return temp;
}
/***************************************************************************
* inet_addr()
****************************************************************************/
int inet_addr(char *str)
{
   unsigned int temp = 0;
   int sum=0;
   int ii = 0, jj = 0;

   if((*str != '\0') &&(*str >= '0') && (*str <= '9'))
   {
      while(ii < 4)
      {
         for( ; (*str != '.') && (*str != '\0'); str++)
         {
            jj++;
            sum = (sum*10)+((*str)-0x30);
         }
         if(*str != 0)
           str++;
         jj = 0;
         if(sum > 255 || sum < 0)
         {
           return -1;
         }
         temp = temp | sum;
         ii++;
         if(ii < 4)
           temp = temp << 8;
         sum = 0;
       }
     temp = htonl(temp);
     return temp;
   }
   return -1;
}


