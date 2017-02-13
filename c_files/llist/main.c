#include<stdio.h>
#include"hdr.h"
//extern int noOfRecords;

void readRec(struct phoneRec *pr)
{
  printf("Enter Name      :");
 __fpurge(stdin);
  scanf("%[^\n]",pr->name);

  printf("Enter Address   :");
 __fpurge(stdin);
  scanf("%[^\n]",pr->addrs);
  printf("Enter Phone number:  ");
  scanf("%d",&pr->phoneNo);
}

int main()
{
  struct phoneRec r;
  int option;
  int phNo;
  while(1)
  {
    printf("\n ENTER 1:ADDTOEND  2.ADDTOBEGIN,  3.DELETE  4.GET\n");
    printf("       5.INSERT    6.DISPLAY ALL  7.EXIT\n");
    printf("Now enter your option   :");
    scanf("%d",&option);
    printf("\n");
    switch(option)
    {
      case ADD_TO_END:
           readRec(&r);
	   addRecToEnd(&r);
	   break;
      case ADD_TO_START:
	   readRec(&r);
	   addRecToStart(&r);
	   break;
      case DELETE:
	   printf("Enter phone number: ");
	   scanf("%d",&phNo);
	   deleteRec(phNo);
	   break;
      case GET:
	   printf("Enter phone number : ");
	   scanf("%d",&phNo);
	   if(getPhoneRec(phNo,&r)==SUCCESS)
	   {
	     
	     printf("phone: %d, Name: %s, Address :%s\n");
	   }
	   else
	     printf("phone number not found\n");
	     break;
	 
     case INSERT:
	     readRec(&r);
	     insertRec(&r);
	     break;
     case DISPLAY_ALL:
	     displayAllRecs();
	     break;
     case EXIT:
	     return 0;
	   }
    }
 
  }


  
  
