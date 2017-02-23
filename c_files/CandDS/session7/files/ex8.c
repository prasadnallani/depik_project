
/********************************************************************
	         	Operations on files 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

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
  int ii, rP[10];

  FILE *fp;
  fp = fopen("binfile", "r");
  
  if( fp < 0)
  {
     printf("file not opned");
     exit(1);
  }
  
  fread(rP, 4, 10, fp);

  for(ii = 0; ii < 10; ii++)
     printf("%d", *(rP+ii));

  printf("\n");
  fclose(fp);
 
  fp = fopen("textfile", "r");
  
  if( fp < 0)
  {
     printf("file not opned");
     exit(1);
  }
  
  fread(rP, 4, 10, fp);

  for(ii = 0; ii < 10; ii++)
     printf("%d", *(rP+ii)-'0');
  printf("\n");

  fclose(fp);

}
  
