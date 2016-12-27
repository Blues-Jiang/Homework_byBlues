#include "timecheck.h"

void TimeCheck::start(){
  gettimeofday(&startTime,NULL);//开始计时
}

void TimeCheck::stop(){
  gettimeofday(&endTime,NULL);//结束计时
}

double TimeCheck::getTime(){
  takeTime = 1000000*(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec);
  takeTime /= 1000;//单位为ms
  return takeTime;
}

void TimeCheck::printTime(){
  std::cout.setf(std::ios::fixed,std::ios::floatfield); //定点格式
  std::cout<<"Take time:"<<std::setprecision(3)<<getTime()<<"ms"<<std::endl;
}
