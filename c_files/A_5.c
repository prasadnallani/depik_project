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
  pr= (struct  record *)malloc(1);
  printf("Enter Id:");
  scanf("%d",&pr->id);
  printf("Enter name:");
  __fpurge(stdin);
  gets(pr->name);
  printf("Enter address :");
  __fpurge(stdin);
  gets(pr->addrs);
  printf("id=%d",pr->id);
  puts(pr->name);
  puts(pr->addrs);
  
 }
