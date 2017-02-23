
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


/********* function prototypes ***********/
void getStruct(sampStruct_t *pSt);
void DispStruct(sampStruct_t st);
void DispStrctWithPtr(sampStruct_t *pSt);

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
  sampStruct_t st, *pSt;

 pSt = &st;

 getStruct(pSt);
 DispStruct(st);
 DispStrctWithPtr(pSt);
 
}
/***********************************************************************
* Name 	      : void getStruct(sampStruct_t *pSt)
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void getStruct(sampStruct_t *pSt)
{
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

}
/***********************************************************************
* Name 	      : void DispStrctWithPtr(sampStruct_t *pSt)
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void DispStrctWithPtr(sampStruct_t *pSt)
{
  printf("****** struct info ******** \n");
  printf("intValue1 :%x\n", pSt->intValue1);
  printf("shValue : %x\n", pSt->shValue);
  printf("intValue2 : %x\n", pSt->intValue2);
  printf("chValue : %x\n", pSt->chValue);
  printf("intValue3 : %x\n", pSt->intValue3);
}
/***********************************************************************
* Name 	      : void DispStruct(sampStruct_t st)
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void DispStruct(sampStruct_t st)
{
  printf("****** struct info ******** \n");
  printf("intValue1 :%x\n", st.intValue1);
  printf("shValue : %x\n", st.shValue);
  printf("intValue2 : %x\n", st.intValue2);
  printf("chValue : %x\n", st.chValue);
  printf("intValue3 : %x\n", st.intValue3);
}
