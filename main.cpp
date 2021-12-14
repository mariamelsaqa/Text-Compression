#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<cmath>
#include <map>
#include<fstream>
#include<queue>
#include<unordered_map>
#define MAX_TREE_HT 256
#define DOLLAR$
using namespace std;
  
map<char, string> Binarycompressed;

map<char, int> Binaryfrequency;
  
struct Node
{
    char Binarydata;
    int Binaryfreq;
    Node *left, *right;
    Node(char Bdata, int Bfrequency)
    {
        left = NULL;
        right = NULL;
        this->Binarydata = Bdata;
        this->Binaryfreq = Bfrequency;
    }
};

struct comparing
{
    bool operator()(Node* left, Node* right)
    {
        return (left->Binaryfreq > right->Binaryfreq);
    }
};
  
void printing(struct Node* rootNode, string str)
{
    if (!rootNode)
        return;
    if (rootNode->Binarydata != '.')
        cout << rootNode->Binarydata << ": " << str << "\n";
    printing(rootNode->left, str + "0");
    printing(rootNode->right, str + "1");
}
  
void storing(struct Node* rootnode, string str)
{
    if (rootnode==NULL)
        return;
    if (rootnode->Binarydata != '.')
        Binarycompressed[rootnode->Binarydata]=str;
    storing(rootnode->left, str + "0");
    storing(rootnode->right, str + "1");
}

priority_queue<Node*, vector<Node*>, comparing> minimumheap;

void HuffCoding(int size)
{
    struct Node *l, *r, *t;
    for (map<char, int>::iterator v=Binaryfrequency.begin(); v!=Binaryfrequency.end(); v++)
        minimumheap.push(new Node(v->first, v->second));
    while (minimumheap.size() != 1)
    {
        l = minimumheap.top();
        minimumheap.pop();
        r = minimumheap.top();
        minimumheap.pop();
        t = new Node('.', l->Binaryfreq + r->Binaryfreq);
        t->left = l;
        t->right = r;
        minimumheap.push(t);
    }
    storing(minimumheap.top(), "");
}

void BinaryFreqCalculation(string str)
{
    for (int i=0; i<str.size(); i++)
        Binaryfrequency[str[i]]++;
}

string decompression(struct Node* rootnode, string str)
{
    string decompressed = "";
    struct Node* currentnode = rootnode;
    for (int i=0;i<str.size();i++)
    {
        if (str[i] == '0')
           currentnode = currentnode->left;
        else
           currentnode = currentnode->right;

        if (currentnode->left==NULL and currentnode->right==NULL)
        {
            decompressed += currentnode->Binarydata;
            currentnode = rootnode;
        }
    }
    return decompressed+'\0';
}

/*string dec_to_binary(int number)
{
    int binary[8];
    string temp="";

    for (int i = 0; i < 8; i++)
        binary[i] = 0;

    for (int i = 0; number > 0; i++)
    {
        binary[7 - i] = number % 2;
        number = number / 2;
    }

    for (int i = 0; i < 8; i++)
        temp += to_string(binary[i]);

    return temp;
}*/

string file_to_binary(){
    ifstream file;
      fstream ofile;
      fstream freq;
    ofile.open("binary.txt");
  file.open("input.txt");
  freq.open("frequencies.txt");
  string text;
    getline(file,text);

  string compressed;
    BinaryFreqCalculation(text);
    HuffCoding(text.length());
    cout << "Each character and it's Binary frequency:"<<endl;
    for (auto v=Binarycompressed.begin(); v!=Binarycompressed.end(); v++){
        cout << v->first <<' ' << v->second << endl;
        freq <<  v->first <<' ' << v->second << '\n';
        //cout<<v->second.length()<<endl;
    }
    for (auto i: text)
        compressed+=Binarycompressed[i];

    cout<<endl;
    cout << "Compressed in Binary form"<<endl; cout<<compressed << endl;
    ofile << compressed;
    return compressed;

}


int binary_to_dec(string input)
{
    int binary = stoi(input);
    int decimal = 0;
    int rem = 0;

    for (int i = 0; binary > 0; i++)
    {
        rem = binary % 10;
        decimal += rem * pow(2, i);
        binary = binary / 10;
    }

    return decimal;
}

void compress()
{
  fstream file;
  file.open("compressed.txt");
  string binary = file_to_binary();
    vector<string> temp;

    while (binary.length() > 0)
    {
        temp.push_back(binary.substr(0, 8));
        binary.erase(0, 8);
    }

  cout<<endl;
  cout<<"compressed text:"<<endl;
    for (int i = 0; i < temp.size(); i++)
    {
        cout << (char)binary_to_dec(temp[i])<<endl;
    file << (char)binary_to_dec(temp[i]);
    }
  cout<<endl;
}
  
void decompress(){
  ifstream file;
  fstream Ofile;
  file.open("binary.txt");
  Ofile.open("decompressed.txt");
  string compressed;
  getline(file, compressed);
  string decompressed;
  decompressed = decompression(minimumheap.top(), compressed);
    cout<<endl;
    cout << "Decoded Huffman Data:" << endl;
    cout<<decompressed << endl;
    Ofile << decompressed;
}
 
void calculations()
{
      string str;
ifstream file("input.txt");
getline(file,str);
    unordered_map<char, int> M;
    for (int i = 0; str[i]; i++)
    {
        if (M.find(str[i]) == M.end())
        {
            M.insert(make_pair(str[i], 1));
        }
        else
        {
            M[str[i]]++;
        }
    }
  string text;
    BinaryFreqCalculation(text);
    HuffCoding(text.length());
    vector<double> P;
    vector<char> c;
    vector<int> length;
    double strlen = str.length()+0.0;
    for (auto v=Binarycompressed.begin(); v!=Binarycompressed.end(); v++){
    for (auto& it : M) {
    if(v->first == it.first){
      P.push_back(it.second/strlen);
      c.push_back(it.first);
    }
    }
    length.push_back(v->second.length()-1);
    }

    vector<double> sum;
    double L=0;
    vector<double> logP;
    vector<double> PlogP;
    double H=0;
    for(int i=0;i<P.size();i++){
    sum.push_back(P[i]*length[i]);
      L+= sum[i];
      logP.push_back(log(P[i]));
      PlogP.push_back(logP[i] * P[i]*-1);
      H+=PlogP[i];
    }
double compressionratio,efficiency;
compressionratio= L/8;
cout<<"The compression ratio = "<<compressionratio<<endl;
efficiency = (H/L)*100;
cout<<"The coding efficiency = "<<efficiency<<" %"<<endl;
}

int main()
{
  string answer;
  cout<<"What do you want to do? (Compress, Decompress)"<<endl;
  cin>>answer;
  if(answer == "Compress" || answer == "compress"){
  compress();}
  else if (answer == "Decompress"|| answer == "decompress"){
  compress();
  decompress();}
  else{
    cout<<"invalid answer"<<endl;
  }
  cout<<endl;
  calculations();
    return 0;
}
