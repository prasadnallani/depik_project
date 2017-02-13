#include<stdio.h>
#include<stdlib.h>
struct record
{
  int id;
  char name[20];
  char addrs[40];
 };
struct record *pr;
int main()
{
  int n,i,j;
  printf("enter no of students record\n");
  scanf("%d",&n);
  pr= (struct  record *) malloc(sizeof(struct record )*n);
  for(i=j=0;i<n;i++)
  {
    printf("Enter student no %d",++j);  
    printf("Enter Id:");
    scanf("%d",&pr->id);
    printf("Enter name:");
    __fpurge(stdin);
    gets(pr->name);
    printf("Enter address :");
    __fpurge(stdin);
    gets(pr->addrs);
  }
 for(i=j=0;i<n;i++)
  {
   printf("Enter student no %d\n",++j); 
   printf("id=%d\n",pr->id);
   puts(pr->name);
  // printf("\n");
   puts(pr->addrs);
//   printf("\n");
    }  
 }
