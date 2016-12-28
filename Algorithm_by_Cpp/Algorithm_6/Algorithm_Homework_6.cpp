#include <iostream>
#include <fstream>
using namespace std;
#include <queue>
#include <stack>
#include <vector>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#define MAX 99
#define INF 9999999
#define s 0
#define t (size-1)

int size = 6;

int maxFlow;
int **C,**F;
bool *isChecked;
queue<int> preQueue;
int* path;

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
  int x,y,weight;
  int edgenum;
  cin>>size>>edgenum;
  maxFlow = 0;
  C = new int*[size];
  F = new int*[size];
  path = new int[size];
  isChecked = new bool[size];
  for(int i=0;i<size;i++){
    C[i] = new int[size];
    F[i] = new int[size];
  }
  for(int i=0;i<size;i++){
    path[i] = -1;
    isChecked[i]=false;
    for(int j=0;j<size;j++){
      C[i][j]=0;
      F[i][j]=0;
    }
  }
  while(edgenum--){
    cin>>x>>y>>weight;
    C[x][y] = weight;
  }
}

void deleteAll(){
  for(int i=0;i<size;i++){
      delete[] C[i];
      delete[] F[i];
  }
  delete[] C;
  delete[] F;
  delete[] path;
  delete[] isChecked;
  while(!preQueue.empty())  preQueue.pop();
}

int getResEdge(int x,int y){
  if(C[x][y] > 0)      return (C[x][y]-F[x][y]);
  else if(C[y][x] > 0) return F[x][y];
  else                 return 0;
}

int BFS(){
  int addValue=INF;
  for(int i=0;i<size;i++){//initial
    isChecked[i]=false;
    path[i] = -1;//path[v]=u,means a edge u->v.
  }
  while(!preQueue.empty())  preQueue.pop();
  //BFS Find the path
  preQueue.push(s);
  isChecked[s]=true;
  while(!preQueue.empty()){
    int point = preQueue.front();
    preQueue.pop();
    //cout<<"-> "<<point<<endl;
    if(point == t)  break;

    for(int i=s+1;i<=t;i++){
      if(isChecked[i]) continue;
      if(getResEdge(point,i) > 0){
        preQueue.push(i);
        isChecked[i] = true;
        path[i] = point;
        addValue = (addValue<=getResEdge(point,i))?addValue:getResEdge(point,i);
        //cout<<point<<" -> "<<i<<endl;
      }
    }
  }

  if(path[t] == -1) return -1;
  else              return addValue;
}

void Ford_Fulkerson(){
  int addValue;
  while(true){
    addValue = BFS();
    if(addValue <= 0){
      cout<<"Can't find a path.The max flow is "<<maxFlow<<'.'<<endl;
      break;
    }
    maxFlow += addValue;
    stack<int> buffer;
    int u=t;
    while(u != s){
      buffer.push(u);
      u = path[buffer.top()];
      F[u][buffer.top()] += addValue;
      F[buffer.top()][u] -= addValue;
    }
    cout<<"s";
    while(buffer.size() > 1 && buffer.top() != t){
      cout<<" -> n"<<buffer.top();
      buffer.pop();
    }
    cout<<" -> t"<<endl;
    cout<<"Add "<<addValue<<" to the flow."<<endl;
  }
}

int main(int argc, char *argv[])
{
  initial();

  tc.start();
    Ford_Fulkerson();
  tc.stop();
  tc.printTime();
  deleteAll();
  return 0;
}
