#include<stdio.h>
int myStrLen(char *);
main(void)
{
 int a;
 char str[8] = "gopal";
 char str2[40] = "venu"; 


 a = myStrLen(str);
 printf("length = %d\n", a);
}


