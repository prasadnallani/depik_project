#include<stdio.h>
#include"hdr.h"

struct phoneRec phRecords[MAX_RECORDS];
 int noOfRecords;

int addRecToEnd(const struct phoneRec *pr)
{
  if(noOfRecords==MAX_RECORDS)
    printf("ARRAY OVERFLOW\n");
    return ARRAY_OVERFLOW_ERR;
  phRecords[noOfRecords++]=*pr;
  return SUCCESS;
}
int addRecToStart( const struct phoneRec *pr)
{
  int ii;
  if(noOfRecords==MAX_RECORDS)
  {
    printf("ARRAY_OVERFLOW_ERR\n");
    return ARRAY_OVERFLOW_ERR;
  }

  for(ii=noOfRecords-1;ii>=0;ii--)
      phRecords[ii+1]=phRecords[ii];

  phRecords[0]=*pr;
  noOfRecords++;
  return SUCCESS;
}
int deleteRec(int phNo)
{
  int ii,jj;
  for(ii=0;ii<=noOfRecords;ii++)
  {
    if(phRecords[ii].phoneNo==phNo)
    {
      for(jj=ii+1;jj<noOfRecords;jj++)
	phRecords[jj-1]=phRecords[jj];
      noOfRecords--;
      return SUCCESS;
    }
  }
  return PH_NUM_NOT_FOUND_ERR;
}

int insertRec(const struct phoneRec *pr)
{
  int ii,jj;
  if(noOfRecords==MAX_RECORDS)
      return ARRAY_OVERFLOW_ERR;
  for(ii=0;ii<=noOfRecords;ii++)
  {
    if(phRecords[ii].phoneNo>pr->phoneNo)
    {
      for(jj=noOfRecords-1;jj>=ii;jj--)
	phRecords[ii]=*pr;
      noOfRecords++;
      return SUCCESS;
    }
  }
  phRecords[noOfRecords++]=*pr;
  return SUCCESS;
}

int getPhoneRec(int phNo,struct phoneRec *pr)
{
  int ii;
  for(ii=0;ii<noOfRecords;ii++)
    {
      if(phRecords[ii].phoneNo==phNo)
      {
	*pr=phRecords[ii];
	return SUCCESS;
      }
    }
  return PH_NUM_NOT_FOUND_ERR;
}

void displayAllRecs()
{
  int ii;
  if(noOfRecords==0)
  {
    printf("No records present\n");
    return;
   }
  printf("Name           phone            address\n");
  printf("--------       --------       ---------------------\n");
  for(ii=0;ii<noOfRecords;ii++)
  {
    printf("%12s        %8d      %s \n" ,phRecords[ii].name,
	                                phRecords[ii].phoneNo,
					phRecords[ii].addrs);
  }
  printf("\n");
}

