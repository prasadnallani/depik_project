int main()
{
  while(1)
  {
    sleep(2);
     printf("\n i am a process,my process id is %d\n",getpid());
    printf("My parent's process id is %d\n\n",getppid());
  }
}

