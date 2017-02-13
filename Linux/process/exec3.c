int main()
{
  printf("I am going to exec an 'ls' program in current process\n");
//  execlp("ls","ls",0);
  execlp("./fork2","./fork2",0);
  printf("I execed 'ls' program\n");
}

