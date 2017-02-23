main(void)
{
  int intVal;
  short shVal;
  char chVal;

  int *iPtr;
  short *sPtr;
  char *cPtr;
 
  iPtr = &intVal;
  sPtr = &shVal;
  cPtr = &chVal;

  *iPtr = 1000;
  *sPtr = 100;
  *cPtr = 10;
  
  printf("intVal = %d\n", intVal);
  printf("shVal = %d\n", shVal);
  printf("chVal = %d\n", chVal);
}

