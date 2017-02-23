
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
     count++;
  pStr++;
  }
 return count;
}
