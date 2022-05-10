#include <iostream>

using namespace std;
char *text="AGAGAAGAGGAGAAGAGAAGAGA";
char *p="AGAAGAG";
struct node
{
    int id,fl; //index of node .....failure link
};
bool valid(int x,int y)//to check if the selected suffix is valid to take the longest proper suffix
{
    int j=0;
    for(int i=x; i<=y; i++)
    {
        if(p[i]!=p[j])//if any char not equal then it's not valid
            return false;
        j++;
    }
    return true;//when all chars equal each other
}
int longestsuffix(int idx) ///idx is the end of suffix
{
    int maxi=-1;//maximum size of suffixes
    for(int i=1; i<=idx; i++)
    {
        if(valid(i,idx))
        {
            maxi=max(maxi,idx-i);//if the suffix is valid then take the longest
        }
    }
    return maxi;
}
int main()
{
    int n=7,N=23;//size of text...size of pattern
    node* a=new node[n]; //array of struct
    for(int i=0; i<n; i++)
    {
        a[i].id=i;//id of each index in pattern
    }
    a[0].fl=0;//first failure link is 0
    for(int i=1; i<n; i++)
    {
        a[i].fl=longestsuffix(i)+1;//assign to each index a failure link
    }
    int i=0,j=0;//pattern ,text
    cout<<"(t"<<j<<','<<"p"<<i<<")\n"; //the first comparison
    while(true)
    {
        if(p[i]==text[j])  //if the first char equal to the second then move forward with both
        {
            i++;
            j++;
        }
        else if(p[i]!=text[j]&&i==0)   //if the first char not equal to the second and the pattern (i)is the first index then move the text iterator only
        {
            j++;
        }
        else if(p[i]!=text[j])
        {
            i=a[i-1].fl;//if the first char not equal to the second then i go to failure link
        }
        if(i==n) //when you find your sequence
        {
            cout<<"(t"<<j<<','<<"p"<<i<<") Rep("<<j-i<<")\n";
            i=a[i-1].fl;//i go to failure link
            cout<<"(t"<<j<<','<<"p"<<i<<")\n";
        }
        else
        {
            cout<<"(t"<<j<<','<<"p"<<i<<")\n";//print every iteration
        }
        if(j==N)
        {
            break;///when the iterator of text reach last index then break there will be no matching
        }
    }
    return 0;
}
