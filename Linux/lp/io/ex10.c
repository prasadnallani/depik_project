/********************************************************************
      Operations on files (read bianry and prepare ASCII) 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

/************ macros ************/
#define SUCCESS		0	
#define NO_RECORDS_ERR  1
#define REC_SIZE	39

/********* global variables ***********/
typedef struct srudent_s
{

  int id;
  char name[20];
  int phNum;

}student_t;

student_t sRec;
FILE *fp, *fp1;

/********* function prototypes ***********/
int binaryToASCIIFile(void);
void stripNewLine(char *name);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
int binaryToASCIIFile(void)
{ 
  char flag = 0;
  student_t tmpRec;
  
  fseek(fp, 0, SEEK_SET);
  
  while(fread((char*)&tmpRec,1,sizeof(sRec),fp) == sizeof(sRec) )
  {
     stripNewLine(tmpRec.name);
     fprintf(fp1, "%-4d | %-20s | %-8d\n", tmpRec.id, tmpRec.name, tmpRec.phNum);
     flag = 1;
  }    
  if(flag)
    return SUCCESS;

  return NO_RECORDS_ERR;

}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
void stripNewLine(char *name)
{
  int len;
  
  len = strlen(name);
  if(name[len - 1] =='\n')
    name[len - 1] = 0;
}
  
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
int main(void)
{
   int status;
 
   fp = fopen("studentRecs.dat", "r");

   if(fp == 0)
   {
     printf("Unable to open file studentRecs.dat\n");
     exit(1);
   }
 
   fp1 = fopen("textStudentRecs.dat", "w");

   if(fp1 == 0)
   {
     printf("Unable to open file studentRecs.dat\n");
     exit(1);
   }

   status = binaryToASCIIFile();
   if(status == SUCCESS)
     printf("Text file created successfully\n");
   else
     printf("No records in the bin file to create text file\n");
}

  
     
