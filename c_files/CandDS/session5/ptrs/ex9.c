#include<stdio.h>

void fillMemory(unsigned char *pBuff, int size, unsigned char val);
void dispBytes(unsigned char *pB, int count);
/***********************************************************************
* Name 	     :void fillMemory(unsigned char *pBuff, int size, unsigned char val)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void fillMemory(unsigned char *pBuff, int size, unsigned char val)
{
  while(size)
  {
    *pBuff = val;
    pBuff++;
    size--;
  }
}

/***********************************************************************
* Name 	      : void dispBytes(unsigned char *pB, int count)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void dispBytes(unsigned char *pB, int count)
{
  while(count)
  {
    printf("%x ", *pB);
    pB++;
    count--;
    if(!(count % 16))    
       printf("\n");
   }
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
  char *arr;
  
  if((arr = malloc(64)) == NULL)
  { 
   printf("memory not allocated fot array\n");
   exit(1);
  }

   fillMemory(arr, 64, 1);
   printf("contents of buffer\n");
   dispBytes(arr, 64);
}
  

  
