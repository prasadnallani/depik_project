#include<stdio.h>
int myfun(void);//declaration of my fun() function
extern int a;  //declaration of variable a
int main()

{
	int x;
	a=50;
	x=myfun();
	printf("my fun returned %d\n",x);
}

