
/********************************************************************
	         	Operations binary and ASCII 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/
void dispDecimalInteger(int val);
void reverse(char *str);
/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispDecimalInteger(int val)
{
  int temp;
  char str[10],ii=0;

  while(val)
  {
    temp = val % 10;
    str[ii] = temp + '0';
    val = val/10;
   ii++;
  }
  str[ii] = '\0';
  reverse(str);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void reverse(char *str)
{
  char *cptr,temp;
  short ii,len;
  
  len = strlen(str);
  cptr = str + len - 1;

  //printf("%s\n", str);
  for(ii=0; ii < len/2; ii++)
  {
    
    *(str+ii) ^= *(cptr-ii) ^= *(str+ii) ^= *(cptr-ii);
    
/*
    temp = *(str+ii);
    *(str+ii) = *(cptr-ii);
    *(cptr-ii) = temp;
*/
  }
  *(str + len ) = '\0';
  printf("integer = %s\n", str);
}   
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{ 
  int iVal;

  __fpurge(stdin);
  printf("Enter an unsigned integer\n");
  scanf("%d", &iVal);

  dispDecimalInteger(iVal);
}
