#include<stdio.h>
#include"queue.h"

/*****Queue implementaion using Linked list****/
struct student cirQArray[MAX_CQ_SIZE];
int headIx;
int tailIx;
int noOfItems;

int enqItem(const struct student *ps)
{
  int stat;
  if(noOfItems==MAX_CQ_SIZE)
    return  CIRQ_FULL_ERR;
  cirQArray[tailIx]=*ps;
  tailIx=(tailIx+1) % MAX_CQ_SIZE;
  noOfItems++;
  return SUCCESS;
}

int deqItem(struct student *ps)
{
  if(noOfItems==0)
  return CIRQ_EMPTY_ERR;
  *ps=cirQArray[headIx];
  headIx=(headIx+1) % MAX_CQ_SIZE;
  noOfItems--;
  return SUCCESS;
}
void dispAllItems()
{  int ii;
  printf("display all items:\n");
  for(ii=0;ii<noOfItems;ii++)
    printf("Id: %d,Name: %s, phone:%d\n",cirQArray[ii].id,cirQArray[ii].name,cirQArray[ii].phone);
}


