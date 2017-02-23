#include<stdio.h>

int countWordsInStr( char *pStr);
void countWordsInStrTD(void);

/***********************************************************************
* Name 	      : void countWordsInStrTD(void)
* Description : Test Driver function for countWordsInStr(char *)
* Inputs      : None
* Output      : None
***********************************************************************/
void countWordsInStrTD(void)
{
  char str[100];
  int noOfWords;

  printf("Enter a string\n");
  __fpurge(stdin);
  fgets(str, sizeof(str), stdin);

  noOfWords = countWordsInStr(str);
  printf("No of words in the string = %d\n", noOfWords);
}

/***********************************************************************
* Name 	      : int countWordsInStr(char*)
* Description : count no of words in the string
* Inputs      : char *, 
* Output      : none
***********************************************************************/
int countWordsInStr( char *pStr)
{
 int ii = 0, count = 1 ;

 while( pStr[ii] != '\n')
 {
   //if( ( (pStr[ii] == ' ') && (pStr[ii+1] != ' ') ) || ( (pStr[ii] == '\t')&&(pStr[ii+1] != '\t') ) ) //Both conditions are correct we can use any one
   if( ( (*pStr == ' ') && (*(pStr+1) != ' ') ) || ( (*pStr == '\t')&&(*(pStr+1) != '\t') ) )
   {
     printf("char = %c\n", *pStr);
     count++;
   }
 pStr++;
 //ii++;
 }
 return count;
}      
