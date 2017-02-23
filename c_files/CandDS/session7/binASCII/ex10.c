
/********************************************************************
	         	Operations binary and ASCII 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/
void dispGivenAsciiChars(char strtChr, char endChr);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispGivenAsciiChars(char strtChr, char endChr)
{
  char ii;
  __fpurge(stdout);

  for(ii = strtChr; ii < endChr; ii++)
  {
    putchar(ii);
    if(!(ii%16))
       printf("\n");
  }
  printf("\n");
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{ 
  char sChar, eChar;

  printf("Enter starting character\n");
  scanf("%d", &sChar);

  printf("Enter ending character\n");
  scanf("%d", &eChar);

  //if((sChar < 32) || ( eChar > 126))
   //  printf("Given range out of printable chars\n");

  dispGivenAsciiChars(sChar, eChar);
}
