
/********************************************************************
	         	Operations on Unions 
*********************************************************************/

/********* Header files *********/
#include<stdio.h>


/************ macros ************/
#define BOOK_INFO 1
#define STUD_INFO 2
#define TRANS_INFO 3

/********* global variables ***********/
typedef struct bookInfo_s
{

  int bookId;
  char title[40];
  char author[20];

}bookInfo_t;

typedef struct studentInfo_s
{
  char name[40];
  int stuId;
  int phNum;

 }studentInfo_t;

typedef struct transInfo_s
{

  int stuId;
  int bookId;
  int issDate;
  int issMonth;
  int issYear;

}transInfo_t;

typedef union recUnion_s
{

  bookInfo_t    bi;
  studentInfo_t si;
  transInfo_t   ti;

}recUnion_t;

recUnion_t rec, *pRec;


/********* function prototypes ***********/
void getRecord(int recType, recUnion_t *pRec);
void dispRecord(int recType, recUnion_t *pRec);

/***********************************************************************
		Function Definitions 
***********************************************************************/
/***********************************************************************
* Name 	      :main() 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
main(void)
{
 int recType;

 pRec = &rec; 

 printf("   RecordType\n");
 printf("1.Book Info\n");
 printf("2.Student Info\n");
 printf("3.Transaction Info\n");
 printf("Enter ur choice: ");
 scanf("%d", &recType);

 getRecord(recType, pRec);
 dispRecord(recType, pRec);

}
/***********************************************************************
* Name 	      :main() 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void getRecord(int recType, recUnion_t *pRec)
{
  if(recType == BOOK_INFO)
  {
    printf("Enter Book Info\n");
    printf("BookId : ");
    scanf("%d", &(pRec->bi.bookId));
    printf("Title  : ");
    __fpurge(stdin);
    fgets(pRec->bi.title, sizeof(pRec->bi.title)/sizeof(pRec->bi.title[0]),stdin);
    printf("Author : ");
    __fpurge(stdin);
    fgets(pRec->bi.author, sizeof(pRec->bi.author)/sizeof(pRec->bi.author[0]),stdin);
 }

  else if(recType == STUD_INFO)
  {
    printf("Enter Student Info\n");
    printf("Name  : ");
    __fpurge(stdin);
    //fgets(pRec->si.name, sizeof(pRec->si.name)/sizeof(pRec->bi.name[0]), stdin);
    printf("StuId : ");
    scanf("%d", &(pRec->si.stuId));
    printf("PhNum : ");
    scanf("%d", &(pRec->si.phNum));
  }
  else if(recType == TRANS_INFO)
  {
    printf("Enter Transacton Info\n");
    printf("StuId  : ");
    scanf("%d", &(pRec->ti.stuId));
    printf("BookId  : ");
    scanf("%d", &(pRec->ti.bookId));
    printf("IssDate : ");
    scanf("%d", &(pRec->ti.issDate));
    printf("IssMonth: ");
    scanf("%d", &(pRec->ti.issMonth));
    printf("IssYear : ");
    scanf("%d", &(pRec->ti.issYear));
  }
  else 
    printf("Inavalid option\n");
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
***********************************************************************/
void dispRecord(int recType, recUnion_t *pRec)
{
  if(recType == BOOK_INFO)
  {
    printf("******Book Info******\n");
    printf("BookId : %d\n", pRec->bi.bookId);
    printf("Title  : %s",pRec->bi.title);
    printf("Author : %s\n",pRec->bi.author);
 }

  else if(recType == STUD_INFO)
  {
    printf("*******Student Info*******\n");
    printf("Name  : %s\n",pRec->si.name);
    printf("StuId : %d\n", pRec->si.stuId);
    printf("PhNum : %d\n", pRec->si.phNum);
  }
  else if(recType == TRANS_INFO)
  {
    printf("*******Transacton Info******\n");
    printf("StuId  : %d\n", pRec->ti.stuId);
    printf("BookId  : %d\n", pRec->ti.bookId);
    printf("IssDate : %d\n", pRec->ti.issDate);
    printf("IssMonth: %d\n", pRec->ti.issMonth);
    printf("IssYear : %d\n", pRec->ti.issYear);
  }
  else 
    printf("Inavalid option\n");
}
