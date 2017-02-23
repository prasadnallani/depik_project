/********************************************************************
	         	Operations on files 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>

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
*********************************************************************/
main(void)
{
  char ch,str[20];
  int ii; 
  FILE *fp;

  printf("Enter file name\n");
  scanf("%s", str);
  
  fp = fopen(str, "r+");

  if( fp < 0 )
  {
    printf("unable to open file...\n");
    exit(1);
 }
 ii = 1;  
 while(1)
 {
   if( fread(&ch, 1, 1, fp) != 1)
     break;
   printf("%02x", ch); 
   if(!(ii%16))
    printf("\n");
   ii++;
  }
  printf("\n");
  fclose(fp);
}
    
  
     

