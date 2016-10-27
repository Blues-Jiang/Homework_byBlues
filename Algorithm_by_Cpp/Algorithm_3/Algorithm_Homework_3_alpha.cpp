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
  int** chessboard;
  int* queenlist;
  bool isSafe(int x,int y);


public:
  QueenChess();
  QueenChess(int size);
  ~QueenChess();
  bool isSucceed();

};

QueenChess::QueenChess(){
  size = 8;
  chessboard = new int*[size];
  for(int i=0;i<size;i++){
    chessboard[i] = new int[size];
    for(int j=0;j<size;j++){
      chessboard[i][j] = 0;
    }
  }
}

QueenChess::QueenChess(int size){
  this->size = size;
  chessboard = new int*[this->size];
  for(int i=0;i<this->size;i++){
    chessboard[i] = new int[this->size];
    for(int j=0;j<this->size;j++){
      chessboard[i][j] = 0;
    }
  }
}

QueenChess::~QueenChess(){
  for(int i=0;i<size;i++){
    delete[] chessboard[i];
  }
  delete[] chessboard;
}

bool QueenChess::isSafe(int x,int y){

}

int main(int argc, char *argv[])
{


  return 0;
}
