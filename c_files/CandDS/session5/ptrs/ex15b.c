
#include<stdio.h>

/*********global variables*********/
typedef struct bookInfo_s
{
  int bookId;
  char title[40];
  char author[20];
}bookInfo_t;



/*********function prototypes*********/
 void getBookInfo(bookInfo_t* pBi);
 void printBookInfo(bookInfo_t* pBi);
 

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
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 bookInfo_t book1;
  getBookInfo(&book1);
  printBookInfo(&book1);
}
