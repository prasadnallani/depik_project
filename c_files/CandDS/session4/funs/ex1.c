void getSumDifAndProduct(int a, int b, int *sum, int *dif, int *product)
{
  *sum = a+b;
  *dif = a-b;
  *product = a*b;
}
main(void)
{
 int x,y, sum, dif, prod;
 printf("enter two integers\n");
 scanf("%d %d", &x,&y);
 getSumDifAndProduct(x, y, &sum, &dif, &prod);
 printf("sum  = %d\n", sum);
 printf("Dif  = %d\n", dif);
 printf("product  = %d\n", prod);
}
