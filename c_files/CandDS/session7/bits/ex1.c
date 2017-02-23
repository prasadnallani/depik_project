/********************************************************************
	         	Operations Bits 
*********************************************************************/

/********* Header files *********/
/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
  unsigned int val, bitNum, bit;
  
  printf("Enter an unsingne integer in Hex format\n");
  scanf("%x",&val);
  
  printf("Enter a bit number\n");
  scanf("%d", &bitNum);
  
  val = val >> bitNum;
  bit = val & 0x1;
  printf("bit = %x\n", bit);
}  
 

