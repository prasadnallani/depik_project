#define TRUE   1
#define FALSE  0
#include<stdio.h>

void ntoH(unsigned char *ptr,int len);
int main()
{
 unsigned int ip;
 char *ch;
 char *str;
 ch = (char *) malloc(25);
 printf("Ennter IP address\n");
 scanf("%s",ch);
 str = (char *) malloc(25);
 if( !ip2bin(ch,&ip) )
    printf("Invalid ip address\n");
 printf("Ip address in binary form : %x\n",ip);
 
 bin2ip(ip,str);
 printf("Entered ip address is : %s",str);
}

int ip2bin(char *str, unsigned char  *ch)
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

int bin2ip(unsigned int ip,char *str )
{
 
 unsigned char *ptr = (char *) &ip,i,*res=str;
 char ch[4];  
// memset(str,'0',15);
 for(i=1;i<=4;i++)
 {
  sprintf(ch,"%d.",*ptr);
  strcat(str,ch);
  ptr = ptr+1;
 }
  printf("%s",res);
 

}
 
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
