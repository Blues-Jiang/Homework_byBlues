
#include <iostream>
using namespace std;

#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MAX 10000
#define MIN 0
//#define N 100
int counter=0;
int counter1=0;

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
  double x,y;
  int id;
  Point(){}
  Point(int id,double x,double y){
    this->id=id;
    this->x=x;
    this->y=y;
  }
  void setPoint(double x,double y){
    this->x=x;
    this->y=y;
  }
};

class PairofPoint{
public:
  double distance;
  Point *a,*b;
  PairofPoint(){
    distance = MAX;
    a=NULL;
    b=NULL;
  }
  PairofPoint(Point *a,Point *b){
    this->a=a;
    this->b=b;
    if(a == b)  distance = MAX*MAX;
    else distance=sqrt(pow(( a->x - b->x ),2) + pow(( a->y - b->y ),2));
  }
};

PairofPoint closer(PairofPoint a,PairofPoint b){
  if(a.distance<=b.distance)  return a;
  else                        return b;
}

class Grid{
private:
  int size;
  Point** list;
  int locA,locB;
  double minDis;
  void exchange(int i,int j);
  void quickSort(int first,int last);
  //void insertionSort(int first,int last);
  void sortY(int first,int last);
  int partition(int first,int last);
  PairofPoint middleCheck(PairofPoint pp,double mid,int locMid);
  PairofPoint mergeDistance(int left,int right);

public:
  Grid();
  Grid(int size);
  ~Grid();
  void sort();
  PairofPoint exhaustiveMinDis();
  PairofPoint mergeDistance();
  PairofPoint distance(int a,int b);

  int getSize();
  bool isXSorted();
};

Grid::Grid(int size){
  minDis=MAX;
  locA=size;
  locB=size;
  srand(time(NULL));
  this->size = size;
  list = new Point* [size];
  for(int i=0;i<size;i++){
    list[i]=new Point(i+1,(rand()%MAX+MIN),(rand()%MAX+MIN));
  }
}

Grid::Grid(){
  minDis=MAX;
  locA=size;
  locB=size;
  size=0;
}

void Grid::exchange(int i,int j){//数据互换
  Point* temp=list[i];
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
  for(int i=0;i<size;i++) delete list[i];
  delete[] list;
}

/*void Grid::insertionSort(int first,int last){
  for(int i=first+1;i<last;i++){
    Point* temp=list[i];
    int j;
    for(j=i-1;j>=0 && list[j]->x>temp->x;j--){
      list[j+1] = list[j];
    }
    list[j+1]=temp;
  }
}*/

void Grid::quickSort(int first,int last){//递归调用该函数
  if(first >= last)  return;//退出条件
  int key=partition(first,last);
  quickSort(first,key-1);
  quickSort(key+1,last);
  }

int Grid::partition(int first,int last){
  int key=first;
  int i=first+1,j=last;
  while(1){
    while(list[key]->x>=list[i]->x && i<last) i++;
    while(list[key]->x<=list[j]->x && j>first) j--;
    if(i>=j)  break;
    exchange(i,j);
  }
  exchange(key,j);
  key=j;
  return key;
}

void Grid::sort(){
    quickSort(0,size-1);
}

PairofPoint Grid::exhaustiveMinDis(){
  PairofPoint closestPair=PairofPoint(list[0],list[0]);
  for(int i=0;i<size-1;i++){
    for(int j=i;j<size;j++){
      closestPair=closer(closestPair,distance(i,j));
    }
  }
  return closestPair;
}

PairofPoint Grid::mergeDistance(){
  sort();
  if(isXSorted())  cout<<"sort complete"<<endl;
  return mergeDistance(0,size-1);
}

PairofPoint Grid::mergeDistance(int left,int right){
  //int locLA,locLB,locRA,locRB;

  PairofPoint minPair;
  PairofPoint minDL,minDR;
  if(right-left == 1){//2 points
    minPair=distance(left,right);

  }
  else if(right-left == 2){//3 points
    minPair=distance(left,right);
    if(distance(left,left+1).distance<minPair.distance)  minPair=distance(left,left+1);
    if(distance(right-1,right).distance<minPair.distance)  minPair=distance(right-1,right);

  }
  else if(right-left >= 3){//more than 3 points
    //double middle=(list[right]->x+list[left]->x)/2;
    //int locMid;
    int locMid=floor((right+left)/2);
    double middle=list[locMid]->x;
    //for(locMid=left;locMid<=right && list[locMid]->x < middle;locMid++);
    minDL=mergeDistance(left,locMid);
    minDR=mergeDistance(locMid+1,right);
    minPair=closer(minDL,minDR);
    minPair=middleCheck(minPair,middle,locMid);
  }
  else{
    minPair=distance(0,0);
  }

  return minPair;
}

  PairofPoint Grid::middleCheck(PairofPoint pp,double mid,int locMid){
    int limit;
    PairofPoint minPair=pp;
    for(int i=locMid;i>=0 && list[i]->x >= (mid-pp.distance);i--){
      limit=0;
      for(int j=locMid;limit<=6 && j<size && list[j]->x <= (mid+pp.distance);j++){
        if (list[j]->y <= (list[i]->y+pp.distance) && (list[j]->y >= list[i]->y-pp.distance)){
          minPair=closer(minPair,distance(i,j));
          limit++;
        }
      }
    }
    return minPair;
  }


PairofPoint Grid::distance(int a,int b){
  return PairofPoint(list[a],list[b]);
}

int main(int argc, char *argv[])
{
  int size;
  int way;
  PairofPoint closestPair;
  Grid* g;
  cout<<"Please input the size:";
  cin>>size;
  cout<<"Please input the way:";
  cin>>way;
  g=new Grid(size);
  tc.start();
  if(way != 0)  closestPair=g->mergeDistance();
  else          closestPair=g->exhaustiveMinDis();
  tc.stop();
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  cout<<setprecision(3)<<tc.getTime()<<endl;
  cout<<"the pair of points is:<"<<setprecision(0)<<closestPair.a->x<<","<<closestPair.a->y<<">,<"<<closestPair.b->x<<","<<closestPair.b->y<<">"<<endl;
  cout<<"Cloest distance:"<<setprecision(3)<<closestPair.distance<<endl;
  return 0;
}
