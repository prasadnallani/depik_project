int main()
{
  char *args[2];


  printf("I am going to exec an 'ls' program in current process\n");

  args[0] = "ls";
  args[1] = 0;
  execv("/bin/ls", args);

  printf("I execed 'ls' program\n");
}

