#include"search.h"

static struct record bArray[MAX_RECORDS];
static int  rCnt;

int searchRec(int phone,struct record *prec)
{
  int ii;
  for(ii=0;ii<rCnt;ii++)
  {
    if(bArray[ii].phone==phone)
    {
      *prec=bArray[ii];
      return SUCCESS;
    }
  }
  return REC_NOT_FOUND_ERR;
}
/*
   * Record is added at the end
   */
int addRec(const struct record *prec)
{
  if(rCnt==MAX_RECORDS)
    return OVERFLOW_ERR;
  bArray[rCnt++]=*prec;
  return SUCCESS;
}

int delRec(int phone)
{
  int ii,jj;
  for(ii=0;ii<rCnt;ii++)
  {
    if(bArray[ii].phone==phone)
    {
      for(jj=ii+1;jj=rCnt;jj++)
	bArray[jj-1]=bArray[jj];
      rCnt--;
      return SUCCESS;
    }
  }
  return REC_NOT_FOUND_ERR;
}

void displayAllRecs()
{
  int ii;
  for(ii=0;ii<rCnt;ii++)
  {
    printf("Name: %s,phone: %d\n",bArray[ii].name,bArray[ii].phone);
    
  }
}

