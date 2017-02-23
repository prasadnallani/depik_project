
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
