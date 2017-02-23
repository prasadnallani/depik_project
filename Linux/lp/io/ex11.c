/********************************************************************
      Operations on files (read ASCII and prepare binary) 
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
char buff[100];

/********* function prototypes ***********/
int ASCIIToBinaryFile(void);
int dispAllStudentRecs(void);
void line2Rec(char *buff, student_t *tmpRec);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
int ASCIIToBinaryFile(void)
{ 
  char flag = 0;
  student_t tmpRec;
  
  fseek(fp, 0, SEEK_SET);
  
  while(fread(buff,1,REC_SIZE,fp1) == REC_SIZE)
  {
    line2Rec(buff, &tmpRec);
    if(fwrite((char*)&tmpRec, 1, sizeof(sRec), fp) == sizeof(sRec))
    {
      flag  = 1;  
      continue;
    }
    else
        break;
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
void line2Rec(char *buff, student_t *tmpRec)
{
  char *str;
 
  str = strtok(buff, "|");
  sscanf(str, "%d", &tmpRec->id);
  str = strtok(0, "|");
  sscanf(str, "%s", tmpRec->name);
  str = strtok(0, "\n");
  sscanf(str, "%d", &tmpRec->phNum);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
*********************************************************************/
int dispAllStudentRecs()
{
  int flag = 0;
  student_t tmpRec;
  
  fseek(fp, 0, SEEK_SET);
  
  while( fread((char*)&tmpRec,1,sizeof(tmpRec),fp) == sizeof(tmpRec) )
  {
    if(tmpRec.id != -1)
    {
      printf("id = %d\nname = %s\nphNum = %d\n\n", tmpRec.id, tmpRec.name, tmpRec.phNum);
      flag = 1;
    }
  }    

  if(flag == 0)
    return NO_RECORDS_ERR;

  return SUCCESS;
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
 
   fp = fopen("binStudentRecs.dat", "w+");

   if(fp == 0)
   {
     printf("Unable to open file binstudentRecs.dat\n");
     exit(1);
   }
 
   fp1 = fopen("textStudentRecs.dat", "r");

   if(fp1 == 0)
   {
     printf("Unable to open file studentRecs.dat\n");
     exit(1);
   }

   status =  ASCIIToBinaryFile();
   if(status == SUCCESS)
     printf("Bin file created successfully\n");
   else
     printf("No records in the textfile file to create bin file\n");

   dispAllStudentRecs();
}

  
     
 
  
    
  
