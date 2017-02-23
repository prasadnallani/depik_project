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
  unsigned int val, startBitNum, noOfBits, bitFieldVal, maskVal= 0x0;
  int ii;
  
  printf("Enter an unsingned integer in Hex format\n");
  scanf("%x",&val);
  
  printf("Enter a start bit number\n");
  scanf("%d", &startBitNum);

  printf("Enter no of bits\n");
  scanf("%d", &noOfBits);

  printf("Enter bit Field Value\n");
  scanf("%x", &bitFieldVal);

  /**** getting mask val at run time******/
  for(ii=0; ii<noOfBits; ii++)
  {
    if(ii)
      maskVal <<= 1;  
    maskVal |= 0x1;	
  }
/*  simple way of doing it ********

  //printf("mvalue = %x\n", maskVal);

  maskVal = ~(maskVal << startBitNum);

  //printf("mvalue = %x\n", maskVal);

  val &= maskVal;

  //printf("val = %x\n", val);

  bitFieldVal <<= startBitNum;

  //printf("bfvalue = %x\n", bitFieldVal);

  val |= bitFieldVal;
*/
/******   Better way of doing it *******
  val &= ( ~(maskVal << startBitNum) );
  val |= (bitFieldVal << startBitNum);
*/
 /******** Best way of doing it ********/
val = (bitFieldVal << startBitNum) | (val & (~(maskVal << startBitNum)));
  printf("value = %x\n", val);
}  
