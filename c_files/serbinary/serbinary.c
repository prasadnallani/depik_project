#include"search.h"

static struct record bArray[MAX_RECORDS];
static int  rCnt;

int searchRec(int phone,struct record *prec)
{
  int start,mid,end;
  start=0;
  end =rCnt -1;
  while(start<= end)
  {
    mid=(start+end) /2;
    if(bArray[mid].phone == phone)
    {
      *prec=bArray[mid];
      return SUCCESS;
    }
    if(bArray[mid].phone > phone)
    {
      end =mid-1;
    }
    else
    {
      start =mid+1;
    }
  }
  return REC_NOT_FOUND_ERR;
}
/*
   *Record is inserted at the right place based on phone number */
int addRec(const struct record *prec)
{
  int ii,jj;
  if(rCnt == MAX_RECORDS)
    return OVERFLOW_ERR;
  for(ii=0;ii<rCnt;ii++)
  {
    if(bArray[ii].phone > prec->phone)
    {
      for(jj=rCnt-1;jj>=ii;jj--)
	bArray[jj+1]=bArray[jj];
      bArray[ii]=*prec;
      rCnt++;
      return SUCCESS;
    }
  }
  bArray[rCnt++]=*prec;
  return SUCCESS;
}
int delRec(int phone)
{
  int ii,jj;
  for(ii=0;ii<rCnt;ii++)
  {
    if(bArray[ii].phone == phone)
    {
      for(jj=ii+1;jj<rCnt;jj++)
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
    printf("Name:  %s,phone:  %d\n",bArray[ii].name,bArray[ii].phone);
  }
}


 
