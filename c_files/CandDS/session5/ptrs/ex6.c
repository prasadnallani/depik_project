
/********************************************************************
	         	Operations on Pointers 
*********************************************************************/

/********* Header files *********/
/************ macros ************/
/********* global variables ***********/
/********* function prototypes ***********/
void dispBytes(unsigned char *pB, int count);
void dispWords(unsigned short *pW, int count);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : void dispBytes(unsigned char *pB, int count)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void dispBytes(unsigned char *pB, int count)
{
  while(count)
  {
    printf("%x ", *pB);
    pB++;
    count--;
    if(!(count % 16))    
       printf("\n");
   }
 }
/***********************************************************************
* Name 	      : void dispWords(unsigned short *pW, int count)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void dispWords(unsigned short *pW, int count)
{
  while(count)
  {
    printf("%x ", *pW);
    pW++;
    count--;
    if(!(count % 8))    
       printf("\n");
   }
 }

/***********************************************************************
* Name 	      : void dispLongs(unsigned int *pL, int count)
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void dispLongs(unsigned int *pL, int count)
{
  while(count)
  {
    printf("%x ", *pL);
    pL++;
    count--;
    if(!(count % 4))    
       printf("\n");
   }
 }
/***********************************************************************
* Name 	      : main(void) 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 char cArr[128];
 short ii;

 for(ii = 0; ii<128; ii++)
   cArr[ii] = ii;


 printf("\nBytes\n");
 dispBytes(cArr,128);
 printf("\nwords\n");
 dispWords(cArr,64);
 printf("\nLongs\n");
 dispLongs(cArr,32);
}

 
 
