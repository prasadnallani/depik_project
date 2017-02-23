
/********************************************************************
         	Operations on arrays 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define MAX_ARRAY_SIZE 20
#define SUCESS		0
#define ERR_INDX	1
#define ARRAY_FULL_ERR  2   
#define NO_ELEMENTS     3  
/********* global variables ***********/
int sampArray[MAX_ARRAY_SIZE];
int noOfElements;

/********* function prototypes ***********/
int insertElement(int elm, int indx);
void displayAllElements(void);
int deleteElementAtIndx(int indx);
int linearSearch(int elm);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int insertElement(int elm, int indx)
{
  int tmp;
  
  if(indx > noOfElements)
    return ERR_INDX;

  if(noOfElements >= MAX_ARRAY_SIZE)
    return ARRAY_FULL_ERR;
  else
  {
    tmp = noOfElements;
    while(tmp >= indx)
    {
      sampArray[tmp+1] = sampArray[tmp];
       tmp--;
    }
    sampArray[indx] = elm;
    noOfElements++;
    return SUCESS;
  } 
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void displayAllElements(void)
{
  int ii = 0;

  while(ii < noOfElements)
  {
    printf("ele = %d\n", sampArray[ii]);
    ii++;
  }
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int deleteElementAtIndx(int indx)
{
  if(noOfElements == 0)
     return NO_ELEMENTS;

  if(indx >= noOfElements)
    return ERR_INDX;

  else
  {
    while(indx < noOfElements - 1 )
    {
      sampArray[indx] = sampArray[indx + 1];
      indx++;   
    }
    noOfElements--;
    return SUCESS;
  }
}  
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int linearSearch(int elm)
{
  short ii;

  for(ii = 0; ii<noOfElements; ii++)
  {
    if(sampArray[ii] == elm)
       return ii;
   }
   return -1;
} 
    
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
  int status = 0, elm, indx;
  char ch, ii; 

  printf("Enter no of elements to be entered\n");
  scanf("%d", &noOfElements);

  for(ii = 0; ii<noOfElements; ii++)
    scanf("%d", &sampArray[ii]);

  while(1)
  {
    printf(" operations on arrays\n");
    printf(" 0.Insert an element\n");
    printf(" 1.Delete an element\n");
    printf(" 2.Search an element\n");
    printf(" 3.Display all elements\n");
    printf("4.Exit\n");
    printf("Enter ur choice\n");
    scanf("%d", &ch);

    switch(ch)
    {
       case 0:
             printf("Enter index and element to be inseted \n");
             scanf("%d%d", &indx,&elm);
      	     status = insertElement(elm, indx);
 
  	     if(status == ARRAY_FULL_ERR)
    	       printf("Err:Array full\n");
  	     else if(status ==  ERR_INDX)
    	       printf("Err:index out of range\n");
             else 
                printf("Element inserted\n");
            break;     

	case 1:
      printf("Enter index(0-noOfElements) of element to be deleted \n");
             scanf("%d", &indx);
   	     status = deleteElementAtIndx(indx);

              printf("iam here\n");   
  	     if(status ==  ERR_INDX)
    	       printf("Err:index out of range\n");
  	     else if(status == NO_ELEMENTS)  
    	       printf("Err:No elements in the array\n");
             else 
    	       printf("Element deleted\n");
              break;

	case 2:  
             printf("Enter element to search \n");
             scanf("%d", &elm);

	     status = linearSearch(elm);

             if(status == -1)
               printf("Element not Found\n");
             else 
               printf("Element found, Index of it = %d\n", status);
             break;

	case 3:
    	     displayAllElements();
             break;

        case 4:
	      exit(1);
 	      break;

        default:
	      printf("Invalid entry\n");       
              break;
     }
  }             

}

