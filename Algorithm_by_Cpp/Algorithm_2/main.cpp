#include "mainwindow.h"
#include <QApplication>
#include "qcustomplot.h"

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MAX 1000000
#define MIN 0
//#define N 100

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

class Point{
public:
  int x,y;
  Point(int x,int y){
    this->x=x;
    this->y=y;
  }
  void setPoint(int x,int y){
    this->x=x;
    this->y=y;
  }
};

class Grid{
private:
  int size;
  Point *list;
  void exchange(int i,int j);
  void quickSort(int first,int last);
  void insertionSort();

public:
  Grid();
  Grid(int size);
  ~Grid();
  void quickSort();

  int getSize();
  bool isXSorted();
};

Grid::Grid(int size){
  srand(time(NULL));
  this->size = size;
  list = new Point[size];
  for(int i=0;i<size;i++){
    list[i]=new Point((rand()%MAX+MIN),(rand()%MAX+MIN));
  }
}

Grid::Grid(){
  size=0;
}

void Grid::exchange(int i,int j){//数据互换
  Point temp=list[i];
  list[i]=list[j];
  list[j]=temp;
}

int Grid::getSize(){
  return size;
}

bool Grid::isXSorted(){//最后判断各个点的x坐标是否已经成功排序
  for(int i=1;i<size;i++){
    if( list[i-1]->x > list[i]->x ) return false;
  }
  return true;
}

Grid::~Grid(){
  for(int i=0;i<size;i++){
    delete list[i];
  }
  delete[] list;
}

Grid::sort(){

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
