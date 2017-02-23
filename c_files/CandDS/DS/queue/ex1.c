/********************************************************************
         	Operations on circular Queue 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include "cirq.c"  //to access circularQ open this and coment the next
//#include "llq.c" //to access Q with linked lists open this

element_t* getElement(void);
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
  
    printf("\n\n\n1.Add element to Queue\n");
    printf("2.Get element to Queue\n");
    printf("3.Display elements in the Queue\n");
    printf("4.Quit the program\n");

    printf("Eneter ur Choice\n");
    __fpurge(stdin);
    ch = getchar();
   
    switch(ch - '0')
    {
	case 1:
                Elm = getElement();
		status = addElementToQ(Elm);

                if(status == SUCESS)
		  printf("Element added sucessfully\n");
      		else
		  printf("Queue is full\n");
		break;
	case 2:
		status = getElementFromQ(Elm);

                if(status == SUCESS)
 		{
		  printf("Element\n");
		  printf("empNo = %d\n", Elm->empNo);
		  printf("salary = %d\n", Elm->salary);
		}  
      		else
		  printf("Queue under flow\n");
		break;

	case 3:
		 displayQueue();
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
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
element_t* getElement(void)
{
  element_t *elm;

  printf("Enter employee No\n");
  scanf("%d", &elm->empNo);
  printf("Enter employee salary\n");
  scanf("%d", &elm->salary);

   return elm;
}
