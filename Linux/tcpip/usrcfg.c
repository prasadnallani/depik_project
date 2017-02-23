/********************************************************************** 
*This program to create initialise OS and to create mainTsk  
***********************************************************************/

#include "config.h"
#include "osdef.h"
#include "osif.h"

extern char _end,_edata;
char serDevName[] = "/dev/ttyS0";
unsigned char *bssStart =&_edata;
unsigned char *bssEnd = &_end;

void usrRoot()
{
  int arg, irq = 4;
  unsigned int baseaddr = 0x3f8;
  int serDrvNum;

  /** Initialize the I/O Subsystem **/
  iosysInit();

  /** Install the serial driver **/
  serDrvNum = serDrv();
  serDevCreate(irq,baseaddr,serDevName,serDrvNum);

/**Open serial for standard input,standard output and standard error **/
  open(serDevName,0);
  open(serDevName,1);
  open(serDevName,2);

  /** Display the kernel banner **/
  dispBanner();

  /** Create shell task **/
  taskSpawn("shellTask",10,0,0x4000,shellTask,0,0,0,0,0,0,0,0,0,0);

  /** Invoke the application starting function **/
  simnetInit();
  applicationStart();
}

usrInit()
{
  /**** Initialize the BSS section to zero ***/
  while(bssStart <= bssEnd)
    *bssStart++ = 0;

  initOs(usrRoot,1,0x1000,0);
}

