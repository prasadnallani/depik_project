#include<stdio.h>
short *p1;
short *p2;
int main()
{
  printf("Read address:");
  scanf("%d%d",&p1,&p2);
  printf("\n first address=%d",p1);
  printf("\n second address=%d",p2);
  printf("\n diffrence=%d",(p2-p1));
}
  
