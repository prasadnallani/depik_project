#include<stdio.h>
#include<termios.h>
#include<fcntl.h>

int getPasswd(char *passwd)
{
  int ii=0;
  struct termios cuset,newset;
  char ch;
  /***Disable echo and canonical mode of processing***/
  tcgetattr(0,&cuset); //here 0 is stdio terminal
  newset=cuset;
  newset.c_lflag &=~ICANON;
  newset.c_lflag &=~ECHO;
  tcsetattr(0,TCSANOW,&newset); 

  setbuf(stdin,NULL);  //here NULL Takes there is no buffer,
  setbuf(stdout,NULL);
  while((ch=getchar()) !='\n')
  {
    passwd[ii++]= ch;
    putchar('*');
  }
  passwd[ii++]=0;
  putchar('\n');

  tcsetattr(0,TCSANOW,&cuset);
}
int main()
{
  char pw[20];
  printf("Enter password :  ");
  getPasswd(pw);
  printf("your password is %s\n",pw);
}

