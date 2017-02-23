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
  unsigned int val, bitNum, bVal, maskVal= 0x1;
  int ii;
  
  printf("Enter an unsingned integer in Hex format\n");
  scanf("%x",&val);
  
  printf("Enter a bit number\n");
  scanf("%d", &bitNum);

  printf("Enter a bit Value(0 or 1)\n");
  scanf("%d", &bVal);
  
  maskVal = ~(maskVal << bitNum);
  val = val & maskVal;
  val = val |(bVal << bitNum);

  printf("value = %x\n", val);
}  
