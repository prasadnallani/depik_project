
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
