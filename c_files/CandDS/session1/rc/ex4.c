/********************************************************************
		Operations on Arrays 
*********************************************************************/

/****** Header files *********/
#include<stdio.h>

/********* macros ***********/
#define NUM_OF_STUDENTS  16
#define PASS_MARKS       40
#define SECOND_CLASS_MIN 50
#define SECOND_CLASS_MAX 60
#define TRUE		 1

/********* function prototypes ***********/
int avgMark(int marks[], int size);
int minMark(int marks[], int size);
int maxMark(int marks[], int size);
int passCount(int marks[], int size);
int secondClassCount(int marks[], int size);
void printFailOr2ndFirst(int marks[], int size);
int aboveAverageCount(int marks[], int);
void printArray(int marks[], int size);
void fillArray(int marks[], int size);


/********* global variables ***********/
int marks[NUM_OF_STUDENTS] = { 70, 65, 89, 45, 32, 58, 91, 83, 28, 59, 
				66, 60, 45, 38, 78, 68};


/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name : int avgMark(int, int);
* Description : calcutes the avg of array elements and returns
* Inputs : array elements, array size
* Output : avg of marks
***********************************************************************/
int avgMark(int marks[], int size)
{
 int ii, sum = 0;

 for(ii = 0; ii < size; ii++)
   sum+= marks[ii];

 return (sum / size);
}
/***********************************************************************
* Name : int minMark(int, int);
* Description : calcutes the min of array elements and returns
* Inputs : array elements, array size
* Output : min of marks
***********************************************************************/
int minMark(int marks[], int size)
{
 int ii = 1, min = marks[0]; 
  
  while(ii < size)
  {
    if(marks[ii] < min)
       min = marks[ii];
    ii++;
  }
  return min;
}
/***********************************************************************
* Name : int maxMark(int, int);
* Description : calcutes the max of array elements and returns
* Inputs : array elements, array size
* Output : max of marks
***********************************************************************/
int maxMark(int marks[], int size)
{
 int ii = 1, max = marks[0]; 

 do 
 {
   if(marks[ii] > max)
      max = marks[ii];
   ii++;
  }while(ii < size);

  return max;
}
/***********************************************************************
* Name : int passCount(int, int);
* Description : calcutes no of students passed (i.e marks >= 40)
* Inputs : array elements, array size
* Output : no of students passed
***********************************************************************/
int passCount(int marks[], int size)
{
 int ii = 0 , noOfPassed = 0;

  while(ii < size)
  {
    if(marks[ii] >= PASS_MARKS) 
        noOfPassed++;
    ii++;
  }
  return noOfPassed;
}
/***********************************************************************
* Name : int secondClassCount(int, int);
* Description : calcutes no of second class students (i.e marks>=50&<60)
* Inputs : array elements, array size
* Output : no of second class students
***********************************************************************/
int secondClassCount(int marks[], int size)
{
 int ii = 0, noOfSecondCount;
 
 while(ii < size)
 { 
  if((marks[ii] >= SECOND_CLASS_MIN) && (marks[ii] < SECOND_CLASS_MAX))
     noOfSecondCount++;
  ii++;
 }
 return noOfSecondCount;
}
/***********************************************************************
* Name : void printFailOr2ndFirst(int, int);
* Description : printf no of fail, ordinary,second, first grade students
* Inputs : array elements, array size
* Output : none
***********************************************************************/
void printFailOr2ndFirst(int marks[], int size)
{ 
 int ii = 0; 
 int  failCount = 0;
 int  ordiCount = 0;
 int  secondCount = 0; 
 int  firstCount = 0;

 // secondCount = secondClassCount(marks, size); //CHECK IT LATER

 while(ii < size)
 {
  if( marks[ii] < PASS_MARKS)
     failCount++;
  else if(( marks[ii] >= PASS_MARKS) && (marks[ii] < SECOND_CLASS_MIN))
     ordiCount++;
  else if((marks[ii] >= SECOND_CLASS_MIN)&&(marks[ii]<SECOND_CLASS_MAX))
     secondCount++;
  else if( marks[ii] >= SECOND_CLASS_MAX)
     firstCount++;
  ii++;
 }
 printf("No of fail Students           = %d\n", failCount); 
 printf("No of ordinary class Students = %d\n", ordiCount); 
 printf("No of second class Students   = %d\n", secondCount); 
 printf("No of first class Students    = %d\n", firstCount); 
}
/***********************************************************************
* Name : int aboveAverageCount(int, int);
* Description :calculate no of students who got above avg marks of class
* Inputs : array elements, array size
* Output : no students who got above avg marks
***********************************************************************/
int aboveAverageCount(int marks[], int size)
{
 int ii, avg, noOfAAvgCount = 0;

 avg = avgMark(marks, size);

 for(ii = 0; ii < size; ii++)
    if(marks[ii] >= avg)
       noOfAAvgCount++;

 return noOfAAvgCount;
}
/***********************************************************************
* Name : void printArray(int, int);
* Description :prints all marks present int the array 4 per line
* Inputs : array elements, array size
* Output : none
***********************************************************************/
void printArray(int marks[], int size)
{
 int  ii = 0;
 printf("Marks of all Students\n");
 while(ii < size)
 {
   printf("%d\t", marks[ii]);
   if( (ii+1) % 4 == 0 )
   {
    printf("\n");
   }
   ii++;
 }
}
/***********************************************************************
* Name : void filltArray(int, int);
* Description :fills the marks array taking input from user
* Inputs : array elements, array size
* Output : none
***********************************************************************/
void fillArray(int marks[], int size)
{
 int  ii;
 printf("Enter %d no of integer marks(elements)\n", size);

 for(ii = 0; ii < size; ii++)
  scanf("%d", &marks[ii]);
}
/***********************************************************************
* Name :  main(void)
* Description :
* Inputs : none
* Output : default
***********************************************************************/
int main(void)
{
 int choice, arraySize;

 arraySize = sizeof(marks)/sizeof(marks[0]);


 printf("array size = %d\n" ,arraySize);

 while(TRUE)
 {
  printf("\n******* Operation on  arrays*********\n");
  printf("0.Fill the Array(marks)\n");
  printf("1.Print the Array(marks)\n");
  printf("2.Compute average of Marks\n");
  printf("3.Compute minimum of Marks\n");
  printf("4.Compute maximum of Marks\n");
  printf("5.Compute no of Students passed\n");
  printf("6.Compute no of second class students\n");
  printf("7.Compute no of above average Students\n");
  printf("8.Print no of Fail, Ordinary,2nd and 1st class students\n");
  printf("9.Exit\n");
  printf("Enter your choice\n");
  scanf("%d", &choice); 

   switch(choice)
   {
    case 0:
          fillArray(marks, arraySize);
          break;
    case 1:
	  printArray(marks, arraySize);
          break;
    case 2:
	  printf("Average of marks = %d\n", avgMark(marks, arraySize));
          
          break;
    case 3:
	  printf("Min of marks = %d\n", minMark(marks, arraySize));
          break;
    case 4:
	  printf("Max of marks = %d\n", maxMark(marks, arraySize));
          break;
    case 5:
	  printf("No of pass Students = %d\n",passCount(marks, arraySize));
          break;
    case 6:
	  printf("No of second class Students = %d\n",secondClassCount(marks, arraySize));
          break;
    case 7:
	  printf("No of above Average Students = %d\n",aboveAverageCount(marks, arraySize));
          break;
    case 8:
	  printFailOr2ndFirst(marks, arraySize);
          break;
    case 9:
 	  exit(TRUE);
          break;
   }
 }
}

 


 

