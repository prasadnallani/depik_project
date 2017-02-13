#include<stdio.h>
#include"queue.h"

void getStudentRec(struct student *ps)
{
  printf("Enter Id: ");
  scanf("%d",&ps->id);
  printf("Enter Phone:");
  scanf("%d",&ps->phone);
  printf("Enter Name :");
  __fpurge(stdin);
  scanf("%[^\n]",ps->name);
}
void dispStuInfo(struct student *ps)
{
 // printf("Id=%d\n",ps->id);
 // printf("Phone=%d",ps->phone);
 // printf("Name =%s\n",ps->name);
  
} 
struct student s,*pstmp;
int option;


int main()
{
  // struct student s,*pstmp;
  // int option;
   while(1)
   {
     printf("Enter 1.ENTER DATA\n");
     printf("      2.DEL DATA\n ");
     printf("      3.DISPLAY ALL\n");
     printf("      4.EXIT\n ");
     printf("Enter Your Option :");
     scanf("%d",&option);
     switch (option)
    
     {
       case ENTER:
                 getStudentRec(&s);
		 enqItem(&s);
		 break;
       case DELETE:
              pstmp=(struct student *) deqItem(&s);
	      dispStuInfo(&pstmp);
	      break;
       case DISPALL:
	      dispAllItems();
	      break;
       case EXIT:
	      return 0;
     }
   }
}
