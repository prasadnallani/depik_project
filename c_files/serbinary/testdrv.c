#include"search.h"
#include<stdio.h>
int main()
{
  struct record rec;
  int option,stat,phone;

  while(1)
  {
    printf("Enter 1.To search and get\n");
    printf("      2.Add to Record    \n");
    printf("      3.Delete a Record   \n");
    printf("      4.Display all records\n");
    printf("      5.Exit             \n");
    scanf("%d",&option);
    switch(option)
    {
      case SER:
	printf("Enter the phone number to search \n");
	scanf("%d",&phone);
	stat=searchRec(phone,&rec);
	if(stat == SUCCESS)
	  printf("Name :%s ,phone:%d\n",rec.name,rec.phone);
	else
	  printf("search failed with error %d\n",stat);
	break;
	
      case ADD:
	printf("Enter phone number to add\n");
	scanf("%d",&rec.phone);
	__fpurge(stdin);
	printf("enter name:\n");
	scanf("%[^\n]",rec.name);
	stat=addRec(&rec);
	if(stat == SUCCESS)
	  printf("Record added successfully\n");
	else
	  printf("Record addition failed with error %d\n",stat);
	break;
	
      case  DEL:
          printf("Enter phone number to delete \n");
	  scanf("%d",&phone);
	  stat=delRec(phone);
	  if(stat==SUCCESS)
	    printf("Record deleted successfully\n");
	  else
	    printf("Record deletion failed with error %d\n",stat);
	  break;
	  
      case DISP:
	  displayAllRecs();
	  break;
	  
      case XIT:
	  return;
	  break;
    }
  }
}

