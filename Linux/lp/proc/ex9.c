/*******************************************************************
			Operations on Terminals
**********************************************************************/

/********* Header Files *********/
#include<signal.h>
#include<stdio.h>
#include<termios.h>

/*********Global Variables*******/
/********* Function prototypes *****/

/**********************************************************************
* Name	: main(void)
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
main(void)
{
 char ii, ch, passwd[100];
 struct termios cuTerm, prevTerm;

 tcgetattr(0, &cuTerm);
 prevTerm = cuTerm;

 cuTerm. c_lflag &= ~ECHO;
 cuTerm. c_lflag &= ~ICANON;

 tcsetattr(0,TCSANOW, &cuTerm);

 setbuf(stdin, NULL);
 setbuf(stdout, NULL);
 
  printf("Eneter Password\n");
  while((ch = getchar()) != '\n')
  {
    passwd[ii++] = ch;
    putchar('*');
  }
  passwd[ii++] = '\0';
  printf("\nYou entered = %s\n", passwd);

  tcsetattr(0,TCSANOW, &prevTerm);

  if(!strcmp(passwd, "venu#123"))
    printf("Correct password\n");
  else
    printf("InCorrect password\n");
}
  
