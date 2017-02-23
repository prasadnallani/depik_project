#include<stdio.h>
extern int igf1;
extern int igf2;
extern int igf3;
extern int igf4;

main()
{
 f1();
 f2();
 f3();
 f4();
 printf("global variable 1 = %d\n", igf1);
 printf("global variable 2 = %d\n", igf2);
 printf("global variable 3 = %d\n", igf3);
 printf("global variable 4 = %d\n", igf4);
}
