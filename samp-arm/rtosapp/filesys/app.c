/*******************************************************************************
 *
 * Copyright (C) 2004 Depik Technologies Pvt. Ltd All rights reserved
 *
 * The information and source code contained herein is the exclusive property
 * of Depik Technologies Pvt. Ltd and may not be disclosed, examined or 
 * reproduced in whole in part without the explicit written autherization 
 * from Depik Technologies.
 ******************************************************************************/
#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "usrcfg.h"
#include "fatfs.h"
#include "board.h"

int createFile( int argc, char *argv[]);

void applicationStart()
{
#ifdef NETWORK
  ifConfig(1,"192.168.0.201");
  addRoute("192.168.0.0", "255.255.255.0","0.0.0.0",0,1);
#endif
  shellRegCmd("crtf",createFile,"Creates file and writes string repeatedly");
}


testfile()
{
  int fd;

  fd = open("/ram0/abc.txt", O_RDWR|O_CREAT);
  if(fd < 0)
  {
    printf("Could not open file\n");
    return 1;
  }
  write(fd, "abcdefghijklmnopqrstuvwxyz\n",27);
  write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n",27);
  close(fd);
}

int createFile( int argc, char *argv[])
{
  int size;
  char path[64];
  int  slen, fd;

  if(argc != 4)
  {
    printf("Invalid arguments\n");
    printf("Usage: %s <fileName> <fileSize> <string>\n",argv[0]);
    return 1;
  }

  if( *argv[1] != '/' )
  {
    current_directory( path );
    strcpy( &path[strlen(path)], argv[1]);
  }
  else
    strcpy( path, argv[1]);
  
  slen = strlen(argv[3]);

  fd = open( path, O_RDWR | O_CREAT );
  
  if( fd < 0)
  {
    printf("[Warn] Unable open file %s\r\n", path);	  
  }
 
  size = atoi(argv[2]); 

  while( size )
  {
    if( size < slen )
      slen = size;
    
    if(write( fd, argv[3], slen) <= 0)
    {
      break;
    }

    size -= slen;
  }
  
  close (fd);
  printf( " Writing file was successfull \r\n" );
}

