/*******Queue implementaion using array********/
#include"queue.h"
#include<stdio.h>
struct student queArray[MAX_Q_SIZE];
int     noOfItems;

int  enqItem(const struct student *ps)
{
  int stat;
  if(noOfItems == MAX_Q_SIZE)
  return QUEUE_FULL_ERR;
  queArray[noOfItems++]=*ps;
  return SUCCESS;
}
int deqItem(struct student *ps)
{
  int ii;
  if(noOfItems==0)
    return QUEUE_EMPTY_ERR;
  *ps=queArray[0];
  for(ii=1;ii<noOfItems;ii++)
    queArray[ii-1]=queArray[ii];
  noOfItems--;
  return SUCCESS;
}
void dispAllItems()
{  int ii;
  printf("display all items:\n");
  for(ii=0;ii<noOfItems;ii++)
    printf("Id: %d,Name: %s, phone:%d\n",queArray[ii].id,queArray[ii].name,queArray[ii].phone);
}


