/********************************************************************
	         	Operations on Structures 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>


/************ macros ************/

/********* global variables ***********/
typedef struct sampStruct
{

  unsigned int intValue1;
  unsigned short shValue;
  unsigned int intValue2;
  unsigned char chValue;
  unsigned int intValue3;

}sampStruct_t;

sampStruct_t st, *pSt;

/********* function prototypes ***********/
void dispStruct(sampStruct_t *pSt);

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
  pSt = (sampStruct_t *)malloc(sizeof(sampStruct_t));
  printf("Enter \n");
  printf("intValue1 : ");
  scanf("%x", &(pSt->intValue1));
  printf("shValue : ");
  scanf("%x", &(pSt->shValue));
  printf("intValue2 : ");
  scanf("%x", &(pSt->intValue2));
  printf("chValue : ");
  scanf("%x", &(pSt->chValue));
  printf("intValue3 : ");
  scanf("%x", &(pSt->intValue3));

  dispStruct(pSt);
  
}

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispStruct(sampStruct_t *pSt)
{
  printf("intValue1 = %x\n", pSt->intValue1);
  printf("shValue = %x\n", pSt->shValue);
  printf("intValue2 = %x\n", pSt->intValue2);
  printf("chValue = %x\n", pSt->chValue);
  printf("intValue3 = %x\n", pSt->intValue3);
}
