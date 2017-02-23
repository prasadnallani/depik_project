#include"config.h"
#include"osdef.h"
#include"osif.h"

void applicationStart()
{
  char *parms[] = { "ifConfig","1","192.168.0.120"};
 // addRoute ("192.168.0.0",  "255.255.255.0",  "0.0.0.0",  0,  1);
  ifConfig(3,parms);//"192.168.0.120");
}


