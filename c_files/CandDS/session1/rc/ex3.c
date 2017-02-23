/********************************************************************
 Area of rectangle, triangle & circle using functions and Testdriver
 functions 
*********************************************************************/

#include<stdio.h>

/******* macros **********/
#define PI   3.14
#define TRUE 1

/******* function prototypes *********/
void areaOfRectangleTstDrv(void);
void areaOfTriangleTstDrv(void);
void areaOfCircleTstDrv(void);
int areaOfRectangle(int,int);
int areaOfTriangle(int,int);
int areaOfCircle(int);

main(void)
{
 int choice;

 while(TRUE)
 {
   printf("\n1.Compute Area of Rectangle\n");
   printf("2.Compute Area of Triangle\n");
   printf("3.Compute Area of Circle\n");
   printf("4.Exit\n");
   printf("Enter ur Choice\n");
   scanf("%d", &choice);
 
   if(choice == 1)
     areaOfRectangleTstDrv();
   else if(choice == 2)
     areaOfTriangleTstDrv();
   else if(choice == 3)
     areaOfCircleTstDrv();
   else if(choice == 4)
      exit(TRUE);
  }
}
/***********************************************************************
* Name :  areaOfRectangleTstDrv()
* Description :
* Inputs : 
* Output : 
***********************************************************************/
void areaOfRectangleTstDrv(void)
{
  int recLength, recWidth;
  int area;

  //Rectangle
  printf("  ******* Area of Rectangle ********\n");
  printf("Enter length and width of rectangle\n");
  __fpurge(stdin);
   scanf("%d %d", &recLength, &recWidth);
   area = areaOfRectangle(recLength, recWidth);
   printf("Area of rectangle is  = %d\n", area);
}
/***********************************************************************
* Name : areaOfTriangle()
* Description :
* Inputs : 
* Output : 
***********************************************************************/
void areaOfTriangleTstDrv(void)
{
  int triBase, triHeight;
  int area;

  //Triangle
  printf("  ******* Area of Triangle ********\n");
  printf("\nEnter base and height of triangle\n");
  __fpurge(stdin);
  scanf("%d %d", &triBase, &triHeight);
  area = areaOfTriangle(triBase, triHeight);
  printf("Area of triangle is  = %d\n", area);
}
/***********************************************************************
* Name :  int areaOfCircle(int radius)
* Description :
* Inputs : radius
* Output : area
*********************************************************************/
void areaOfCircleTstDrv(void)
{
  int radius, area;

  //Circle
  printf("  ******* Area of Circle ********\n");
  printf("\nEnter radius of circle\n");
  __fpurge(stdin);
  scanf("%d", &radius);
  area = areaOfCircle(radius);
  printf("Area of Circle is  = %d\n", area);
}
/***********************************************************************
* Name : int areaOfRectangle(int length, int width)
* Description :
* Inputs : length, width
* Output : area
***********************************************************************/
int areaOfRectangle(int length, int width)
{
 return (length * width);
}
/***********************************************************************
* Name : int areaOfTriangle(int base, int height)
* Description :
* Inputs : base, height
* Output : area
***********************************************************************/
int areaOfTriangle(int base, int height)
{
 return (0.5 * base * height);
}

/***********************************************************************
* Name :  int areaOfCircle(int radius)
* Description :
* Inputs : radius
* Output : area
*********************************************************************/
int areaOfCircle(int radius)
{
 return (PI * radius * radius);
}
 

