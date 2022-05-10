#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
struct Node //for trie of nodes
{
    Node* Child[4];//A..C..G..T
    Node* fl;//failure link for every node that points to another node
    int id;// id of strings you need to search
    int value;// value of every char in trie
};
struct patterns
{
    int id; //to get length of every string in search function
    char* p;//rray of chars
};
int CharToInt[256];//convert char to int
char IntToChar[4];//convert int to char
const int N=5;
patterns arr[N];
char *text="GAACAAGTGAAGTGAGAAGAAGT";
Node* root;
int x=0;//to put values
Node* CreateTrieNode()//create new node
{
    Node* node=new Node;
    int i;
    for(i=0; i<4; i++) node->Child[i]=0;//all childs = null
    node->fl=0;
    node->id=-1;//id =-1 except when we put id of one of the strings
    node->value=x;
    x++;
    return node; //return new node
}
bool validsuffix(char* r,int start, int endd)//if the suffix is in the trie return true else false
{
    Node* cur_node=root;
    for(int i=start; i<=endd; i++)
    {
        if(!cur_node->Child[CharToInt[r[i]]]) return false; //node not found
        cur_node=cur_node->Child[CharToInt[r[i]]];//next node
    }
    return true; //node found
}
Node* suffix(char* r,int start, int endd) // Find Read r in the trie
{
    Node* cur_node=root;
    for(int i=start; i<=endd; i++) //the proper suffix from start to endd
    {
        cur_node=cur_node->Child[CharToInt[r[i]]];
    }
    return cur_node; //return the failure link
}

Node* SearchToFindFailue(char* s)//create failure link for every node in trie
{
    int n=strlen(s);//length of char* s
    if(n==0||n==1)return root;//if string composite of 1 char or 0 char then failure link root
    for(int i=1; i<n; i++)
    {
        if(validsuffix(s,i,n-1))//if valid then it's the proper suffix we use
        {
            return suffix(s,i,n-1);//return the failure node
        }
    }
    return root;//else return root
}

void CreateFailureLink(Node* node,char* curstring)
{
    node->fl=SearchToFindFailue(curstring);//return the failure link and put in node


    for(int i=0; i<4; i++) if(node->Child[i])
        {
            char str[100]= {}; //to store the current string and put the next char
            for(int i=0; i<strlen(curstring); i++)
            {
                str[i]=curstring[i];//store the current string
            }
            str[strlen(curstring)]=IntToChar[i];//store the new char
            CreateFailureLink(node->Child[i],str);///recursion to visit every node in trie and put failure link
        }
}
void Insert(char* r,int id) //to insert the strings we need to search in trie
{
    int n=strlen(r);//length of r
    Node* cur_node=root;
    for(int i=0; i<n; i++)
    {
        if(!cur_node->Child[CharToInt[r[i]]]) cur_node->Child[CharToInt[r[i]]]=CreateTrieNode();//create node if there is null
        cur_node=cur_node->Child[CharToInt[r[i]]];//go to the next node

    }

    cur_node->id=id; //put id of the string we have
}
void print(Node* node)//just to check the values of nodes and failure link
{

    cout<<node->value<<" "<<node->fl->value<<endl;
    for(int i=0; i<4; i++) if(node->Child[i])print(node->Child[i]);
}
void AhoCorasick(Node* node)
{
    int i=0;//to iterate over text
    Node* j=root;//to iterate over nodes
    cout<<"(t"<<i<<",p"<<j->value<<")"<<endl;//print the first compare
    while(i<strlen(text))//iterate until reaching the end of text
    {
        if(j->Child[CharToInt[text[i]]])//if text[i] in the current node child
        {
            j=j->Child[CharToInt[text[i]]];//go to child
            i++;//next char in text
            cout<<"(t"<<i<<",p"<<j->value<<")";
            Node* cur=j;
            while(cur->value!=0)//search in failure links of the current node until we reach the root
            {
                if(cur->id!=-1)//if there is id print it
                {
                    cout<<"Rep("<<cur->id<<","<<i-strlen(arr[cur->id].p)<<") ";
                }
                cur=cur->fl;//go to the failure link of the current node
            }
            cout<<endl;
        }
        else //if text[i] is not in the current node child
        {
            if(j->value==0&&j->fl->value==0)//if the current root is the root and no childs have the text[i]
            {
                i++;//go to the next char in text
                j=root;// stay in root
            }
            else
            {
                j=j->fl; //go to failure link of the node
            }
            cout<<"(t"<<i<<",p"<<j->value<<")"<<endl;
        }
    }
}
int main()
{
    int n=5;//size of strings we need to search in the text
    for(int i=0; i<n; i++)
    {
        arr[i].id=i;
    }
    arr[0].p="AGA";
    arr[1].p="AA";
    arr[2].p="AAG";
    arr[3].p="GAAG";
    arr[4].p="TCG";
    // make char to int to make a memory for just 4 childs not more
    //make int to char for the same purpose
    IntToChar[0]='A';
    IntToChar[1]='C';
    IntToChar[2]='G';
    IntToChar[3]='T';
    CharToInt['A']=0;
    CharToInt['C']=1;
    CharToInt['G']=2;
    CharToInt['T']=3;

    root=CreateTrieNode();//create root node
    for(int i=0; i<n; i++)
    {
        Insert(arr[i].p,i);//insert the strings
    }
    CreateFailureLink(root,"");//failure link for every node
    AhoCorasick(root);//run the algorithm over the trie to search for strings in arr
    return 0;
}
