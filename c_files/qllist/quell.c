#include"queue.h"
#include<stdio.h>
/****Queue implementation using linked list***/
struct node
{
  struct student stu;
  struct node *pnxt;
};
struct node *pQueHd;
struct node *pQueTl;
int enqItem(const struct student *ps)
{
  struct node *pn;
  pn=malloc(sizeof(*pn));
  pn->stu=*ps;
  if(pQueTl==0)
    pQueTl=pQueHd=pn;
  else
  {
    pQueTl->pnxt=pn;
    pQueTl=pn;
  }
  pn->pnxt=0;
  return SUCCESS;
}

int deqItem(struct student *ps)
{
  struct node *pn;
  if(pQueHd==0)
  {
    return QUEUE_EMPTY_ERR;
    pn=pQueHd;
    pQueHd==pQueHd->pnxt;
    if(pQueHd==0)
      pQueTl=0;
    *ps=pn->stu;
    free(pn);
    return SUCCESS;
  }
}

void dispAllItems()
{
  struct node *ptmp;
  ptmp=pQueHd;
  while(ptmp)
  {
    printf("Id=%d  phone=%d  Name=%s\n",ptmp->stu.id,ptmp->stu.phone,ptmp->stu.name);
     ptmp=ptmp->pnxt;
  }
}


    
