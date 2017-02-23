
#include<stdio.h>

/*********global variables*********/
typedef struct bookInfo_s
{
  int bookId;
  char title[40];
  char author[20];
}bookInfo_t;

bookInfo_t *pBi[5];

/*********function prototypes*********/
void getBookInfo(bookInfo_t *pBi);
void printBookInfo(bookInfo_t *pBi);
 

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 int ii;
 bookInfo_t b1, b2, b3, b4, b5;

 for(ii = 0; ii < 5; ii++)
   pBi[ii] = (bookInfo_t*)malloc(sizeof(bookInfo_t));

 getBookInfo(&b1);
 getBookInfo(&b2);
 getBookInfo(&b3);
 getBookInfo(&b4);
 getBookInfo(&b5);

 printBookInfo(&b1);
 printBookInfo(&b2);
 printBookInfo(&b3);
 printBookInfo(&b4);
 printBookInfo(&b5);
}
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void getBookInfo(bookInfo_t *pBi)
{
  printf("Enter BookInfo\n");
  printf("BookId :");
  scanf("%d", &(pBi->bookId));
  __fpurge(stdin);
  printf("Title :");
  fgets(pBi->title, sizeof(pBi->title)/sizeof(pBi->title[0]), stdin);
  __fpurge(stdin);
  printf("Author :");
  fgets(pBi->author, sizeof(pBi->author)/sizeof(pBi->author[0]), stdin);
}

/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
void printBookInfo(bookInfo_t *pBi)
{
  printf("\n*******BookInfo*******\n");
  printf("BookId : %d\n",pBi->bookId);
  printf("Title  : %s",pBi->title);
  printf("Author : %s\n",pBi->author);
}
