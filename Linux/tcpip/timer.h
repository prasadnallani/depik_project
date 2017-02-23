#ifndef __TIMER_H_
#define __TIMER_H_

#include "config.h"
#include "osdef.h"
#include "osif.h"
#include "pktbuf.h"
#include "nwstk.h"

typedef struct alarm_s
{
  INT32    tmOutInMilliSecs;
  INT32    startTick;
  void     (*fp)(void *arg);
  void     *arg;
  struct   alarm_s *pnxt;
  struct   alarm_s *pprv;

}alarm_t;


void alarmTask();

#define      UNSUCCESS     1
#endif
