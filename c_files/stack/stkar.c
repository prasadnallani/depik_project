#include<stdio.h>
#include"stack.h"

static struct student stkArray[MAX_STK_SIZE];
static int stktop,ii;

int pushItem(const struct student *ps)
{
  if(stktop==MAX_STK_SIZE)
  {
    return STK_FULL_ERR;
  }
  stkArray[stktop++]=*ps;
  return SUCCESS;
}

int popItem(struct student *ps)
{
  if(stktop==0)
  {
    return STK_EMPTY_ERR;
  }
  *ps=stkArray[--stktop];
  return SUCCESS;
}

void dispAllItems()
{
  for(ii=0;ii<stktop;ii++)
    printf("Id: %d,Name: %s, phone:%d\n",stkArray[ii].id,stkArray[ii].name,stkArray[ii].phone);
}
  
