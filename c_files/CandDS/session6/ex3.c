
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
  unsigned char *cPtr, ii;

  st.intValue1 = 0x1234;
  st.shValue = 0x56;
  st.intValue2 = 0x789a;
  st.chValue = 0xbc;
  st.intValue3 = 0xfedcba98;

  printf("size of the structure variable  = %d\n", sizeof(st));
  printf("addr of the structure variable  = %d\n", &st);

  pSt = &st;

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
