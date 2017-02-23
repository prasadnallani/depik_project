#include<stdio.h>

int main()
{
  char buff[100];  
  int ii;
  while(1)
  {
    __fpurge(stdin);
    fgets(buff, sizeof(buff), stdin);
    for(ii = 0; buff[ii] != '\n' ; ii++)
    {    
      if(buff[ii] >= 'a' && buff[ii] <= 'z')
       buff[ii] -= 32;
      else if(buff[ii] >= 'A' && buff[ii] <= 'Z')
       buff[ii] += 32;
    }
    puts(buff);
  }
}

