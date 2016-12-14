#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#define MAX 99

int size = 6;
int **C,**F;

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
  C = new int*[size];
  F = new int*[size];
  for(int i=0;i<size;i++){
    C[i] = new int[size];
    F[i] = new int[size];
  }
  for(int i=0;i<size;i++){
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
}


int main(int argc, char *argv[])
{
  HuffmanTree ht=HuffmanTree();

  tc.start();
    //ht.Compression();
  tc.stop();
  cout<<"Compression complete."<<endl;
  tc.printTime();
  tc.start();
    //ht.Decompression();
  tc.stop();
  cout<<"Decompression complete."<<endl;
  tc.printTime();

  deleteAll();
  return 0;
}
