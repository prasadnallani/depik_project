#include<stdio.h>

int uig1;
int ig1 = 1;
int uig2;
int ig2 = 2;
int uig3;
int ig3 =3;

void f1(int pa, int pb)
{
  int x,y;
  printf("\nAddress of all the local and parameter variables of f1\n");
  printf("Address of parameter variable\n pa = %x\n,  pb = %x\n", &pa,&pb);
  printf("Address of local variables \n x = %x\n,  y = %x\n", &x, &y);
}

void f2()
{ 
  f1(1, 2);
}

int main()
{
  int uila;
  int ila = 10;
  static uisl;
  static isl =20;

  /******* printf the address of all the functions*******/
 printf("\nAddresses of function f1 = %x\n, and f2 = %x\n and main = %x\n", &f1, &f2, &main);

 printf("\nAddresss of all the local variables \n");
 printf("uila = %x\n, ila = %x\n", &uila,&ila);
 printf("uisl = %x\n, isl = %x\n", &uisl,&isl);
  
printf("\n address of all the global variables in main\n");
printf("uig1 = %x\n, ig1 = %x\n", &uig1, &ig1);
printf("uig2 = %x\n, ig2 = %x\n", &uig2, &ig2);
printf("uig3 = %x\n, ig3 = %x\n", &uig3, &ig3);

/********print he address of dynamically allocaed memory********/
printf("\n Address of dynamically allocated memory = %x\n", malloc(100));
f1(1,2);
f2();
f1(1,2);
}



