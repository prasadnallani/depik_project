//if DEBUG is defined then only the message Hru Bob is printed 
//#include<stdio.h>
#define DEBUG 0

int main()
{
  printf("hellow\n");
 
  #ifdef DEBUG
    printf("Hru Bob\n");
  #endif
  if(DEBUG)
    printf("I am fine\n");

}
 
