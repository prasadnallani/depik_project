/********************************************************************
			Inter Process Communication
**********************************************************************/

/********* Header Files *********/
#include<sys/types.h>

/*********Global Variables*******/
/********* Function prototypes *****/

/**********************************************************************
* Name	      : main(void)
* Description :
* Inputs      : none 
* outputs     : none
*********************************************************************/
main(void)
{
  char ch;

  ch= getchar();

  if(ch >= 'a' && ch <= 'z')
    ch -= 32;
  else if(ch >= 'A' && ch <= 'Z')
    ch += 32;
  putchar(ch);
  printf("\n");
}


    
