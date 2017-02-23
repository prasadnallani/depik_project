  
/***********************************************************************
* Name 	      : int myStrLen(char *)
* Description : compute string length
* Inputs      : string pointer- char *
* Output      : string length - int
***********************************************************************/
int myStrLen(char *pStr)
{
  int ii = 0;

  while(*pStr++ != '\0')
    ii++;

  return ii;
}
