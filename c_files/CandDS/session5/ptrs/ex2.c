
main(void)
{
  int intVal;
  short shVal;
  char chVal;

  char *cPtr;
 
  cPtr = (char *)&intVal;
  *cPtr = 126;
  printf("intVal = %d\n", intVal);

  cPtr = (char *)&shVal;
  *cPtr = 100;
  printf("shVal = %d\n", shVal);

  cPtr = &chVal;
  *cPtr = 10;
  printf("chVal = %d\n", chVal);
}
