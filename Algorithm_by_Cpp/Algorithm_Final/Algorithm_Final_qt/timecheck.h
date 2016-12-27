#ifndef TIMECHECK_H
#define TIMECHECK_H

#include <iostream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>


class TimeCheck{
public:
  timeval startTime,endTime;//计时用结构体
  double takeTime;//记录的时间差

  void start();
  void stop();
  double getTime();
  void printTime();
} tc;

#endif // TIMECHECK_H
