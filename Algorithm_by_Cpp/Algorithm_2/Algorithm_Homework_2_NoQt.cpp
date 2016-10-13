
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
    if(a == b)  distance = MAX;
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
  Point** buffer;
  PairofPoint closestPair;

  void exchange(int i,int j);
  void exchbuffer(int i,int j);
  PairofPoint distance(int a,int b);
  //merge sort is to sort by x,the source is the List itself,sort list by x line before devide and conquer.
  void mergeCombine(int first,int middle,int last);
  void mergeSort(int first,int last);
  //quick sort is to sort by Y.when everytime we neet to combine the left part and right part,sort only (m-d,m+d) in another buffer,the list is still sort by X.
  void quickSort(int first,int last);
  int partition(int first,int last);

  PairofPoint exhaustiveMinDis();
  PairofPoint mergeDistance(int left,int right);
  PairofPoint combineMiddle(PairofPoint pp,double middle,int locMid);

public:
  Grid(int size);
  Grid();
  ~Grid();

  int getSize();
  PairofPoint getClosetPair();
  bool isXSorted();
  bool isYSorted(int bottom,int top);

  void sortX();
  void sortY(int a,int b);
  PairofPoint exhaustiveDistance();
  PairofPoint mergeDistance();

};

Grid::Grid(int size){
  srand(time(NULL));
  this->size = size;
  list = new Point* [size];
  buffer = new Point* [size];
  closestPair=PairofPoint();
  for(int i=0;i<size;i++){
    list[i]=new Point(i+1,(rand()%MAX+MIN),(rand()%MAX+MIN));
  }
}

Grid::Grid(){
  srand(time(NULL));
  size=0;
  closestPair=PairofPoint();
}

Grid::~Grid(){
  for(int i=0;i<size;i++){
    delete list[i];
  }
  delete[] list;
  delete[] buffer;
}

void Grid::exchange(int i,int j){
  Point* temp=list[i];
  list[i]=list[j];
  list[j]=temp;
}

void Grid::exchbuffer(int i,int j){
  Point* temp=buffer[i];
  buffer[i]=buffer[j];
  buffer[j]=temp;
}

int Grid::getSize(){
  return size;
}

PairofPoint Grid::getClosetPair(){
  return closestPair;
}

bool Grid::isXSorted(){//最后判断各个点的x坐标是否已经成功排序
  for(int i=1;i<size;i++){
    if( list[i-1]->x > list[i]->x ) return false;
  }
  return true;
}

bool Grid::isYSorted(int bottom,int top){
  for(int i=bottom;i<top;i++){
    if( buffer[i]->y > buffer[i+1]->y ) return false;
  }
  return true;
}


void Grid::mergeCombine(int first,int middle,int last){
  int i=first,j=middle+1,k=first;
  for(;i<=middle && j<=last;k++){
    if(list[i]->x <= list[j]->x)  buffer[k] = list[i++];
    else                    buffer[k] = list[j++];
  }
  while(i<=middle)  buffer[k++] = list[i++];
  while(j<=last)    buffer[k++] = list[j++];
  for(k=first;k<=last;k++)  list[k]=buffer[k];
}

void Grid::mergeSort(int first,int last){
  if(first < last){
    int middle = (first + last)/2;
    mergeSort(first,middle);
    mergeSort(middle+1,last);
    mergeCombine(first,middle,last);
  }
}

void Grid::quickSort(int first,int last){//过程中用于处理Y轴顺序
  if (first >= last)  return;//退出条件
  int key=partition(first,last);
  quickSort(first,key-1);
  quickSort(key+1,last);
}

int Grid::partition(int first,int last){
  int key=first;
  int i=first+1,j=last;
  while(1){
    while(buffer[key]->y>=buffer[i]->y && i<last) i++;
    while(buffer[key]->y<=buffer[j]->y && j>first) j--;
    if(i>=j)  break;
    exchbuffer(i,j);
  }
  exchbuffer(key,j);
  key=j;
  return key;
}


void Grid::sortX(){
  mergeSort(0,size-1);
}

void Grid::sortY(int a,int b){
  quickSort(a,b);
}

PairofPoint Grid::exhaustiveDistance(){
  for(int i=0;i<size-1;i++){
    for(int j=i;j<size;j++){
      closestPair=closer(closestPair,distance(i,j));
    }
  }
  return closestPair;
}

PairofPoint Grid::mergeDistance(){
  sortX();
  //if(isXSorted())  cout<<"sort complete"<<endl;
  closestPair=mergeDistance(0,size-1);
  return closestPair;
}

PairofPoint Grid::mergeDistance(int left,int right){
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
    minPair=combineMiddle(minPair,middle,locMid);
  }
  else{
    minPair=distance(0,0);
  }

  return minPair;
}

  PairofPoint Grid::combineMiddle(PairofPoint pp,double middle,int locMid){
    PairofPoint minPair=pp;
    int left,right,cursor;
    int limit;
    for(left=locMid-1;left>=0 && list[left]->x >= (middle-pp.distance);left--)    buffer[left]=list[left];
    for(right=locMid;right<size && list[right]->x <= (middle+pp.distance);right++)  buffer[right]=list[right];
    sortY(++left,locMid-1);
    sortY(locMid,--right);
    //left++;
    //right--;
    cursor=locMid;
    for(int i=left;i<locMid;i++){
      limit=0;
      for(int j=cursor;j<=right;j++){
        if (buffer[j]->y <= (buffer[i]->y+pp.distance) && (buffer[j]->y >= buffer[i]->y-pp.distance)){
          minPair=closer(minPair,distance(i,j));
          if(++limit == 6)  break;
        }
      }
    }
    /*for(int i=locMid;i>=0 && list[i]->x >= (mid-pp.distance);i--){
      for(int j=locMid;j<size && list[j]->x <= (mid+pp.distance);j++){
        if (list[j]->y <= (list[i]->y+pp.distance) && (list[j]->y >= list[i]->y-pp.distance)){
          minPair=closer(minPair,distance(i,j));
        }
      }
    }*/
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
  else          closestPair=g->exhaustiveDistance();
  tc.stop();
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  cout<<setprecision(3)<<tc.getTime()<<endl;
  cout<<"the pair of points is:<"<<setprecision(0)<<closestPair.a->x<<","<<closestPair.a->y<<">,<"<<closestPair.b->x<<","<<closestPair.b->y<<">"<<endl;
  cout<<"Cloest distance:"<<setprecision(3)<<closestPair.distance<<endl;
  return 0;
}
