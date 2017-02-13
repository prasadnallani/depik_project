/*********stack implementation using linked list****/
#include"stack.h"
#include<stdio.h>
struct node
{
  struct student stu;
  struct node *pnxt;
};

struct node *pStkHd;
int pushItem(const struct student *ps)
{
  struct node *pn;
  pn=malloc(sizeof(*pn));
  if(pn==NULL)
  {
    return STK_FULL_ERR;
  }
  pn->stu=*ps;
  pn->pnxt=pStkHd;
  pStkHd=pn;
  return SUCCESS;
}
int popItem(struct student *ps)
{
  struct node *pn;
  if(pStkHd==NULL)
  {
    return STK_EMPTY_ERR;
  }
  pn=pStkHd;
  pStkHd=pStkHd->pnxt;
  *ps=pn->stu;
  free(pn);
  return SUCCESS;
}
void dispAllItems()
{
  struct node *ptmp;
  ptmp=pStkHd;
  while(ptmp)
  {
    printf("    Id   Phone   Name   \n");
    printf(" ------  ------  ------\n");
    printf(" %d     %d     %s\n ",ptmp->stu.id,ptmp->stu.phone,ptmp->stu.name);
    ptmp=ptmp->pnxt;
  }
}


