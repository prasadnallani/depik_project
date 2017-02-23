
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
int insertElmSorted(int elm);
void displayAllElements(void);
int binarySearch(int elm);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
int insertElmSorted(int elm)
{
  int tmp, indx = 0;
   
  if(noOfElements >= MAX_ARRAY_SIZE)
    return ARRAY_FULL_ERR;
  else
  {
    tmp = noOfElements - 1;
    while(noOfElements >= indx)
    {
      if(sampArray[indx] >= elm)
      { 
    	 while(tmp >= indx)
         {
           sampArray[tmp+1] = sampArray[tmp];
           tmp--;
          }
          sampArray[indx] = elm;
          noOfElements++;
          return SUCESS;
       } 
       indx++;
     }
     sampArray[noOfElements] = elm;
     noOfElements++;
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
int binarySearch(int elm)
{
  int first = 0, last = noOfElements, mid = 0;
  
  while(first <= last)
  {
    mid = (first+last)/2;

    if(sampArray[mid] == elm) 
        return mid;
    else if(sampArray[mid] > elm)
	last = mid - 1;
    else
	first = mid + 1;
   }
   return -1;
}
/*
  int tmp = 0;
  if(sampArray[tmp] == elm)
    return tmp;
  if(noOfElements%2)
    if(sampArray[noOfElements - 1] == elm)
       return noOfElements-1;

  tmp++;
  while( (tmp < noOfElements) && (tmp > 0) )
  { 
    if(sampArray[tmp] > elm)
	tmp = tmp/2;
    else if(sampArray[tmp] < elm)
	tmp = tmp+noOfElements/2;
    else 
         return tmp;  
   }  
   return -1;
} 
*/    
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

  printf("Enter no of elements to be stored\n");
  scanf("%d", &noOfElements);

  printf("Enter %d elements \n", noOfElements);
  for(ii = 0; ii<noOfElements; ii++)
    scanf("%d", &sampArray[ii]);

  while(1)
  {
    printf(" operations on arrays\n");
    printf(" 0.Insert an element in sorted array\n");
    printf(" 1.Binary Search an element(pending)\n");
    printf(" 2.Display all elements\n");
    printf(" 3.Exit\n");
    printf("Enter ur choice\n");
    scanf("%d", &ch);

    switch(ch)
    {
       case 0:
             printf("Enter element to be inseted \n");
             scanf("%d",&elm);
      	     status = insertElmSorted(elm);
 
  	     if(status == ARRAY_FULL_ERR)
    	       printf("Err:Array full\n");
             else 
                printf("Element inserted\n");
            break;     

	case 1:  
             printf("Enter element to search \n");
             scanf("%d", &elm);

	     status = binarySearch(elm);

             if(status == -1)
               printf("Element not Found\n");
             else 
               printf("Element found, Index of it = %d\n", status);
            break;


	case 2:
    	     displayAllElements();
             break;

        case 3:
	      exit(1);
 	      break;

        default:
	      printf("Invalid entry\n");       
              break;
     }
  }             

}

