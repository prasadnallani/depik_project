/********************************************************************
	         	Operations Bits 
*********************************************************************/

/********* Header files *********/
/************ macros ************/
#define LOGICAL 0
#define BITWISE 1
#define AND	0
#define OR	1
#define NOT	2
#define XOR	3
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
  unsigned int lOperation, operation, val1, val2, result=0;
  int ii, flag=0;
 while(1)
{ 
  printf("******Select a logical operation*****\n");
  printf("0.Logical operation\n");
  printf("1.Bitwise operation\n");
  printf("2.Exit\n");
  scanf("%d", &lOperation);

  if(lOperation == 2)
       exit(1);
  printf("Select a operation\n");
  printf("0.AND operation\n");
  printf("1.OR operation\n");
  printf("2.NOT operation\n");

  if(lOperation == 1)
    printf("3.XOR operation\n");
  scanf("%d", &operation);
  
  printf("Enter an unsigned integer in hex format\n");
  scanf("%x", &val1);

  if(operation != NOT)
  {
    printf("Enter another unsigned integer in hex format\n");
    scanf("%x", &val2);
  }

  if(lOperation == 1)
  {
    switch(operation)
    {
   	case AND:
	       result = val1 & val2;	
	       break;
   	case OR:
	       result = val1 | val2;	
	       break;
   	case NOT:
	       result = ~val1;	
	       break;
   	case XOR:
	       result = val1 ^ val2;	
	       break;
  	default:
		printf("operation selected is invalid\n");
	       break;
    }	
     printf("Result = %x\n",result);
  } 	
  else if(lOperation == 0)
  {
    switch(operation)
    {
	
   	case AND:
	       result = val1 && val2;	
	       break;
   	case OR:
	       result = val1 || val2;	
	       break;
   	case NOT:
	       result = !val1;	
	       break;
  	default:
	       printf("operation selected is invalid\n");
	       break;
     }
     printf("Result = %x\n",result);
    }
    else
	printf("Logical operation selected is invalid\n");
  }	
 } 
