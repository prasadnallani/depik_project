/* Area of rectangle, triangle and circle using functions */

#include<stdio.h>

/******* macros **********/
#define PI   3.14
#define TRUE 1

/******* function prototypes *********/
int areaOfRectangle(int,int);
int areaOfTriangle(int,int);
int areaOfCircle(int);

main(void)
{
 int recLength, recWidth;
 int triBase, triHeight;
 int radius, area;
 int choice;

 while(TRUE)
 {
   printf("\n1.Compute Area of Rectangle\n");
   printf("2.Compute Area of Triangle\n");
   printf("3.Compute Area of Circle\n");
   printf("4.Exit\n");
   printf("Enter ur Choice\n");
   scanf("%d", &choice);

   switch(choice)
   {
     case 1: 
          //Rectangle
          printf("  ******* Area of Rectangle ********\n");
          printf("Enter length and width of rectangle\n");
          __fpurge(stdin);
          scanf("%d %d", &recLength, &recWidth);
          area = areaOfRectangle(recLength, recWidth);
          printf("Area of rectangle is  = %d\n", area);
          break;
     case 2:
          //Triangle
          printf("  ******* Area of Triangle ********\n");
	  printf("\nEnter base and height of triangle\n");
	  __fpurge(stdin);
	  scanf("%d %d", &triBase, &triHeight);
	  area = areaOfTriangle(triBase, triHeight);
	  printf("Area of triangle is  = %d\n", area);
	  break;
     case 3:
	  //Circle
          printf("  ******* Area of Circle ********\n");
	  printf("\nEnter radius of circle\n");
 	  __fpurge(stdin);
	  scanf("%d", &radius);
	  area = areaOfCircle(radius);
	  printf("Area of Circle is  = %d\n", area);
          break;  
     case 4:
          exit(TRUE);
          break;
    }
  }
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
 
