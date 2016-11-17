#include <iostream>
using namespace std;
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <time.h>
#include <sys/time.h>
#define MAX 99

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

class bag{
private:
  class good{
  public:
    int weight;
    int value;
    good(){weight=0;value=0;}
    good(int w,int v){weight=w;value=v;}
  };

  good **goodList;
  int **table;
  int sumWeight;
  int size;

public:
  stack<int> result;
  bag(){}
  bag(int n,int W);
  ~bag();
  void DP();
  void findResult();
  void printList();
  void printValueTable();
  void printResult();
};

bag::bag(int n,int W){
  srand(time(NULL));
  sumWeight = W;
  size = n;
  goodList = new good*[size+1];
  for(int i=0;i<size;i++){
    goodList[i] = new good(rand()%sumWeight+1,rand()%MAX+1);
  }
  table = new int*[size];
  for(int i=0;i<size;i++){
    table[i]=new int[sumWeight+1];
  }
}

bag::~bag(){
  for(int i=0;i<size;i++){
    delete[] table[i];
    delete  goodList[i];
  }
  delete[] table;
  delete[] goodList;
}

void bag::DP(){
  for(int i=0;i<size;i++){
    table[i][0]=0;
  }
  for(int i=0;i<size;i++){
    for(int w=1;w<=sumWeight;w++){
      if(goodList[i]->weight > w){
        table[i][w] = (i!=0)?table[i-1][w]:0;
      }
      else{
        if(i==0)  table[i][w] = goodList[i]->value;
        else if( table[i-1][w] > (table[i-1][w-goodList[i]->weight]+goodList[i]->value) ){
          table[i][w] = table[i-1][w];
        }
        else{
          table[i][w] = table[i-1][w-goodList[i]->weight]+goodList[i]->value;
        }
      }
    }
  }
}

void bag::findResult(){
  for(int i=size-1,w=sumWeight;i>=0;i--){
    if(i == 0){
       if(table[i][w] > 0) result.push(i);
    }
    else if(table[i][w] == table[i-1][w-goodList[i]->weight] + goodList[i]->value){
        result.push(i);
        w -= goodList[i]->weight;
    }
  }
}

void bag::printList(){
    cout<<left<<setw(8)<<"No."<<left<<setw(8)<<"Weight"<<left<<setw(8)<<"Value"<<endl;
    for(int i=0;i<size;i++){
      //cout<<left<<setw(8)<<(char)(i+65)<<left<<setw(8)<<goodList[i]->weight<<left<<setw(8)<<goodList[i]->value<<endl;
      cout<<left<<setw(8)<<(i+1)<<left<<setw(8)<<goodList[i]->weight<<left<<setw(8)<<goodList[i]->value<<endl;
    }
}

void bag::printValueTable(){
  cout<<left<<setw(4)<<"n\\w";
  for(int i=0;i<=sumWeight;i++) cout<<left<<setw(4)<<i;
  cout<<endl;
  for(int i=0;i<size;i++){
    cout<<left<<setw(4)<<(i+1);
    for(int j=0;j<=sumWeight;j++) cout<<left<<setw(4)<<table[i][j];
    cout<<endl;
  }
}

void bag::printResult(){
  cout<<"Result:";
  while(1){
    //char temp=result.top() + 65;
    int temp=result.top() + 1;
    result.pop();
    cout<<temp;
    if(result.empty()){
      cout<<endl;
      break;
    }
    else  cout<<',';
  }
}

int main(int argc, char *argv[])
{
  int w,n;
  cout<<"Please input the max weight of bag:";
  cin>>w;
  cout<<"Please input the number of goods:";
  cin>>n;
  bag x=bag(n,w);
  tc.start();
    x.DP();
    x.findResult();
  tc.stop();
  cout.setf(ios::fixed,ios::floatfield); //定点格式
  cout<<"Take time:"<<setprecision(3)<<tc.getTime()<<endl;

  x.printList();
  cout<<endl;
  x.printValueTable();
  cout<<endl;
  x.printResult();

  return 0;
}
