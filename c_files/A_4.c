#include<stdio.h>
int *p;
int main()
{
  int i,j;
  p=(int *)malloc(10);
   for(i=j=0;i<=9;i++)
   {
     printf(" Enter number% d: " ,++j);
     scanf("%d",(p+i));
   }
   for(i=j=0;i<=9;i++)
   {
     printf("\n Number %d= %d",++j,*(p+i));
    }

}

