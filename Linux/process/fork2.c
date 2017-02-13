int main()
{
  printf("\nI am a process my process id is %d\n", getpid());
  printf("My parent's process id is       %d\n", getppid());
  printf("Now i am going to create a child process by calling fork\n\n");
  fork();
  printf("My PID : %d, My parent PID : %d\n",getpid(), getppid());
}

