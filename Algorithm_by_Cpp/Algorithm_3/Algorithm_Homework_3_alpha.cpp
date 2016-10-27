#include <iostream>
using namespace std;

#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define CHESSSIZE 8


class TimeCheck{
public:
  timeval startTime,endTime;//计时用结构体
  double takeTime;//记录的时间差

  void start(){
    gettimeofday(&startTime,NULL);//开始计时
  }
  void stop(){
    gettimeofday(&endTime,NULL);//结束计时

  }
  double getTime(){
    takeTime = 1000000*(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec);
    takeTime /= 1000;//单位为ms
    return takeTime;
  }
} tc;

class QueenChess{
private:
  int size;
  int* queenlist;//queenlist[0] is the number of chess already on board,chess list from 1 to size,the point is x,value is y
  bool isSafe(int x,int y);


public:
  QueenChess();
  QueenChess(int size);
  ~QueenChess();
  bool isSucceed();

};

QueenChess::QueenChess(){
  size = 8;
  queenlist = new int[size+1];
}

QueenChess::QueenChess(int size){
  this->size = size;

}

QueenChess::~QueenChess(){
  delete[] queenlist;
}

bool QueenChess::isSafe(int x,int y){

}

int main(int argc, char *argv[])
{


  return 0;
}
