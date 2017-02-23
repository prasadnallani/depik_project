
/********************************************************************
	         	Operations on Unions 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>


/************ macros ************/

/********* global variables ***********/
typedef union sampUnion_s
{

  unsigned char carray[4];
  unsigned short shValue;
  unsigned char chValue;
  unsigned int intValue3;

}sampUnion_t;

sampUnion_t un;


/********* function prototypes ***********/

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      :main() 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
 printf("size of union = %d\n", sizeof(un));
 printf("addr of union = %x\n", &un);

 printf("addr of carray = %x\n", &(un.carray));
 printf("addr of shValue = %x\n", &(un.shValue));
 printf("addr of chValue = %x\n", &(un.chValue));
 printf("addr of int = %x\n", &(un.intValue3));

}
