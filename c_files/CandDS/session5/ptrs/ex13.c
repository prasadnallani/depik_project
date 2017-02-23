#include<stdio.h>
typedef struct student
{ 
  char name[10];
  float id;
}studentInfo_t;

char *pc;
short *ps;
int *pi;
float *pf;
studentInfo_t *pst;


/***********************************************************************
* Name 	      : 
* Description : 
* Inputs      : 
* Output      : 
**********************************************************************/
main(void)
{
 pc = (char*)100;
 ps = (short*)100;
 pi = (int*)100;
 pf = (float*)100;
 pst = (studentInfo_t *)100;

 printf("addr of pc = %d\n",pc);
 printf("addr of ps = %d\n",ps);
 printf("addr of pi = %d\n",pi);
 printf("addr of pf = %d\n",pf);
 printf("addr of pst= %d\n",pst);

/*
 printf("content of pc= %d\n",*pc);
 printf("content of ps= %d\n",*ps);
 printf("content of pi= %d\n",*pi);
 printf("content of pf= %d\n",*pf);
 printf("content of pst= %d\n",*pst);
*/
 pc++;
 ps++;
 pi++;
 pf++;
 pst++;

 printf("addr of pc++ = %d\n",pc);
 printf("addr of ps++ = %d\n",ps);
 printf("addr of pi++ = %d\n",pi);
 printf("addr of pf++ = %d\n",pf);
 printf("addr of pst++= %d\n",pst);
/*
 printf("content of pc++= %d\n",*pc);
 printf("content of ps++= %d\n",*ps);
 printf("content of pi++= %d\n",*pi);
 printf("content of pf++= %d\n",*pf);
 printf("content of pst++= %d\n",*pst);
*/
 pc+=10;
 ps+=10;
 pi+=10;
 pf+=10;
 pst+=10;

 printf("addr of pc+10 = %d\n",pc);
 printf("addr of ps+10 = %d\n",ps);
 printf("addr of pi+10 = %d\n",pi);
 printf("addr of pf+10 = %d\n",pf);
 printf("addr of pst+10= %d\n",pst);
 printf("content of pc+10= %d\n",*pc);
 printf("content of ps+10= %d\n",*ps);
 printf("content of pi+10= %d\n",*pi);
 printf("content of pf+10= %d\n",*pf);
 printf("content of pst+10= %d\n",*pst);
}
