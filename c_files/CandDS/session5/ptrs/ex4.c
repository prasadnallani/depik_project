
main(void)
{

 unsigned int x;

 char *cPtr;
 short *sPtr;
 int *iPtr;

 cPtr = (char *)&x;
 sPtr = (short *)&x;
 iPtr = &x;

 printf("Before increment \n");
 printf("cPtr = %x, sPtr =%x, iPtr = %x\n", cPtr, sPtr, iPtr);
 
 cPtr+=5;
 sPtr+=5;
 iPtr+=5;

 printf(" After incrementing each by 5 \n");
 printf("cPtr = %x, sPtr =%x, iPtr = %x\n", cPtr, sPtr, iPtr);
} 

