#include <stdio.h>

int countVowelsInStr( char *pStr);
void countVowelsInStrTD(void);
/***********************************************************************
* Name 	      : int countVowelsInStr(char*)
* Description : append source string 2 source dest string
* Inputs      : char *, char *
* Output      : none
***********************************************************************/
int countVowelsInStr( char *pStr)
{
  int ii = 0;
  
  while( *pStr != '\n' ) 
  {
   if( (*pStr == 'a') || (*pStr == 'A') || (*pStr == 'e') || (*pStr == 'E') || 
       (*pStr == 'i') || (*pStr == 'I') || (*pStr == 'o') || (*pStr == 'O') || 
       (*pStr == 'u') || (*pStr == 'U') )
     ii++;
     pStr++;
  }
 return ii;
}
/***********************************************************************
* Name 	      : void countVowelsInStrTD(void)
* Description : Test Driver function for countVowelsInStr(char *)
* Inputs      : None
* Output      : None
***********************************************************************/
void countVowelsInStrTD(void)
{
  char str[100];
  int noOfVowels;

  printf("Enter a string\n");
  __fpurge(stdin);
  fgets(str, sizeof(str), stdin);

  noOfVowels = countVowelsInStr(str);
  printf("No of vowels in the string = %d\n",noOfVowels);
}

