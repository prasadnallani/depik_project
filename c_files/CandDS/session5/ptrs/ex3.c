main(void)
{

 unsigned int x;

 char *cPtr;
 short *sPtr;
 int *iPtr;

 cPtr = (char *)&x;
 sPtr = (short *)&x;
 iPtr = &x;
 
 x = 0x12345678;

 printf("*cPtr = %x, *sPtr =%x, *iPtr = %x\n", *cPtr, *sPtr, *iPtr);
} 


