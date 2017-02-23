main(void)
{
 float fVal = 10.234;
 char *cPtr;
 short ii;

 cPtr = (char*)&fVal;
 
 for(ii = 0; ii<4; ii++)
 {
    printf("%x ", *cPtr);
    cPtr++;
 }
    printf("\n");
}
 
 
