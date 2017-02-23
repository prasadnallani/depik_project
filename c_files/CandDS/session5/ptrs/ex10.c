#include<stdio.h>

main(void)
{
 unsigned int val = 0xabcd1234;
 unsigned char *cPtr;

 cPtr = (char*) &val;
 *(cPtr+2)  = 0xef;
 
 printf(" the replaced value = %x\n", val);

}





