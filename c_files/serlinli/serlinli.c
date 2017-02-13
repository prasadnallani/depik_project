#include"serach.h"
#include<stdio.h>
struct node
{
  struct record rec;
  struct node *pnxt;
};
struct node *pHead;
int searchRec(int phone,struct record *prec)
{
  struct node *ptmp;
  ptmp=pHead;
  while(ptmp)
  {
    if(ptmp->rec.phone==phone)
    {
      *prec=ptmp->rec;
      return SUCCESS;
    }
    return REC_NOT_FOUND_ERR;
  }
  
  int addRec(const struct record *prec)
  {
    struct node *pn;
    pn=malloc(sizeof(*pn));
    if(pn==NULL)
    {
      return NO_MEMORY_ERR;
      pn->rec=*prec;
      pn->pnxt=pHead;
      pHead=pn;
      return SUCCESS;
    }
  }

int delRec(int phone)
    {
      struct node *ptmp,*delnode;
      if(pHead==0)
      {
	return REC_NOT_FOUND_ERR;
      }
      if(pHead->rec.phone==phone)
      {
	delnode =pHead;
	pHead=pHead->pnxt;
	free(delnode);
	return SUCCESS;
      }
        ptmp=pHead;
	while(ptmp->pnxt)
	{
	  if(ptmp->pnxt->phone ==phone)
	  {
	    delnode=ptmp->pnxt;
	    ptmp->pnxt=ptmp->pnxt->pnxt;
	    free(delnode);
	    return SUCCESS;
	  }
	  ptmp=ptmp->pnxt;
	}
	return REC_NOT_FOUND_ERR;
    }

    void displayAllRecs()
    {
      struct node *ptmp;
      ptmp=pHead;
      while(ptmp)
      {
	printf("Name: %s,phone: %d\n",ptmp->rec.name,ptmp->rec.phone);
	ptmp=ptmp->pnxt;
      }
    }

