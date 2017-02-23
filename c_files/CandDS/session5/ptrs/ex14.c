#include<stdio.h>

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void areaOfRectangle(int length, int width, int *pArea)
{
 *pArea = length * width;
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void areaOfTriangle(int base, int height, int *pArea)
{
 *pArea = 0.5*base * height;
}
/***********************************************************************
* Name 	      :main(void) 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 int l,w, aR;
 int b,h,aT;
 printf("Enter lenght and widh of rectangle\n");
 scanf("%d%d",&l,&w);
 areaOfRectangle(l, w, &aR);
 printf("Area of rectangle = %d\n", aR);


 printf("Enter base and height of triangle\n");
 scanf("%d%d",&b,&h);
 areaOfTriangle(b, h, &aT);
 printf("Area of triangle = %d\n", aT);
}

