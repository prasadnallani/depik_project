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
  int ii, *iP, rP[10];
  FILE *fp;
 
  if( (iP = (int *) (malloc(10 * sizeof (int)))) == NULL)
  { 
    printf("memory not allocated for 10 integers\n");
    exit(1);
  }
  printf(" Enter 10 integers\n");

  for(ii = 0; ii < 10; ii++)
  {
    scanf("%d", (iP + ii));
  } 

  fp = fopen("textfile", "w");
  
  if( fp < 0)
  {
     printf("file not opned");
     exit(1);
  }
  for(ii = 0; ii < 10; ii++)
     *(iP+ ii) += '0';

  fwrite(iP, 4, 10, fp);
    
  fclose(fp);


  fp = fopen("binfile", "w");
  
  if( fp < 0)
  {
     printf("file not opned");
     exit(1);
  }
  for(ii = 0; ii < 10; ii++)
     *(iP+ ii) -= '0';

  fwrite(iP, 4, 10, fp);

  fclose(fp);
  
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
  

  
 

