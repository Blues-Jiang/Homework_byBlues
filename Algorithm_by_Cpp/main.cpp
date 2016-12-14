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
const int size = 256;


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

/*void updateFilename(){
  size_t loc;
  loc=orgfilename.find_last_of(".");
  if(loc != npos){
    extension = orgfilename.substr(loc+1);
    cfilename = orgfilename.append(".hmc");

  }

  loc=cfilename.find_last_of(".hmc");
  if(loc != npos) dcfilename = cfilename.substr(0,loc);
  loc = dcfilename.find_last_of('.'+extension);
  if(loc != npos) dcfilename.insert(loc,"_dc");
}*/


class HuffmanTree{
private:
  node *root;
  priority_queue<node*,vector<node*>,compare> pq;
  string *codeTable;
  int *freqTable;
  string orgfilename;
  string cfilename;
  string dcfilename;
  string extension;

  void deleteNode(node *x);
  void countFreq();
  void initialHuffmanTree();
  void buildCodeTable(node *x,string str);
  void DLRtraverse(ofstream* fout,node *x,unsigned char* buffer,int* pointer);
  void rebuildHuffmanTree(ifstream* fin,node *x,unsigned char* buffer,int* pointer);
public:
  HuffmanTree();
  ~HuffmanTree();
  node* getRoot();

  void Compression(string filename);
  void Decompression(string filename);

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
  ifstream fin(orgfilename.c_str(),ios_base::in|ios_base::binary);
  if(!fin.is_open()){
    cout<<"Error when open file."<<endl;
    return;
  }
  //count every charactor's freqency.
  while(fin.good()){
    fin.read((char *)&temp,sizeof(temp));
    freqTable[(int)temp]++;
  }
  fin.close();
}

void HuffmanTree::initialHuffmanTree(){//initial the Huffman Tree table based on freqency table.
  for(int i=0;i<size;i++){
    if(0 == freqTable[i])  continue;
    node *temp = new node((unsigned char)i,freqTable[i]);
    pq.push(temp);
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
    pq.push(temp);
  }
  root = pq.top();
  pq.pop();
}

void HuffmanTree::buildCodeTable(node *x,string str){
  if(x->isLeaf()){
    codeTable[(int)x->value] = str;
    return;
  }
  buildCodeTable(x->left,str+'0');
  buildCodeTable(x->right,str+'1');
}

void HuffmanTree::Compression(string filename=""){
  //Update the Compression filename.
  if(!filename.empty()) orgfilename = filename;
  size_t loc=orgfilename.find_last_of(".");
  if(loc != string::npos){
    //extension = orgfilename.substr(loc+1);
    cfilename = orgfilename + ".hmc";
  }
  //some step before build the Compression file.
  countFreq();
  initialHuffmanTree();
  buildCodeTable(root,"");

  ifstream fin(orgfilename.c_str(), ios_base::in|ios_base::binary);
  ofstream fout(cfilename.c_str(), ios_base::out|ios_base::binary);

  fin.seekg(0, ios_base::end);
  unsigned int fileLen = fin.tellg();
  fout.write((char *)&fileLen, sizeof(fileLen));
  fin.seekg(0, ios_base::beg);

  unsigned char inBuff;
  unsigned char outBuff;
  int pointer=1;

  DLRtraverse(&fout,root,&outBuff,&pointer);
  fout.write((char *)&outBuff,sizeof(outBuff));

  string::iterator itstr;

  //read the origenal file to make the Compression file
  while (fin.read((char*)&inBuff,sizeof(inBuff))){
    //while(fin.good())
    //fin.read((char*)&inBuff,sizeof(inBuff));
    itstr = codeTable[inBuff].begin();
    do{
      outBuff = (outBuff<<1) | (*itstr&0x01);
      pointer++;
      if(pointer == sizeof(outBuff)*8){
        fout.write((char *)&outBuff,sizeof(outBuff));
        //outBuff = 0;
        pointer = 1;
      }
    }while(++itstr < codeTable[inBuff].end());
  }
  fout.write((char *)&outBuff,sizeof(outBuff));

  fin.close();
  fout.close();
}

void HuffmanTree::DLRtraverse(ofstream* fout,node *x,unsigned char* buffer,int* pointer){
  if(x->isLeaf()){
    *buffer =*buffer << 1 | 0x01;
    (*pointer)++;
    if(*pointer == sizeof(*buffer)*8){
      fout->write((char *)buffer,sizeof(*buffer));
      *pointer=0;
    }
    *buffer = *buffer << (sizeof(*buffer)*8 - *pointer) | x->value >> *pointer;
    fout->write((char *)buffer,sizeof(*buffer));
    *buffer = x->value;
    return;
  }
  else{
    *buffer =*buffer << 1 | 0x00;
    (*pointer)++;
    if(*pointer == sizeof(*buffer)*8){
      fout->write((char *)buffer,sizeof(*buffer));
      *pointer=0;
    }
    DLRtraverse(fout,x->left,buffer,pointer);
    DLRtraverse(fout,x->right,buffer,pointer);
  }
}

void HuffmanTree::rebuildHuffmanTree(ifstream* fin,node *x,unsigned char* buffer,int* pointer){//File Header has the node list of Huffman Tree by DLR traverse.Start from root
  if(*pointer < 0){
    fin->read((char *)buffer,sizeof(*buffer));
    *pointer = sizeof(*buffer)*8-1;
  }
  unsigned char temp = *buffer >> *pointer & 0x01;
  (*pointer)--;
  if(temp == 1){//is a leaf
    unsigned char v = *buffer << *pointer;
    fin->read((char *)buffer,sizeof(*buffer));
    v = v | *buffer >> *pointer;
    x->value=v;
    return;
  }
  else if(temp == 0){
    node *l=new node();
    node *r=new node();
    x->left = l;
    l->parent = x;
    rebuildHuffmanTree(fin,l,buffer,pointer);
    x->right = r;
    r->parent = x;
    rebuildHuffmanTree(fin,r,buffer,pointer);
  }
}

void HuffmanTree::Decompression(string filename=""){

  //Update the Deompression filename.
  if(!filename.empty()) cfilename = filename;
  size_t loc=cfilename.find(".hmc");
  if(loc != string::npos) dcfilename = cfilename.substr(0,loc);
  loc = dcfilename.find_last_of('.'+extension);
  if(loc != string::npos) dcfilename.insert(loc,"_dc");

  //some step before build the Compression file.
  ifstream fin(cfilename.c_str(), ios_base::in|ios_base::binary);
  ofstream fout(dcfilename.c_str(), ios_base::out|ios_base::binary);

  unsigned int fileLen = 0;
  fin.read((char *)&fileLen, sizeof(fileLen));

  unsigned char inBuff;
  unsigned char outBuff;
  int pointer=sizeof(inBuff)*8-1;
  fin.read((char *)&inBuff, sizeof(inBuff));
  root = new node();
  rebuildHuffmanTree(&fin,root,&inBuff,&pointer);

  node* np = root;
  while (fin.good()){
    if(pointer < 0){
      fin.read((char*)&inBuff,sizeof(inBuff));
      pointer=sizeof(inBuff)*8-1;
    }
    unsigned char temp = inBuff >> pointer & 0x01;
    pointer--;
    if(np->isLeaf()){
      outBuff = np->value;
      np=root;
      fout.write((char*)&outBuff,sizeof(outBuff));
    }
    else if(temp == 0x00) np = np->left;
    else if(temp == 0x01) np = np->right;
  }

  fin.close();
  fout.close();
}

int main(int argc, char *argv[])
{
  HuffmanTree ht=HuffmanTree();
  string filename="cacm.all";
  tc.start();
    ht.Compression(filename);
  tc.stop();
  cout<<"Compression complete."<<endl;
  tc.printTime();
  /*tc.start();
    ht.Decompression();
  tc.stop();
  cout<<"Decompression complete."<<endl;
  tc.printTime();*/
  return 0;
}

/*void HuffmanTree::Compression(){
  initialHT();
  buildCodeTable();
  //for binary file
  ifstream fin(filename, ios_base::in|ios_base::binary);
  ofstream fout(cfilename, ios_base::out|ios_base::binary);

  unsigned char temp;
  string::iterator itstr;

  while (fin.good()) {
    fin.read((char*)&temp,sizeof(temp));
    itstr = codeTable[]
  }

  fin.close();
  fout.close();
}

void HuffmanTree::Decompression(){
  ifstream fin(cfilename, ios_base::in|ios_base::binary);
  ofstream fout(dcfilename, ios_base::out|ios_base::binary);

  fin.close();
  fout.close();
}

/*

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
  ofstream fout(cfilename, ios_base::binary);

  char temp;
  while (!fin.eof()) {
    fin.get(temp);
    fout<<code[(int)temp];
  }

  fin.close();
  fout.close();
}

void HuffmanTree::Decompression(){
  ifstream fin(cfilename, ios_base::binary);
  ofstream fout(dcfilename, ios_base::binary);

  fin.close();
  fout.close();
}


*/
