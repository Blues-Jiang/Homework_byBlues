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


bool readBit(ifstream* fin,unsigned char *buffer,int* pointer){//pointer is from 8 to 0.It means there are xxx bits wait for read.
  //if(!fin->good())   return false;
  unsigned char temp;
  if((*pointer) <= 0){
    fin->read((char *)buffer,sizeof(*buffer));
    *pointer = sizeof(*buffer)*8;
  }
  (*pointer)--;
  temp = ( *buffer >> *pointer ) & 0x01;
  return (temp == 0x00)?false:true;
}

unsigned char readByte(ifstream* fin,unsigned char *buffer,int* pointer){
  //if(!fin->good())   return 0xff;
  unsigned char temp;
  if((*pointer) <= 0){
    fin->read((char *)buffer,sizeof(*buffer));
    temp = *buffer;
  }
  else{
    temp = *buffer << ( sizeof(*buffer)*8 - *pointer );
    fin->read((char *)buffer,sizeof(*buffer));
    temp = temp | ( *buffer >> *pointer );
  }
  return temp;
}

void writeBit(ofstream* fout,bool x,unsigned char* buffer,int* pointer){//pointer is from 0 to 7.It means there are already xxx bits write in buffer,if pointer is equal to 8,means this buffer is full to write.
  if(!fout->good())   return;
  *buffer = (*buffer << 1) | (x?0x01:0x00);
  (*pointer)++;
  if(*pointer >= sizeof(*buffer)*8){
    fout->write((char *)buffer,sizeof(*buffer));
    *pointer = 0;
    //*buffer = 0x00;
  }
}

void writeByte(ofstream* fout,unsigned char x,unsigned char* buffer,int* pointer){
  if(!fout->good())   return;
  if(*pointer == 0){
    *buffer = x;
    fout->write((char *)buffer,sizeof(*buffer));
    //*buffer = 0x00;
  }
  else{
    *buffer = ( *buffer << ( sizeof(*buffer)*8 - *pointer )) | ( x >> *pointer );
    fout->write((char *)buffer,sizeof(*buffer));
    *buffer = x;
  }
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
  double weight;  //weight value of node
  unsigned char value; //thos node mean 'ch'
  node *left,*right,*parent;
  node(unsigned char value,double weight=0){
    this->value=value;
    this->weight = weight;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
  node(node *l,node *r){
    left = l;
    right = r;
    parent = NULL;
    value = 0;
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
    return (x->weight - y->weight) > 0;
  }
};

class HuffmanTree{
private:
  node *root;
  string *codeTable;
  double *freqTable;
  string orgfilename;
  string cfilename;
  string dcfilename;


  void deleteNode(node *x);
  void countFreq();
  void initialHuffmanTree();
  void buildCodeTable(node *x,string str);
  void DLRtraverse(ofstream* fout,node *x,unsigned char* buffer,int* pointer);
  void rebuildHuffmanTree(ifstream* fin,node *x,unsigned char* buffer,int* pointer);
  void printCodeTable(node *x);
public:
  HuffmanTree();
  ~HuffmanTree();
  node* getRoot();

  void Compression(string filename);
  void Decompression(string filename);

  void buildCodeTable();
  void printCodeTable();
  void printRebuildedCodeTable();

};

HuffmanTree::HuffmanTree(){
  root = NULL;
  codeTable = new string[size];
  freqTable = new double[size];
  for(int i=0;i<size;i++) freqTable[i] = 0;
}

HuffmanTree::~HuffmanTree(){
  deleteNode(root);
  delete[] codeTable;
  delete[] freqTable;
  //while(!pq.empty())  pq.pop();
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
  priority_queue<node*,vector<node*>,compare> pq;
  for(int i=0;i<size;i++){
    if(freqTable[i] <= 0)  continue;
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

void HuffmanTree::printCodeTable(){
  for(int i=0;i<size;i++){
    if(freqTable[i] == 0) continue;
    cout<<i<<'('<<(char)i<<",freq:"<<freqTable[i]<<"):"<<codeTable[i]<<endl;
  }
}

void HuffmanTree::printRebuildedCodeTable(){
  for(int i=0;i<size;i++){
    if(codeTable[i] == "") continue;
    cout<<i<<'('<<(char)i<<"):"<<codeTable[i]<<endl;
  }
}

void HuffmanTree::printCodeTable(node *x){
  if(x == NULL) return;
  if(x->isLeaf()){
    cout<<(int)(x->value)<<'('<<x->value<<"):"<<codeTable[x->value]<<endl;
    return;
  }
  printCodeTable(x->left);
  printCodeTable(x->right);
}

void HuffmanTree::buildCodeTable(node *x,string str){
  if(x->isLeaf()){
    codeTable[x->value] = str;
    return;
  }
  buildCodeTable(x->left,str+'0');
  buildCodeTable(x->right,str+'1');
}

void HuffmanTree::DLRtraverse(ofstream* fout,node *x,unsigned char* buffer,int* pointer){//use DLR traverse to save the Huffman Tree to the compression file
  if(x == NULL) return;
  if(x->isLeaf()){
    writeBit(fout,true,buffer,pointer);
    writeByte(fout,x->value,buffer,pointer);
    return;
  }
  else{
    writeBit(fout,false,buffer,pointer);
    DLRtraverse(fout,x->left,buffer,pointer);
    DLRtraverse(fout,x->right,buffer,pointer);
  }
}

void HuffmanTree::Compression(string filename=""){
  //Update the Compression filename.
  if(!filename.empty()) orgfilename = filename;
  size_t loc=orgfilename.find_last_of(".");
  if(loc != string::npos){
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
  unsigned char outBuff=0x00;
  int pointer=0;

  DLRtraverse(&fout,root,&outBuff,&pointer);
  while(pointer > 0){//In case of there are some bit hasn't write in compression file
    writeBit(&fout,false,&outBuff,&pointer);
  }

  cout<<"-->>"<<fout.tellp()<<endl;

  pointer=0;
  outBuff=0;
  string::iterator itstr;
  //read the origenal file to make the Compression file
  while (fin.good()){
    //while(fin.good())
    fin.read((char *)&inBuff,sizeof(inBuff));
    itstr = codeTable[inBuff].begin();
    do{
      bool temp = (*itstr == '1')?true:false;
      writeBit(&fout,temp,&outBuff,&pointer);
    }while(++itstr <= codeTable[inBuff].end());
  }
  /*while(pointer > 0){//In case of there are some bit hasn't write in compression file
    writeBit(&fout,false,&outBuff,&pointer);
  }*/
  cout<<"-->>"<<fout.tellp()<<endl;
  fin.close();
  fout.close();
}

void HuffmanTree::rebuildHuffmanTree(ifstream* fin,node *x,unsigned char* buffer,int* pointer){//File Header has the node list of Huffman Tree by DLR traverse.Start from root
  //Read the first bit,if it's 0 ,means this node has children.If it's 1,means this node is a leaf,and 1 byte after this bit is the value of this leaf node.
  //if(x == NULL) return;
  bool temp = readBit(fin,buffer,pointer);
  if(temp){//is a leaf
    x->value = readByte(fin,buffer,pointer);
    return;
  }
  else{
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
  loc = dcfilename.find_last_of('.');
  if(loc != string::npos) dcfilename.insert(loc,"_dc");

  //some step before build the Compression file.
  ifstream fin(cfilename.c_str(), ios_base::in|ios_base::binary);
  ofstream fout(dcfilename.c_str(), ios_base::out|ios_base::binary);

  unsigned int fileLen = 0;
  fin.read((char *)&fileLen, sizeof(fileLen));

  //cout<<"Filelen from cfile:"<<fileLen<<endl;
  //cout<<"->"<<fin.tellg()<<endl;

  unsigned char inBuff;
  unsigned char outBuff;
  int inPointer = 0;
  int outPointer = 0;

  root = new node();
  rebuildHuffmanTree(&fin,root,&inBuff,&inPointer);
  while(inPointer > 0){
    readBit(&fin,&inBuff,&inPointer);
  }

  cout<<"-->>"<<fin.tellg()<<endl;

  buildCodeTable(root,"");

  node* np = root;
  //while (fin.good() && fileLen > 0){
  while (fin.good()){
    bool temp = readBit(&fin,&inBuff,&inPointer);
    if(np->isLeaf()){
      fileLen--;
      writeByte(&fout,np->value,&outBuff,&outPointer);
      np=root;
      continue;
    }
    if(temp)  np = np->right;
    else      np = np->left;
  }

  fin.close();
  fout.close();
}

int main(int argc, char *argv[])
{
  HuffmanTree ht=HuffmanTree();
  string filename="./test/pi_data.txt";
  tc.start();
    ht.Compression(filename);
  tc.stop();
  cout<<"Compression complete."<<endl;
  tc.printTime();
  ht.printCodeTable();

  HuffmanTree htdc=HuffmanTree();
  filename = filename + ".hmc";
  tc.start();
    htdc.Decompression(filename);
  tc.stop();
  cout<<"Decompression complete."<<endl;
  tc.printTime();
  //htdc.printRebuildedCodeTable();
  return 0;
}
