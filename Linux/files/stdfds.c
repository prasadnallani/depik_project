int main()
{
  char buf[80];
  int n;

  write(1, "This is written to fd number 1\n",31);
  write(2, "This is written to fd number 2\n",31);
  write(1, "Enter a line of text\n",21);
  n = read(0, buf, 80);
  write(1, "Following is the line i read\n",29);
  write(1,buf,n);
}

