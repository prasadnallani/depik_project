/********************************************************************
	         	Operations binary and ASCII 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/
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
void reverse(char *str)
{
  char *cptr,temp;
  short ii,len;
  
  len = strlen(str);
  cptr = str + len - 1;

  printf("%s\n", str);
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
  printf("%s\n", str);
}   
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{ 
  char str[1000];

  __fpurge(stdin);
  fgets(str, sizeof(str), stdin);

  reverse(str);
}
