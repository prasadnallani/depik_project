
/********************************************************************
         	Operations on stack 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
//#include "arstk.c" //to access array stack open this and coment the next
#include "llstk.c" //to access linked list stack open this and coment the next

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
element_t* getElement()
{
  element_t *elm;

  printf("Enter employee No\n");
  scanf("%d", &elm->empNo);
  printf("Enter employee salary\n");
  scanf("%d", &elm->salary);

   return elm;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
  char ch;
  int status;
  element_t *Elm;

  while(1)
  {
  
    printf("\n\n\n1.Push element to Stack\n");
    printf("2.Pop element from stack\n");
    printf("3.Display all elements in the Stack\n");
    printf("4.Quit the program\n");

    printf("Eneter ur Choice\n");
    __fpurge(stdin);
    ch = getchar();
   
    switch(ch - '0')
    {
	case 1:
                Elm = getElement();
		status = pushElementToStack(Elm);

                if(status == 0)
		  printf("Element pushed sucessfully\n");
      		else
		  printf("stack is overflow\n");
		break;
	case 2:
		status = popElementFromStack(Elm);

                if(status == 0)
 		{
		  printf("Element\n");
		  printf("empNo = %d\n", Elm->empNo);
		  printf("salary = %d\n", Elm->salary);
		}  
      		else
		  printf("Stack under flow\n");
		break;

	case 3:
		 displayStack();
		 break;
	case 4:
		exit(1);
		break;
	default:
		printf("Invalid Choice Entered\n");
		break;
     }
  } 
}
   
