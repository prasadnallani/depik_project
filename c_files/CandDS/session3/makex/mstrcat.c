
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
