#include <iostream>
using namespace std;
#include <queue>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define MAX 100000
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
  Point** listY;
  //Point** buffer;
  //Point **listL,**listR;
  PairofPoint closestPair;

  void exchange(int i,int j);
  void exchange(int i,int j,Point** a);
  PairofPoint distance(Point* a,Point* b);
  //merge sort is to sort by x,the source is the List itself,sort list by x line before devide and conquer.
  void mergeCombine(int first,int middle,int last,Point** buffer,bool xory);//TRUE->X FALSE->Y
  void mergeSort(int first,int last,Point** buffer,bool xory);
  //quick sort is to sort by Y.when everytime we neet to combine the left part and right part,sort only (m-d,m+d) in another buffer,the list is still sort by X.
  //void quickSort(int first,int last);
  //int partition(int first,int last);

  PairofPoint exhaustiveMinDis();
  PairofPoint mergeDistance(int left,int right, Point** buffer);
  PairofPoint combineMiddle(PairofPoint pp,double middle,int locMid,int left,int right,Point** buffer);

public:
  Grid(int size);
  Grid();
  ~Grid();

  int getSize();
  PairofPoint getClosetPair();
  bool isXSorted();
  bool isYSorted(int bottom,int top);

  void sortX();
  void sortY();
  PairofPoint exhaustiveDistance();
  PairofPoint mergeDistance();
};

Grid::Grid(int size){
  srand(time(NULL));
  this->size = size;
  list = new Point* [size];
  listY = new Point* [size];
  //buffer = new Point* [size];
  //listL = new Point* [size];
  //listR = new Point* [size];
  closestPair=PairofPoint();
  for(int i=0;i<size;i++){
    list[i]=new Point(i+1,(rand()%MAX+MIN),(rand()%MAX+MIN));
    //listY[i]=list[i];
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
  delete[] listY;
  //delete[] listL;
  //delete[] listR;
}

void Grid::exchange(int i,int j){
  Point* temp=list[i];
  list[i]=list[j];
  list[j]=temp;
}

void Grid::exchange(int i,int j,Point** a){
  Point* temp=a[i];
  a[i]=a[j];
  a[j]=temp;
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
    if( listY[i]->y > listY[i+1]->y ) return false;
  }
  return true;
}


void Grid::mergeCombine(int first,int middle,int last,Point** buffer,bool xory){

  int i=first,j=middle+1,k=first;
  if (xory) {
    for(;i<=middle && j<=last;k++){
      if(list[i]->x <= list[j]->x)  buffer[k] = list[i++];
      else                    buffer[k] = list[j++];
    }
    while(i<=middle)  buffer[k++] = list[i++];
    while(j<=last)    buffer[k++] = list[j++];
    for(k=first;k<=last;k++)  list[k]=buffer[k];

  }
  else{
    for(;i<=middle && j<=last;k++){
      if(listY[i]->y <= listY[j]->y)  buffer[k] = listY[i++];
      else                    buffer[k] = listY[j++];
    }
    while(i<=middle)  buffer[k++] = listY[i++];
    while(j<=last)    buffer[k++] = listY[j++];
    for(k=first;k<=last;k++)  listY[k]=buffer[k];

  }
}


void Grid::mergeSort(int first,int last,Point** buffer,bool xory){
  if(first < last){
    int middle = (first + last)/2;
    mergeSort(first,middle,buffer,xory);
    mergeSort(middle+1,last,buffer,xory);
    mergeCombine(first,middle,last,buffer,xory);
  }
}

void Grid::sortX(){
  Point** buffer=new Point*[size];
  mergeSort(0,size-1,buffer,true);
  delete[] buffer;
}

void Grid::sortY(){
  Point** buffer=new Point*[size];
  mergeSort(0,size-1,buffer,false);
  delete[] buffer;
}

/*airofPoint Grid::exhaustiveDistance(){
  for(int i=0;i<size-1;i++){
    for(int j=i;j<size;j++){
      closestPair=closer(closestPair,distance(i,j));
    }
  }
  return closestPair;
}*/

PairofPoint Grid::exhaustiveDistance(){
  sortX();
  for(int i=0;i<size-1;i++){
    for(int j=i;j<size;j++){
      if(list[j]->x-list[i]->x > closestPair.distance)  break;
      closestPair=closer(closestPair,distance(list[i],list[j]));
    }
  }
  return closestPair;
}


PairofPoint Grid::mergeDistance(){
  sortX();
  Point** buffer=new Point*[size];
  //sortY();
  for(int i=0;i<size;i++) listY[i]=list[i];
  //if(isXSorted())  cout<<"sort complete"<<endl;
  closestPair=mergeDistance(0,size-1,buffer);
  delete[] buffer;
  return closestPair;
}

PairofPoint Grid::mergeDistance(int left,int right,Point** buffer){

  PairofPoint minPair;

  if(right-left == 1){//2 points
    minPair=distance(list[left],list[right]);
    if(listY[left]->y>listY[right]->y)  exchange(left,right,listY);
  }
  /*else if(right-left == 2){//3 points
    minPair=distance(list[left],list[right]);
    if(distance(list[left],list[left+1]).distance<minPair.distance)  minPair=distance(list[left],list[left+1]);
    if(distance(list[right-1],list[right]).distance<minPair.distance)  minPair=distance(list[right-1],list[right]);
  }*/
  else if(right-left >= 2){//more than 2 points
    PairofPoint minDL,minDR;
    //double middle=(list[right]->x+list[left]->x)/2;
    int locMid=(left +right) /2;
    double middle=list[locMid]->x;
    //for(locMid=left;locMid<=right && list[locMid]->x < middle;locMid++);
    minDL=mergeDistance(left,locMid-1,buffer);
    minDR=mergeDistance(locMid,right,buffer);
    minPair=closer(minDL,minDR);
    minPair=combineMiddle(minPair,middle,locMid,left,right,buffer);
  }
  else{
    minPair=distance(0,0);
  }
  return minPair;
}

  PairofPoint Grid::combineMiddle(PairofPoint pp,double middle,int locMid,int left,int right,Point** buffer){
    Point **listL,**listR;

    //queue<Point*> listL;
    int l=0,r=0;
    PairofPoint minPair=pp;
    int limit;
    listR=new Point*[right-locMid+5];
    listL=new Point*[locMid-left+5];
    for(int i=left;i<locMid;i++){
      if(listY[i]->x >= middle-minPair.distance)  listL[l++]=listY[i];
    }
    for(int i=locMid;i<=right;i++){
      if(listY[i]->x <= middle+minPair.distance)  listR[r++]=listY[i];
    }
    for(int i=0;i<l;i++){
      limit=0;
      for(int j=0;j<r;j++){
        if(listR[j]->y > listL[i]->y+pp.distance)  break;
        minPair=closer(minPair,distance(listL[i],listR[j]));
        if(++limit == 6)  break;
      }
    }
    delete[] listR;
    delete[] listL;
    mergeCombine(left,locMid-1,right,buffer,false);
    /*while(listL.size() != 0){
      limit=0;
      for(int j=0;j<r;j++){
        if(listR[j]->y > listL.front()->y+pp.distance)  break;
        minPair=closer(minPair,distance(listL.front(),listR[j]));
        if(++limit == 6)  break;
      }
      listL.pop();
    }
      delete[] listR;
      mergeCombine(left,locMid-1,right,buffer,false);*/
    /*for(int i=locMid;i>=0 && list[i]->x >= (middle-pp.distance);i--){
      limit=0;
      for(int j=locMid;j<size && list[j]->x <= (middle+pp.distance);j++){
        if (list[j]->y <= (list[i]->y+pp.distance) && (list[j]->y >= list[i]->y-pp.distance)){
          minPair=closer(minPair,distance(i,j));
          if(++limit == 6) break;
        }
      }
    }*/
    return minPair;
  }


PairofPoint Grid::distance(Point* a,Point* b){
  return PairofPoint(a,b);
}


int main(int argc, char *argv[])
{
  int size;
  int way;
  PairofPoint closestPair;
  Grid* g;
  cout<<"Please input the size:";
  cin>>size;
  //cout<<"Please input the way:";
  //cin>>way;
  g=new Grid(size);
  tc.start();
  closestPair=g->mergeDistance();

  tc.stop();
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  cout<<"Take time:"<<setprecision(3)<<tc.getTime()<<endl;
  cout<<"the pair of points is:<"<<setprecision(0)<<closestPair.a->x<<","<<closestPair.a->y<<">,<"<<closestPair.b->x<<","<<closestPair.b->y<<">"<<endl;
  cout<<"Cloest distance:"<<setprecision(3)<<closestPair.distance<<endl;
  tc.start();
  closestPair=g->exhaustiveDistance();

  tc.stop();
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  cout<<"Take time:"<<setprecision(3)<<tc.getTime()<<endl;
  cout<<"the pair of points is:<"<<setprecision(0)<<closestPair.a->x<<","<<closestPair.a->y<<">,<"<<closestPair.b->x<<","<<closestPair.b->y<<">"<<endl;
  cout<<"Cloest distance:"<<setprecision(3)<<closestPair.distance<<endl;

  return 0;
}
