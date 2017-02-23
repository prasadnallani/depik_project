#include"config.h"
#include"osdef.h"
#include"osif.h"

void applicationStart()
{
//  addRoute("192.168.0.0","255.255.255.0","0.0.0.0",0,1);
//  ifConfig(1,"192.168.0.120");
  char *parms[] = { "ifConfig","1","192.168.0.100"};
//  addRoute ("192.168.2.0",  "255.255.255.0",  "0.0.0.0",  0,  1);
  ifConfig(3, parms);
}


