#include <iostream>
using namespace std;

#include <iomanip>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define CHESSSIZE 8

QueenChess* initialChess();

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
  bool findASolusion();
  bool findNextSolusion();
  bool findFromRest();
  void clearAll();
  void printCmd();
  bool setChess(int x,int y);
};

QueenChess::QueenChess(){
  size = 8;
  queenlist = new int[size+1];
  queenlist[0] = 0;
  for(int i=1;i<=size;i++)  queenlist[i] = 0;
}

QueenChess::QueenChess(int size){
  this->size = size;
  queenlist = new int[size+1];
  queenlist[0] = 0;
  for(int i=1;i<=size;i++)  queenlist[i] = 0;

}

QueenChess::~QueenChess(){
  delete[] queenlist;
}

bool QueenChess::isSafe(int x,int y){
  if( x>size || x<1 || y>size || y<1 )  return false;
  for(int i=1;i<=size;i++){
    if(i == x || queenlist[i] == 0) continue;
    if(queenlist[i] == y) return false;
    if((y-x) == (queenlist[i]-i)) return false;
    if((y+x) == (queenlist[i]+i)) return false;
  }
  return true;
}

bool QueenChess::isSucceed(){
  queenlist[0] = 0;
  for(int i=1;i<=size;i++){
    if(queenlist[i] != 0){
      if(isSafe(i,queenlist[i]))  queenlist[0]++;
      else                        return false;
    }
  }
  return true;
}

void QueenChess::clearAll(){
  for(int i=0;i<=size;i++){
    queenlist[i] = 0;
  }
}

bool QueenChess::findASolusion(){
  int x,y;
  do{
    x=queenlist[0]+1;
    y=queenlist[x]+1;
    if(isSafe(x,y)){
      queenlist[0]++;
      queenlist[x]=y;
    }
    else if(y == size){
      queenlist[0]--;
      queenlist[x] = 0;
    }
    else{
      queenlist[x]++;
    }
  }while(queenlist[0] > 0 || queenlist[0] < size);

  if(queenlist[0] == 0) return false;
  else                  return true;
  }

bool QueenChess::findNextSolusion(){
  int x,y;
  queenlist[queenlist[0]] = 0;
  queenlist[0]--;
  do{
    x=queenlist[0]+1;
    y=queenlist[x]+1;
    if(isSafe(x,y)){
      queenlist[0]++;
      queenlist[x]=y;
    }
    else if(y == size){
      queenlist[0]--;
      queenlist[x] = 0;
    }
    else{
      queenlist[x]++;
    }
  }while(queenlist[0] > 0 || queenlist[0] < size);

  if(queenlist[0] == 0) return false;
  else                  return true;
}

bool QueenChess::findFromRest(){
    vector<int> vx;
    int vxaddr=0;
    int x,y;
    for(int i=size;i>0;i--){
      if(queenlist[i] == 0) vx.push_back(i);
    }

    do{
      x=vx[vxaddr];
      y=queenlist[x]+1;
      if(isSafe(x,y)){
        vxaddr++;
        queenlist[x]=y;
      }
      else if(y == size){
        vxaddr--;
        queenlist[x] = 0;
      }
      else{
        queenlist[x]++;
      }
    }while(vxaddr >= 0 || vxaddr < vx.size());

    if(isSucceed()) return true;
    else            return false;
}

void QueenChess::printCmd(){
  cout<<"**********Result of "<<size<<" queens puzzle**********"<<endl;
  for(int i=1;i<=size;i++){
    for(int j=1;j<=size;j++){
      if(j == queenlist[i]) cout<<"# ";
      else                  cout<<"* ";
    }
    cout<<endl;
    cout<<endl;
  }
}

bool QueenChess::setChess(int x,int y){
  if( x>size || x<1 || y>size || y<1 )  return false;
  if( queenlist[x] != 0 ) return false;
  queenlist[x]=y;
  queenlist[0]++;
  return true;
}

QueenChess* initialChess(){
  int size,x,y;
  cout<<"Size of queen";
  cin<<size;
  QueenChess qc = new QueenChess(size);
  cout<<"Please input the coordinate of queen(input 0 to interrupt):";
  for(int i=1;i<=size;i++){
    cin<<x<<y;
    if(x == 0 || y == 0) break;
    if(!qc.setChess(x,y)) cout<<"The coordinate of queen ("<<x<<","<<y") is obey the rules,ignore this queen.";
  }
  cout<<"Initial succeed";
  return qc;
}

int main(int argc, char *argv[])
{
  QueenChess* chessboard=initialChess();
  

  return 0;
}
