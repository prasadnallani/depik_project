#include<stdio.h>
int g1,g2;
int g3=0x12345678;
int getlargestnum(int a,int b,int c)
{
	int large;
	large=a;

	if(b>large)
	   large=b;
	if(c>large)
	  large=c;
	return large;
}
int getsmallestnum(int a,int b,int c)
{
	int small;
	small=a;
	if(b<small)
	   small=b;
	if(c<small)
	   small=c;
	return small;
}
int main()
{
	int lg,sm;
	printf("enter three numbers\n");
	scanf("%d%d%d",&g1,&g2,&g3);
	lg=getlargestnum(g1,g2,g3);
	sm=getsmallestnum(g1,g2,g3);
	printf("Large and small of your three numbers are %d, %d\n",lg,sm);
	printf("\n %x",&g1);
}
