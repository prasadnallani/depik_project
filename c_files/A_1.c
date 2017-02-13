#include<stdio.h>
struct record
{
  int id;
  char name[20];
  char addrs[40];
 };
int *p;
short *ps;
char *pc;
struct record *pr;
main()
{
  printf("\n  contents of pointer varibles %d %d %d %d",p,ps,pc,pr);
  printf("\n  address of pointer varibles %x %x %x %x",&p,&ps,&pc,&pr);
  printf("\n  int size=%d ",sizeof(p));
  printf("\n  char size=%d ",sizeof(pc));
  printf("\n   short size=%d ",sizeof(ps));
  printf("\n   struct size=%d ",sizeof(pr));
  printf("\n  int size=%d ",sizeof(*p));
  printf("\n  char size=%d ",sizeof(*pc));
  printf("\n   short size=%d ",sizeof(*ps));
  printf("\n   struct size=%d ",sizeof(*pr));
   p=(int *)100;
   ps=(short *)100;
   pc=(char *)100;
   
   
  

}
