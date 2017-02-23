
#include<stdio.h>

char* copyByte(char *src, char *dest, int size);
void dispArray(unsigned char *cPtr, int size);

/***********************************************************************
* Name 	      :main(void)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 int i;
 int iVal = 0x12345678;
 char cVal = 0x9a;
 float fVal = 1234.5678;
 short sVal = 0xbcde;
 int iVal1 = 0xf1234567;
 unsigned char message[15];

 unsigned char *src, *dest;

 dest = &message[0];

 src  = (char*)&iVal;
 dest = copyByte(src, dest, 4);

 src= (char*)&cVal;
 dest = copyByte(src, dest, 1);

 src= (char*)&fVal;
 dest = copyByte(src, dest, 4);

 src= (char*)&sVal;
 dest = copyByte(src, dest, 2);

 src  = (char*)&iVal1;
 dest = copyByte(src, dest, 4);

 for(i = 0; i<15; i++)
 printf("array = %x\n", message[i]);

 dispArray(message, 15);

} 
/***********************************************************************
* Name 	      : char * copyByte(char *src, char *dest, int size)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
char * copyByte(char *src, char *dest, int size)
{
  int i;

  for(i = 0 ; i<size; i++)
  {
   *dest = *src;
    dest++;
    src++;
  }
 return dest;
} 
/***********************************************************************
* Name 	      : void dispArray(unsigned char *cPtr, int size)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void dispArray(unsigned char *cPtr, int size)
{
 int ii;
 int *iPtr;
 unsigned short *sPtr;
 float *fPtr;
  
  iPtr = (int*) cPtr;
  printf("\niVal = %x", *iPtr++);

  cPtr = (char*)iPtr;
  printf("\ncVal = %x", *cPtr++);

  fPtr = (float*)cPtr;
  printf("\nfVal = %x", *fPtr++);

  sPtr = (unsigned short*)fPtr;
  printf("\nsVal = %x", *sPtr++);

  iPtr = (int*)sPtr;
  printf("\niVal1= %x\n", *iPtr);
}
