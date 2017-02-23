main(void)
{

 int iArr[10];
 int *iPtr1, *iPtr2;

 iPtr1 = &iArr[1];
 iPtr2 = &iArr[7];

 printf("iPtr1 = %x, iPtr2 = %x\n", iPtr1, iPtr2);
 
 printf("Difference is\n"); 
 printf("iPtr2 - iPtr1 = %x\n", (iPtr2-iPtr1));
} 
