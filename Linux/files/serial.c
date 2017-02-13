#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>

/*******************************************************************************
* Name:
* Description:
*******************************************************************************/
int serial_init()
{
  int sfd;
  struct termios tio;

  sfd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);

  if(sfd < 0)
  {
    perror("Unable to open /dev/ttyS0");
    exit(1);
  }
 
  tcgetattr(sfd, &tio); 
  tio.c_cflag        = B19200 | CS8 | CLOCAL | CREAD;
  tio.c_iflag        = 0;
  tio.c_oflag        = 0;
  tio.c_lflag        = 0; 
  tcflush(sfd, TCIFLUSH);
  tcsetattr(sfd,TCSANOW,&tio);
 
  return sfd;
}

int main()
{
  int sfd,n;
  char buf[128];

  sfd = serial_init();
  while(1)
  {
    n = read(sfd,buf,128);
    if(n<0)
    {
      exit(2);
    }
    buf[n] = 0;
    printf("%s",buf);
  }
}


