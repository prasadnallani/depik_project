/********************************************************************
	         	Operations on files 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>
#include<fcntl.h>

/************ macros ************/
#define SUCCESS		0	
#define NO_RECORDS_ERR  1
#define ERR  		2
#define ADD  		1
#define DEL  		2
#define DISP 		3
#define EXIT 		4
#define REC_SIZE	sizeof(sRec)

/********* global variables ***********/
typedef struct srudent_s
{

  int id;
  char name[20];
  int phNum;

}student_t;

student_t sRec;

/********* function prototypes ***********/
int deleteStudentRec(int fd, int stuId);
int addNewStudentRec(int fd, student_t *ps);
int dispAllStudentRecs(int  fd);
void dispUserInterface(char *pch);
void getRecord(student_t* newRec);
int openFileNGetfd(void);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      : int dispAllStudentRecs(int  fd)
* Description : displays all student recs removing the deleted one's
* Inputs      : fd
* Output      : display all recs ( SUCCESS, FAIL)
*********************************************************************/
int dispAllStudentRecs(int  fd)
{
  int flag = 0;
  student_t tmpRec;
  
  lseek(fd, 0, SEEK_SET);
  
  while( read(fd, &tmpRec, sizeof(tmpRec)) == sizeof(tmpRec) )
  {
    if(tmpRec.id != -1)
    {
      printf("id = %d\nname = %sphNum = %d\n\n", tmpRec.id, tmpRec.name, tmpRec.phNum);
      flag = 1;
    }
  }    

  if(flag == 0)
    return NO_RECORDS_ERR;

  return SUCCESS;
}
  
/***********************************************************************
* Name 	      : int addNewStudentRec(int fd, student_t *ps)
* Description : Adds new record to the db file
* Inputs      : fd, student_t *ps
* Output      : SUCCESS, FAIL
*********************************************************************/
int addNewStudentRec(int fd, student_t *ps)
{
  lseek(fd, 0, SEEK_SET);
  
  while( read(fd, &sRec, sizeof(sRec)) == sizeof(sRec) )
  {
    if(sRec.id == -1)
    {
      lseek(fd, -1 * REC_SIZE, SEEK_CUR);
      break;
    }
  }
  
  if( write(fd, ps, sizeof(sRec)) == sizeof(sRec) )
    return SUCCESS;

  return ERR;
}
/***********************************************************************
* Name 	      : int deleteStudentRec(int fd, int id)
* Description : deletes a record from the db file
* Inputs      : fd, id
* Output      : SUCCESS, ERR
*********************************************************************/
int deleteStudentRec(int fd, int stuId)
{
  int delId  = -1;
  student_t rec;
  
  lseek(fd, 0, SEEK_SET);
  
  while( read(fd, &rec, sizeof(rec)) == sizeof(rec) )
  {
    if(rec.id == stuId)
    {
      lseek(fd, -sizeof(rec), SEEK_CUR);
      if( write(fd, &delId, sizeof(delId)) == sizeof(delId) )
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
  printf("Enter student phoneNumber\n");
  scanf("%d", &newRec->phNum);
}
/***********************************************************************
* Name 	      : 
* Description :
* Inputs      : 
* Output      :
*********************************************************************/
int openFileNGetfd(void)
{
  int fd;
  
  fd = open("studentRecs.dat", O_RDWR);
  
  if(fd < 0)
  {
    printf("Creating file...\n");
    fd = open("studentRecs.dat", O_RDWR | O_CREAT, 0760);

    if(fd < 0)
    {
      printf("Unable to create File\n");
      exit(1);
    }
  }
  return fd;
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
  int stuId, fd, status;
  student_t *newRec;

  if( (newRec = (student_t*)malloc(sizeof(newRec))) == NULL)
  {
    printf("Memory not allocated for new Rec\n");
    exit(1);
  }
  
  fd = openFileNGetfd();
while(1)
{
  dispUserInterface(&option);
  
  switch(option)
  {
     case ADD:
	      getRecord(newRec);
              status = addNewStudentRec(fd, newRec);
              if(status == SUCCESS)
 	        printf("Record added successfully\n");
	      else
 	        printf("Adding new record failed\n");
   	      break;

     case DEL:
  	      printf("Enter Student Id whose rec is to be deleted\n");
	      scanf("%d", &stuId);
	      status = deleteStudentRec(fd, stuId);
              if(status == SUCCESS)
 	        printf("Record deleted successfully\n");
	      else
 	        printf("Record not found\n");
  	      break;

      case DISP:
	        status = dispAllStudentRecs(fd);
  	        if(status != SUCCESS)
	          printf("No Records to Dsiaplay\n");
                 break;
      case EXIT:
		exit(1);

      default: 
		printf("Invalid Choice\n");
		break;
    }           
 }
}	
