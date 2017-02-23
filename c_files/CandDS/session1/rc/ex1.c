/* Area of rectangle, triangle and circle with out using functions */
#include<stdio.h>

#define PI 3.14

main(void)
{
 int recWidth, recHeight;
 int triBase, triHeight;
 int radius, area;

//Rectangle
 printf("Enter width of rectangle\n");
__fpurge(stdin);
 scanf("%d\n", &recWidth);
 printf("Enter  height of rectangle\n");
__fpurge(stdin);
 scanf("%d", &recHeight);
 area = recWidth * recHeight;
 printf("Area of rectangle is  = %d\n", area);

//Triangle
 printf("\nEnter base and height of triangle\n");
__fpurge(stdin);
 scanf("%d %d", &triBase, &triHeight);
 area = 0.5 * triBase * triHeight;
 printf("Area of triangle is  = %d\n", area);

//Circle
printf("\nEnter radius of circle\n");
__fpurge(stdin);
scanf("%d", &radius);
area = PI*radius*radius;
printf("Area of Circle is  = %d\n", area);

}


/* __fpurge("Stream")

The function fpurge() clears the buffers of the given stream. For output streams this discards any unwritten output. 
For input streams this discards any input read from the underlying object but not yet obtained via getc(3); 
this includes any text pushed back via ungetc(). See also fflush(3).
The function __fpurge() does precisely the same, but without returning a value.   

*/