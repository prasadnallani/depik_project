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
  unsigned int val, temp=0;
  int ii, flag=0;
  
  printf("Enter an unsingned integer in Hex format\n");
  scanf("%x",&val);

  for(ii = 32; ii > 0; ii--)
  {  
     temp = val >> (ii - 1);
     temp &= 0x1;
     if(!flag)
     {
       if(temp)
         flag = 1;
     }
    if(flag)
      printf("%x",temp);
   } 	
/******* simple logic to print a int in binary form (all bits)******* 
   for(ii=32; ii>0; ii--)
   {
     printf("%d", ( val & 0x80000000 ) ? 1 : 0 );
     val <<= 1;  
   }
*********************************************************************/
  printf("\n");
 } 
