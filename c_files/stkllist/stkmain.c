#include<stdio.h>
#include"stack.h"
void getStudentRec(struct student *ps)
{
  printf("Enter Id: ");
  scanf("%d",&ps->id);
  printf("Enter Phone:");
  scanf("%d",&ps->phone);
  printf("Enter Name :");
  __fpurge(stdin);
  scanf("%[^\n]",&ps->name);
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
     printf("Enter 1.PUSH\n");
     printf("      2.POP\n ");
     printf("      3.DISPLAY ALL\n");
     printf("      4.exit\n ");
     printf("Enter Your Option :");
     scanf("%d",& option);
     switch (option)
    // switch (1)
     {
       case PUSH:
                 getStudentRec(&s);
		 pushItem(&s);
		 break;
       case POP:
              pstmp= popItem(&s);
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
