#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <sstream>
#include <regex>
#include <queue>
#include <vector>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#define MAX 99
const int size = 256;

string orgfilename="cacm.all";
string cfilename="cacm.all.hmc";
string dcfilename="cacm.dc.all";

void updateFilename(){
  regex re("(*)\\.(*)$");
}

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
  int weight;  //weight value of node
  unsigned char value; //thos node mean 'ch'
  node *left,*right,*parent;
  node(unsigned char value,int freq=0){
    this->value=value;
    this->weight = weight;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  node(node *l,node *r){
    left = l;
    right = r;
    value = '\0';
    weight = l->weight + r->weight;
  }
  node(){
    value = 0;
    weight = 0;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  bool isLeaf(){
    return (NULL == left && NULL == right);
  }
};

struct compare{//For priority queue
  bool operator()(node *x,node *y) const{
    return x->weight > y->weight;
  }
};

class HuffmanTree{
private:
  node *root;
  priority_queue<node*,vector<node*>,compare> pq;
  string *codeTable;
  int *freqTable;

  void deleteNode(node *x);
  void buildCodeTable(node *x,string str);
public:
  HuffmanTree();
  ~HuffmanTree();
  node* getRoot();
  void Compression();
  void Decompression();

  void initialHT();
  void buildCodeTable();
  void printCodeTable();

};

HuffmanTree::HuffmanTree(){
  root = NULL;
  codeTable = new string[size];
  freqTable = new int[size];
  for(int i=0;i<size;i++) freqTable[i] = 0;
}

HuffmanTree::~HuffmanTree(){
  deleteNode(root);
  delete[] codeTable;
  delete[] freqTable;
  while(!pq.empty())  pq.pop();
}

void HuffmanTree::deleteNode(node *x){
  if(NULL == x) return;
  deleteNode(x->left);
  deleteNode(x->right);
  delete x;
}

node* HuffmanTree::getRoot(){
  return root;
}

void HuffmanTree::countFreq(){
  unsigned char temp;
  //Read File
  ifstream fin(orgfilename.c_str(),ios_base::in);
  if(!fin.is_open()){
    cout<<"Error when open file."<<endl;
    return;
  }
  //count every charactor's freqency.
  while(!fin.eof()){

    fin.get(temp);
    freqTable[(int)temp]++;
  }
  fin.close();
}

void HuffmanTree::initialHuffmanTree(){//initial the Huffman Tree table based on freqency table.
  for(int i=0;i<size;i++){
    if(0 == freqTable[i])  continue;
    node *temp = new node((unsigned char)i,freqlist[i]);
    hqueue.push(temp);
  }
  //Finished every leaf's initial.
  node *x,*y;
  while(pq.size() > 1){
    x = pq.top();
    pq.pop();
    y = pq.top();
    pq.pop();
    node *temp = new node(x,y);
    x->parent = temp;
    y->parent = temp;
    hqueue.push(temp);
  }
  root = pq.top();
  pq.pop();
}

void HuffmanTree::DLRtraverse(){
  
}

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
  return 0;
}
