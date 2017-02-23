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
  char str[20];
  char buff[16];
  int ii, iLen, offset = 0; 
  FILE *fp;

  printf("Enter file name\n");
  scanf("%s", str);
  
  fp = fopen(str, "r+");

  if( fp < 0 )
  {
    printf("unable to open file...\n");
    exit(1);
 }
 while(1)
 {
  fseek(fp, offset, SEEK_SET);

  iLen = fread(buff, 1, 16, fp);
  for(ii = 0; ii < iLen; ii++)
    printf("%02x ", buff[ii]);  
    printf("   ");  
  for(ii = 0; ii < iLen; ii++)
  {
    if(buff[ii] >=32 && buff[ii] < 128)
      printf("%c", buff[ii] );  
    else
      printf(".");  
  }

  offset +=iLen;
  printf("\n");

  if(iLen < 16)
   break;
 }
  fclose(fp);
}
    
  
     

