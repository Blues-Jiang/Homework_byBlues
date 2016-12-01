#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#define MAX 99
const int size = 256;

char filename[]="cacm.all";
char cmpfilename[]="cacm.all.hmc";
char dcfilename[]="cacm.dc.all";

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

class node{
public:
  int freq;  //weight value of node
  char value; //thos node mean 'ch'
  node *left,*right,*parent;
  node(char value,int freq=0){
    this->value=value;
    this->freq = freq;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  node(node *l,node *r){
    left = l;
    right = r;
    value = '\0';
    freq = l->freq + r->freq;
  }
  node(){
    value = 0;
    freq = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  bool isLeaf(){
    return (NULL == left && NULL == right);
  }
};

struct compare{
  bool operator()(node *x,node *y) const{
    return x->freq > y->freq;
  }
};

class HuffmanTree{
private:
  node *root;
  priority_queue<node*,vector<node*>,compare> hqueue;
  string *code;
  void buildCodeTable(node *x,string str);
public:
  HuffmanTree();
  //~HuffmanTree();

  void initialHT();
  void buildCodeTable();
  void printCodeTable();
  void Compression();
  void Decompression();
};

HuffmanTree::HuffmanTree(){
  root = NULL;
  code = new string[size];
}

void HuffmanTree::initialHT(){
  int *freqlist=new int[size];
  //Read File
  ifstream fin(filename);
  //ifstream fin(filename,ios_base::binary);//for binary file
  if(!fin.is_open()){
    cout<<"Error when open file."<<endl;
    return;
  }
  //count every charactor's freqency.
  while(!fin.eof()){
    char ch;
    fin.get(ch);
    freqlist[(int)ch]++;
  }
  fin.close();

  for(int i=0;i<size;i++){
    if(0 == freqlist[i])  continue;
    node *temp = new node((char)i,freqlist[i]);
    hqueue.push(temp);
  }

  //Finished every leaf's initial.
  node *x,*y;
  while(hqueue.size() > 1){
    x = hqueue.top();
    hqueue.pop();
    y = hqueue.top();
    hqueue.pop();
    node *temp = new node(x,y);
    x->parent = temp;
    y->parent = temp;
    hqueue.push(temp);
  }
  root = hqueue.top();
  hqueue.pop();
}
//void HuffmanTree::importCodeTable(){
//}

void HuffmanTree::buildCodeTable(){
  buildCodeTable(root,"");
}

void HuffmanTree::buildCodeTable(node *x,string str){
  if(x->isLeaf()){
    code[(int)x->value] = str;
    return;
  }
  buildCodeTable(x->left,str+'0');
  buildCodeTable(x->right,str+'1');
}

void HuffmanTree::printCodeTable(){
  if(code == NULL){
    cout<<"ERROR"<<endl;
    return;
  }
  for(int i=0;i<size;i++){
    if(code[i].empty()) continue;
    //cout<<i<<'('<<(char)i<<"):"<<code[i]<<endl;
    cout<<i<<":"<<code[i]<<endl;
  }
}

void HuffmanTree::Compression(){
  initialHT();
  buildCodeTable();
  //for binary file
  ifstream fin(filename, ios_base::binary);
  ofstream fout(cmpfilename, ios_base::binary);

  char temp;
  while (!fin.eof()) {
    fin.get(temp);
    fout<<code[(int)temp];
  }

  fin.close();
  fout.close();
}

void HuffmanTree::Decompression(){
  ifstream fin(cmpfilename, ios_base::binary);
  ofstream fout(dcfilename, ios_base::binary);

  fin.close();
  fout.close();
}

int main(int argc, char *argv[])
{
  HuffmanTree ht=HuffmanTree();

  tc.start();
    //ht.Compression();
    ht.initialHT();
    ht.buildCodeTable();
    ht.printCodeTable();
  tc.stop();
  cout<<"Compression complete."<<endl;
  //tc.printTime();
  /*tc.start();
    ht.Decompression();
  tc.stop();
  cout<<"Decompression complete."<<endl;
  tc.printTime();*/
  // ht.printCodeTable();
  return 0;
}
