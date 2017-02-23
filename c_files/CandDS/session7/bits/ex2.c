
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
  unsigned int val, bitNum, noOfBits, maskVal= 0x0, exVal;
  int ii;
  
  printf("Enter an unsingned integer in Hex format\n");
  scanf("%x",&val);
  
  printf("Enter no of bits to be extracted\n");
  scanf("%d", &noOfBits);

  printf("Enter starting bit number\n");
  scanf("%d", &bitNum);
  
  for(ii = 0; ii< noOfBits; ii++)
  {
    if(ii)
      maskVal = maskVal << 1;

    maskVal = maskVal | 0x00000001;
  }
  val = val >> bitNum;
  exVal = val & maskVal;
  printf("value = %x\n", exVal);
}  
 
