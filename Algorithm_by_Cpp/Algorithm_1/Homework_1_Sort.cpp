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

timeval startTime,endTime;//计时用结构体
double takeTime;//记录的时间差

class Sort{
private:
    int size;
    int *list;
    void exch(int i,int j);
    void mergeList(int first,int middle,int last,int* buffer);
    void mergeSort(int first,int last,int* buffer);
    void quickSort(int first,int last);
    int partition(int first,int last);

public:
    Sort();
    Sort(int size);
    ~Sort();

    void initial(int size);
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void mergeSort();
    void quickSort();

    int getSize();
    bool isSorted();
};


Sort::Sort(int size){
  srand(time(NULL));
  this->size = size;
  list = new int[size];
  for(int i=0;i<size;i++){
    list[i]=rand() % MAX + MIN;
  }
}

Sort::Sort(){
  size=0;
}

void Sort::initial(int size){
  delete[] list;
  this->size = size;
  list = new int[size];
  for(int i=0;i<size;i++){
    list[i]=rand() % MAX + MIN;
  }}

void Sort::exch(int i,int j){//数据互换
  int temp=list[i];
  list[i]=list[j];
  list[j]=temp;
}

int Sort::getSize(){
  return size;
}

bool Sort::isSorted(){//最后判断是否已经成功排序
  for(int i=1;i<size;i++){
    if( list[i-1] > list[i] ) return false;
  }
  return true;
}

Sort::~Sort(){
  delete[] list;
}

void Sort::bubbleSort(){
  for(int i=size-1;i>=0;i--){
    for(int j=0;j<i;j++){
      if(list[j]>list[j+1]) exch(j,j+1);
    }
  }
}

void Sort::selectionSort(){
  for(int i=0;i<size;i++){
    int min = i;
    for(int j=i+1;j<size;j++){
      if(list[j]<list[min]) min=j;
    }
    exch(min,i);
  }
}

void Sort::insertionSort(){
  for(int i=1;i<size;i++){
    int temp=list[i],j;
    for(j=i-1;j>=0 && list[j]>temp;j--){
      list[j+1] = list[j];
    }
    list[j+1]=temp;
  }
}

void Sort::mergeSort(){//归并排序入口
  int *buffer=new int[size];//生成一个等大的空间供其交换，可优化
  mergeSort(0,size-1,buffer);
  delete[] buffer;
}

void Sort::mergeList(int first,int middle,int last,int* buffer){
  int i=first,j=middle+1,k=first;
  for(;i<=middle && j<=last;k++){//选择合适的项进行对换
    if(list[i] <= list[j])  buffer[k] = list[i++];
    else                    buffer[k] = list[j++];
  }
  while(i<=middle)  buffer[k++] = list[i++];
  while(j<=last)    buffer[k++] = list[j++];
  for(k=first;k<=last;k++)  list[k]=buffer[k];
}

void Sort::mergeSort(int first,int last,int* buffer){
  if(first < last){
    int middle = (first + last)/2;
    mergeSort(first,middle,buffer);
    mergeSort(middle+1,last,buffer);
    mergeList(first,middle,last,buffer);
  }
}

void Sort::quickSort(){//快速排序函数入口
  quickSort(0,size-1);
}

void Sort::quickSort(int first,int last){//递归调用该函数
  if (first >= last)  return;//退出条件
  int key=partition(first,last);
  quickSort(first,key-1);
  quickSort(key+1,last);
}

int Sort::partition(int first,int last){
  int key=first;
  int i=first+1,j=last;
  while(1){
    while(list[key]>=list[i] && i<last) i++;
    while(list[key]<=list[j] && j>first) j--;
    if(i>=j)  break;
    exch(i,j);
  }
  exch(key,j);
  key=j;
  return key;
}

int main(int argc,char* argv[]) {
  int sortWay=1,size=10;

  if(argc == 3){//main way size <-输入顺序
    switch (argv[1][0]) {//选择对应的排序方法
      case 'b':case 'B': sortWay = 1;  break;
      case 's':case 'S': sortWay = 2;  break;
      case 'i':case 'I': sortWay = 3;  break;
      case 'm':case 'M': sortWay = 4;  break;
      case 'q':case 'Q': sortWay = 5;  break;
    }

    switch (argv[2][0]) {
      case '1': size = 10;  break;
      case '2': size = 100;  break;
      case '3': size = 1000;  break;
      case '4': size = 10000;  break;
      case '5': size = 100000;  break;
	  case '6': size = 200000;  break;
	  case '7': size = 400000;  break;
	  case '8': size = 600000;  break;
	  case '9': size = 800000;  break;
    }
  }
  else{
    cout<<"b -> bubble sort"<<endl;
    cout<<"s -> selection sort"<<endl;
    cout<<"i -> insertion sort"<<endl;
    cout<<"m -> merge sort"<<endl;
    cout<<"q -> quick sort"<<endl;
    cout<<"please choose the way to sort:";
    cin>>sortWay;
    cout<<"please input the size of numbers:";
    cin>>size;
  }
  Sort *x=new Sort(size);

  gettimeofday(&startTime,NULL);//开始计时
  switch(sortWay){//进行计时的排序算法
    case 1: x->bubbleSort();    break;
    case 2: x->selectionSort(); break;
    case 3: x->insertionSort(); break;
    case 4: x->mergeSort();     break;
    case 5: x->quickSort();     break;
  }

  gettimeofday(&endTime,NULL);//结束计时
  takeTime = 1000000*(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec);
  takeTime /= 1000;//单位为ms
  switch(sortWay){//输出
    case 1: cout<<"bubbleSort "<<"size:"<<size<<" Time:";    break;
    case 2: cout<<"selectionSort "<<"size:"<<size<<" Time:"; break;
    case 3: cout<<"insertionSort "<<"size:"<<size<<" Time:"; break;
    case 4: cout<<"mergeSort "<<"size:"<<size<<" Time:";     break;
    case 5: cout<<"quickSort "<<"size:"<<size<<" Time:";     break;
  }
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  if(x->isSorted())  cout<<setprecision(3)<<takeTime<<endl;
  else  cout<<"ERROR"<<endl;
  return 0;
}
