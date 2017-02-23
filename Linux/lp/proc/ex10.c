/*******************************************************************
			Operations on Terminals
**********************************************************************/

/********* Header Files *********/
#include<signal.h>
#include<stdio.h>
#include<termios.h>

/*********Global Variables*******/
 char ii, ch, passwd[100];
 struct termios cuTerm, prevTerm;

/********* Function prototypes *****/
void sigHandler(int sigNo);

/**********************************************************************
* Name	: main(void)
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
main(void)
{

 tcgetattr(0, &cuTerm);
 prevTerm = cuTerm;

 cuTerm. c_lflag &= ~ECHO;
 cuTerm. c_lflag &= ~ICANON;

 tcsetattr(0,TCSANOW, &cuTerm);

 if(signal(SIGINT, sigHandler) == SIG_ERR)
   printf("Can't catch signal SIGINT\n");
 if(signal(SIGQUIT, sigHandler) == SIG_ERR)
   printf("Can't catch signal SIGQUIT\n");

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

  if(!strcmp(passwd, "elico#123"))
    printf("Correct password\n");
  else
    printf("InCorrect password\n");
}
/**********************************************************************
* Name	: 
* Description :
* Inputs : none 
* outputs : none
*********************************************************************/
void sigHandler(int sigNo)
{
  if(sigNo == SIGINT || sigNo == SIGQUIT)
   printf("\nRecieved signal %d\n", sigNo);
   tcsetattr(0,TCSANOW, &prevTerm);
   exit(1);
}
    
