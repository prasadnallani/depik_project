#include<stdio.h>
#include"hdr.h"
struct node
{
  struct phoneRec r;
  struct node     *pnxt;
};
static struct node *pHead;
static struct node *pTail;

int addRecToEnd(const struct phoneRec *pr)
{
  struct node *pn;
  pn=malloc(sizeof(*pn));
  pn->r=*pr;
  if(pTail)
  {
    pTail->pnxt=pn;
    pn->pnxt=NULL;
    pTail=pn;
  }
  else
  {
    pHead=pn;
    pTail=pn;
    pn->pnxt=NULL;
  }
  return SUCCESS;
 }

int addRecToStart(const struct phoneRec *pr)
{
  struct node *pn;
  pn=malloc(sizeof(*pn));
  pn->r=*pr;
  if(pHead)
  {
    pn->pnxt=pHead;
    pHead   =pn;
  }
  else
  {
    pHead=pn;
    pTail=pn;
    pn->pnxt=NULL;
  }
  return SUCCESS;
}

int deleteRec(int phNo)
{
  struct node *ptmp,*pdel;
  if(pHead==NULL)
  {
    return PH_NUM_NOT_FOUND_ERR;
  }
  if(pHead->r.phoneNo==phNo)
  {
    pdel=pHead;
    pHead=pHead->pnxt;
    free(pdel);
    if(pHead==NULL)
      pTail=NULL;
    return SUCCESS;
  }
  ptmp=pHead;
  while(ptmp->pnxt)
  {
    if(ptmp->pnxt->r.phoneNo==phNo)
    {
      pdel=ptmp->pnxt;
      ptmp->pnxt=ptmp->pnxt->pnxt;
      if(pdel==pTail)
	pTail=ptmp;
      free(pdel);
      return SUCCESS;
    }
    ptmp=ptmp->pnxt;
  }
  return PH_NUM_NOT_FOUND_ERR;
}

int insertRec(const struct phoneRec *pr)
{
  struct node *pn,*ptmp;
  pn=malloc(sizeof(*pn));
  pn->r=*pr;
  if(pHead==0)
  {
    pn->pnxt=0;
    pHead=pn;
    pTail=pn;
    return SUCCESS;
   }
  if(pHead->r.phoneNo > pn->r.phoneNo)
  {
    pn->pnxt=pHead;
    pHead=pn;
    return SUCCESS;
  }
  ptmp=pHead;
  while(ptmp->pnxt)
  {
    if(ptmp->pnxt->r.phoneNo > pn->r.phoneNo)
    {
      pn->pnxt=ptmp->pnxt;
      ptmp->pnxt=pn;
      pn->pnxt=0;
      pTail=pn;
      return SUCCESS;
     }
  }
}

int getPhoneRec(int phNo,struct phoneRec *pr)
{
   struct node *ptmp;
   if(pHead==NULL)
   {
     return PH_NUM_NOT_FOUND_ERR;
   }
   ptmp=pHead;
   while(ptmp)
   {
     if(ptmp->r.phoneNo==phNo)
     {
       *pr=ptmp->r;
       return SUCCESS;
     }
      ptmp=ptmp->pnxt;
   }
   return PH_NUM_NOT_FOUND_ERR;

}
void displayAllRecs()
{
  struct node *ptmp;
  if(pHead==NULL)
  {
    printf("No records\n");
  }
  ptmp=pHead;
  printf("Name         Phone      Address\n");
  printf("--------    --------   -------------\n");
  while(ptmp)
  {
    printf("%12s       %8d    %s \n",ptmp->r.name,ptmp->r.phoneNo,
	                               ptmp->r.addrs);
    ptmp=ptmp->pnxt;
  }
}
  
  

