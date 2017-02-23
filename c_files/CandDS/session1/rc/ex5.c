/********************************************************************
	         	Operations on Strings 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>

/************ macros ************/
#define	TRUE	1

/********* global variables ***********/

/********* function prototypes ***********/
int myStrLen(char *str);
void myStrCpy(char *pDstStr, char *pSrcStr);
void myStrCat(char *pDstStr, char *pSrcStr);
int countVowelsInStr( char *pStr);
int countWordsInStr( char *pStr);
void myStrLenTD(void);
void myStrCpyTD(void);
void myStrCatTD(void);
void countVowelsInStrTD(void);
void countWordsInStrTD(void);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : int myStrLen(char *)
* Description : compute string length
* Inputs      : string pointer- char *
* Output      : string length - int
***********************************************************************/
int myStrLen(char *pStr)
{
  int ii = 0;

  while(*pStr++ != '\n')
    ii++;

  return ii;
}
/***********************************************************************
* Name 	      : void myStrCpy(char *, char *)
* Description : copies string from source 2 destination
* Inputs      : char *, char *
* Output      : none
***********************************************************************/
void myStrCpy(char *pDstStr, char *pSrcStr)
{
  while(*pSrcStr)
    *pDstStr++ = *pSrcStr++; //copies first and then increments

 *pDstStr = '\0';
}
/***********************************************************************
* Name 	      : void myStrCat(char *, char *)
* Description : append source string 2 source dest string
* Inputs      : char *, char *
* Output      : none
***********************************************************************/
void myStrCat(char *pDstStr, char *pSrcStr)
{
  while(*pDstStr != '\n')
    pDstStr++;

 while(*pSrcStr != '\n')
   *pDstStr++ = *pSrcStr++;

 *pDstStr = '\0';
} 
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
	
 
/***********************************************************************
* Name 	      : void myStrLenTD()
* Description : Test Driver function for myStrLen(char *)
* Inputs      : None
* Output      : None
***********************************************************************/
void myStrLenTD(void)
{ 
  char str[100];
  int strLength;

  printf("Enter a String\n");
  __fpurge(stdin);
  fgets( str, sizeof(str), stdin);

  strLength = myStrLen(str);
  printf("String length = %d\n", strLength);
}
/***********************************************************************
* Name 	      : void myStrCpyTD(char *, char *)
* Description : Test Driver function for myStrCpy(char *, char *)
* Inputs      : char*, char*
* Output      : None
***********************************************************************/
void myStrCpyTD(void)
{ 
  char srcStr[100],destStr[100];

  if( sizeof(srcStr) > sizeof(destStr) )
    printf("size of destination string is less than source string\n");

  printf("Enter source string\n");
  __fpurge(stdin);
  fgets(srcStr, sizeof(srcStr), stdin);

  myStrCpy(destStr, srcStr);
  printf("String after copy = %s\n",destStr);
}
/***********************************************************************
* Name 	      : void myStrCatTD(char *, char *)
* Description : Test Driver function for myStrCat(char *, char *)
* Inputs      : char*, char*
* Output      : None
***********************************************************************/
void myStrCatTD(void)
{
  char srcStr[100],destStr[200];

  printf("Enter source string\n");
  __fpurge(stdin);
  fgets(srcStr, sizeof(srcStr), stdin);
  printf("Enter dest string\n");
  __fpurge(stdin);
  fgets(destStr, sizeof(destStr), stdin);

  if( sizeof(srcStr) + myStrLen(destStr) >  sizeof(destStr) )
    printf("size of destination string is less too fit the stringa\n");
  
  myStrCat(destStr, srcStr);
  printf("String after concatination = %s\n", destStr);
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
* Name 	      : main()
* Description : 
* Inputs      : None
* Output      : None
***********************************************************************/
main(void)
{
 int choice;

 while(TRUE)
 {
  printf("\n******* Operations on Strings ********\n");
  printf("0.Compute the length of a string\n");
  printf("1.Copy a string from Source to Destination\n");
  printf("2.Concatinate a String with the Other\n");
  printf("3.Compute no of Vowels in a String\n");
  printf("4.Compute no of words in String\n");
  printf("5.Exit\n");
  printf("Enter your choice\n");
  scanf("%d", &choice); 

   switch(choice)
   {
    case 0:
 	  myStrLenTD();
          break;
    case 1:
 	  myStrCpyTD();
          break;
    case 2:
	  myStrCatTD();
          break;
    case 3:
 	  countVowelsInStrTD();
          break;
    case 4:
 	  countWordsInStrTD();
          break;
    case 5:
	  exit(TRUE);
          break;
     }//end of switch
  }//end of while
}
