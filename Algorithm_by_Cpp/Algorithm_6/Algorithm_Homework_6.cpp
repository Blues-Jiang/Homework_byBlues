#include <iostream>
#include <fstream>
using namespace std;
#include <queue>
#include <vector>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#define MAX 99

int size = 6;
int maxFlow;
int **C,**F;
bool *isChecked;
queue<int> preQueue;
queue<int> addRoad;

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
  void printTime(){
    cout.setf(ios::fixed,ios::floatfield); //定点格式
    cout<<"Take time:"<<setprecision(3)<<getTime()<<"ms"<<endl;
  }
} tc;

void initial(){
  maxFlow = 0;
  C = new int*[size];
  F = new int*[size];
  isChecked = new bool[size];
  for(int i=0;i<size;i++){
    C[i] = new int[size];
    F[i] = new int[size];
  }
  for(int i=0;i<size;i++){
    isChecked[i]=false;
    for(int j=0;j<size;j++){
      C[i][j]=0;
      F[i][j]=0;
    }
  }
}


void input(){
  int x,y,weight;
  do{
    cin>>x>>y>>weight;
    C[x][y] = weight;
  }while(x != 0 && y != 0);
}

void deleteAll(){
  for(int i=0;i<size;i++){
      delete[] C[i];
      delete[] F[i];
  }
  delete[] C;
  delete[] F;
  delete[] isChecked;
  while(!preQueue.empty())  preQueue.pop();
  while(!addRoad.empty())  addRoad.pop();
}

void Ford_Fulkerson(){

}

int main(int argc, char *argv[])
{
  HuffmanTree ht=HuffmanTree();

  tc.start();
    //ht.Compression();
  tc.stop();

  deleteAll();
  return 0;
}
