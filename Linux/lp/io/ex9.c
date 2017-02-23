/********************************************************************
	      Operations on files (store Rcords in ASCII format) 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

/************ macros ************/
#define SUCCESS		0	
#define NO_RECORDS_ERR  1
#define ERR  		2
#define ADD  		1
#define DEL  		2
#define DISP 		3
#define EXIT 		4
#define REC_SIZE	39

/********* global variables ***********/
typedef struct srudent_s
{

  int id;
  char name[20];
  int phNum;

}student_t;

student_t sRec;
FILE *fp;
char buff[100];

/********* function prototypes ***********/
int deleteStudentRec(int stuId);
int addNewStudentRec(student_t *ps);
int dispAllStudentRecs(void);
void dispUserInterface(char *pch);
void getRecord(student_t* newRec);
void openFile(void);
void stripNewLine(char *name);
void line2Rec(char *buff, student_t *pSrec);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : int dispAllStudentRecs(void)
* Description : displays all student recs removing the deleted one's
* Inputs      : fd
* Output      : display all recs ( SUCCESS, FAIL)
*********************************************************************/
int dispAllStudentRecs(void)
{
  int flag = 0;
  student_t tmpRec;
  
  fseek(fp, 0, SEEK_SET);
  
  while(fread(buff,1,REC_SIZE,fp) == REC_SIZE )
  {
    line2Rec(buff, &tmpRec);
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
* Name 	      : int addNewStudentRec(student_t *ps)
* Description : Adds new record to the db file
* Inputs      : student_t *ps
* Output      : SUCCESS, FAIL
*********************************************************************/
int addNewStudentRec(student_t *ps)
{
  student_t tmpRec;

  fseek(fp, 0, SEEK_SET);  //rewind(fp);
  
  while(fread(buff,1,REC_SIZE,fp) == REC_SIZE )
  {
    line2Rec(buff, &tmpRec);
    if(tmpRec.id == -1)
    {
      fseek(fp, -1 * REC_SIZE, SEEK_CUR);
      fprintf(fp,"%-4d | %-20s | %-8d\n", ps->id, ps->name, ps->phNum);
      return SUCCESS;
    }
  }
  fprintf(fp, "%-4d | %-20s | %-8d\n", ps->id, ps->name, ps->phNum);
 
  return SUCCESS;
}
/***********************************************************************
* Name 	      : int deleteStudentRec(int fd, int id)
* Description : deletes a record from the db file
* Inputs      : fd, id
* Output      : SUCCESS, ERR
*********************************************************************/
int deleteStudentRec(int stuId)
{
  int delId  = -1;
  student_t rec;
  
  fseek(fp, 0, SEEK_SET);
  
  while( fread(buff,1,REC_SIZE,fp) == REC_SIZE )
  {
    line2Rec(buff, &rec);
    if(rec.id == stuId)
    {
      rec.id = -1;
      fseek(fp, -1 * REC_SIZE, SEEK_CUR);
      fprintf(fp, "%-4d | %-20s | %-8d\n", rec.id, rec.name, rec.phNum);
      return SUCCESS;
    }
  }
  return ERR;
}
/***********************************************************************
* Name 	      : 
* Description :
* Inputs      : 
* Output      :
*********************************************************************/
void line2Rec(char *buff, student_t *pSrec)
{
  char *str;
  str = strtok(buff, "|");
  sscanf(str, "%d", &pSrec->id);
  str = strtok(0, "|");
  sscanf(str, "%s", pSrec->name);
  str = strtok(0, "\n");
  sscanf(str, "%d", &pSrec->phNum);
}
  
/***********************************************************************
* Name 	      : 
* Description :
* Inputs      : 
* Output      :
*********************************************************************/
void dispUserInterface(char *ch)
{
  printf("\n\nDatabase of Student Using Files\n");
  printf("1.Add a new record\n");
  printf("2.Delete a record\n");
  printf("3.Display all records\n");
  printf("4.Quit the program\n");
  printf("Enter ur choice\n");
  scanf("%d", ch);
}

/***********************************************************************
* Name 	      : 
* Description :
* Inputs      : 
* Output      :
*********************************************************************/
void getRecord(student_t* newRec)
{
  printf("Enter student Id\n");
  scanf("%d", &newRec->id);
  printf("Enter student name\n");
  __fpurge(stdin) ;
  fgets(newRec->name, sizeof(newRec->name), stdin);
  stripNewLine(newRec->name);
  printf("Enter student phoneNumber\n");
  scanf("%d", &newRec->phNum);
  //printf("phNum = %d\n", newRec->phNum);
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
void openFile(void)
{
  fp = fopen("TStuRecs.dat", "r+");
  //printf("fp = %x\n", fp);
  
  if(fp == 0)
  {
    fp = fopen("TStuRecs.dat", "w+");
    if(!fp)
    {
      printf("Unable to create File\n");
       exit(1);
     }
    }
 }
/***********************************************************************
* Name 	      : 
* Description :
* Inputs      : 
* Output      :
*********************************************************************/
main(void)
{
  char option;
  int stuId,status;
  student_t *newRec;

  if( (newRec = (student_t *)malloc(sizeof(student_t))) == NULL)
  {
    printf("Memory not allocated for new Rec\n");
    exit(1);
  }
  

while(1)
{
  openFile();
  dispUserInterface(&option);
  
  switch(option)
  {
     case ADD:
	      getRecord(newRec);
              status = addNewStudentRec(newRec);
              if(status == SUCCESS)
 	        printf("Record added successfully\n");
	      else
 	        printf("Adding new record failed\n");
   	      break;

     case DEL:
  	      printf("Enter Student Id whose rec is to be deleted\n");
	      scanf("%d", &stuId);
	      status = deleteStudentRec(stuId);
              if(status == SUCCESS)
 	        printf("Record deleted successfully\n");
	      else
 	        printf("Record not found\n");
  	      break;

      case DISP:
	        status = dispAllStudentRecs();
  	        if(status != SUCCESS)
	          printf("No Records to Dsiaplay\n");
                 break;
      case EXIT:
		exit(1);

      default: 
		printf("Invalid Choice\n");
		break;
    }           
    fclose(fp);
 }
 free(newRec);
}	
