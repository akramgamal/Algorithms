#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<bits/stdc++.h>
using namespace std;
const int N=5e6;
int n,tt=1;
char *s,*line; //s->array of chars ....line->to read line by line and put it into s
bool compare1(int x,int y)
{
    int i=x,j=y;
    if(i>j) //to iterate until reaching the smaller the last index of suffix
    {
        while(i<n)
        {
            if(s[i]<s[j])
            {
                return true;
            }
            else if(s[i]>s[j])
            {
                return false;
            }
            i++;
            j++;
        }
        return true;
    }
    else
    {
        while(j<n)
        {
            if(s[i]<s[j])
            {
                return true;
            }
            else if(s[i]>s[j])
            {
                return false;
            }
            i++;
            j++;
        }
        return false;
    }
}
struct suffix
{
    int index,order; //index of s
    //order to sort them
};
bool compare2(suffix x,suffix y)
{
    if(x.order<y.order)return true; //sort by order for the first time in function 2......used only once
    return false;
}
int old,total,newchars;//old->to iterate from the first char after the equal ones...total-> 2^i.....newchars->the distance you need to iterate
bool compare3(suffix x,suffix y)
{
    if(x.order!=y.order)return x.order<y.order; //if not equal sort normally
    else
    {
        int s1=x.index+old,s2=y.index+old,c=0;
        while(c<newchars) //distance you need to iterate in 2^i
        {
            if(s1>=n) return true; //s1 exceed size of s
            if(s2>=n) return false; //s2 exceed size of s
            if(s[s1]<s[s2])return true;//smaller return true
            else if(s[s1]>s[s2]) return false;//bigger return false
            s1++;
            s2++;
            c++;//number of chars you need to iterate
        }

    }
    return false;
}
bool thesame(int x,int y) //find if the first suffix equal to the second or not
{
    int s1=x+old,s2=y+old,c=0;
    while(c<newchars)
    {
        if(s[s1]!=s[s2]||(s1>=n&&s2<n)||(s1<n&&s2>=n)) return false;//if it's not equal in any way return false else return true
        s1++;
        s2++;
        c++;
    }
    return true;
}
void suffixarray(suffix b[])
{
    bool uniquee=true;
    if(b[n-1].order!=n-1)uniquee=false;//see if becomes unique or not
    old=1,total=2;//total =2^1 of the first time
    newchars=total-old;//distance you need to iterate
    while(!uniquee)
    {
        sort(b,b+n,compare3);
        int *arr=new int[N],x=1;//new orders to update the old ones
        arr[0]=0;
        for(int i=1; i<n; i++)
        {
            if(b[i].order==b[i-1].order) //if 2 orders have the same number
            {
                if(thesame(b[i-1].index,b[i].index))arr[i]=arr[i-1]; //if the same chars then it's the same order else not the same order
                else
                {
                    arr[i]=x;
                    x++;
                }
            }
            else
            {
                arr[i]=x;
                x++;
            }
        }
        for(int i=0; i<n; i++)
        {
            b[i].order=arr[i];//put the new order instead of old ones
        }
        if(b[n-1].order==n-1)uniquee=true;
        old=total;//the last index we checked
        total*=2;//the next iteration logn
        newchars=total-old;//number of chars we need to check
    }

}
void functionFor10000Gene()
{
    n=10000;
    s=new char[n];
    line=new char[200];
    FILE* file=fopen("genome.fasta.txt","r");
    fscanf(file,"%[^\n\r] ",s);//ignoring the id of genome
    s[0]=0;//delete the id line
    while(true)
    {
        if(strlen(s)>n)break; //to stop when it exceed 10000 chars
        fscanf(file,"%s",line);//read the next line
        strcat(s,line);//append lines in s
    }
    int* a=new int[n];
    suffix* b=new suffix[n]; //struct of order and index
    for(int i=0; i<n; i++)
    {
        //filling the suffix
        if(s[i]=='A')
            b[i].order=0;
        else if(s[i]=='C')
            b[i].order=1;
        else if(s[i]=='G')
            b[i].order=2;
        else if(s[i]=='T')
            b[i].order=3;
        b[i].index=i;
    }
   for(int i=0; i<n; i++)
    {
        a[i]=i;//initialization of array a that works n^2(log(n))
    }
    sort(b,b+n,compare2);//sorting for the second function the first time to sort by orders to make it easy to see the same orders

    suffixarray(b); //change the suffix array and sort it

    sort(a,a+n,compare1); //sort for the first function
    FILE* writonfile1=fopen("output1.txt","w");//the first file output for n^2 logn
    FILE* writonfile2=fopen("output2.txt","w");//the second file output for n(log(n)))^2
    for(int i=0; i<n; i++)
    {
       fprintf(writonfile1,"%d\n",a[i]);//write on file for function 1
       fprintf(writonfile2,"%d\n",b[i].index);//write on file for function 2

    }
   /* delete[] a;
    fclose(file);
    fclose(writonfile1);
    fclose(writonfile2);*/

}
void functionForWholeGenome()
{
    s=new char[N];
    line=new char[200];
    FILE* file=fopen("genome.fasta.txt","r");
    fscanf(file,"%[^\n\r] ",s);//ignoring the id of genome
    s[0]=0;
    while(true)
    {
        fscanf(file,"%s",line);
        if(line[0]=='>')break; //to stop when the genome is over
        strcat(s,line);
    }
    n=strlen(s);//the capacity of the genome in the array
    suffix* b=new suffix[n]; //struct of order and index
    for(int i=0; i<n; i++)
    {
        //filling the suffix
        if(s[i]=='A')
            b[i].order=0;
        else if(s[i]=='C')
            b[i].order=1;
        else if(s[i]=='G')
            b[i].order=2;
        else if(s[i]=='T')
            b[i].order=3;
        b[i].index=i;
    }
    sort(b,b+n,compare2);//sorting for the second function the first time to sort by orders to make it easy to see the same orders

    suffixarray(b); //change the suffix array and sort it
    FILE* writonfile3=fopen("output3.txt","w");//output for whole genome
    for(int i=0; i<n; i++)
    {
        fprintf(writonfile3,"%d\n",b[i].index);//write on file for function 2

    }
   /* delete[] b;
    delete[] s;
    delete[] line;
    fclose(file);
    fclose(writonfile3);*/
}
char* te;//for testcases
int sizee;//size each testcase
bool compare4(int x,int y) //same as compare1
{
    int i=x,j=y;
    if(i>j) //to iterate until reaching the smaller the last index of suffix
    {
        while(i<sizee)
        {
            if(te[i]<te[j])
            {
                return true;
            }
            else if(te[i]>te[j])
            {
                return false;
            }
            i++;
            j++;
        }
        return true;
    }
    else
    {
        while(j<sizee)
        {
            if(te[i]<te[j])
            {
                return true;
            }
            else if(te[i]>te[j])
            {
                return false;
            }
            i++;
            j++;
        }
        return false;
    }
}
void outputconsole(char test[])//for testcases
{

    int* a=new int[sizee];
    for(int i=0; i<sizee; i++)
    {
        a[i]=i;//initialization of array a that works n^2(log(n))
    }
    sort(a,a+sizee,compare4); //sort for the first function
    cout<<"test "<<tt<<": ";
    tt++;
    for(int i=0; i<sizee; i++)
    {
        cout<<a[i]<<" ";//output sorted testcases

    }
    cout<<"\n\n";
}
void testcases()
{
    char test1[]="AAAAAAAAAAAAAAA";
    char test2[]="CCCCCCCCCCCCCCC";
    char test3[]="GGGGGGGGGGGGGGG";
    char test4[]="TTTTTTTTTTTTTTT";
    char test5[]="AAACCCGGGGTTTTGGGG";
    char test6[]="TTACGCCACCAGAT";
    char test7[]="CATTATTTATCTATGGAGGTGTTGGTTTAGGAAA";
    char test8[]="CGCTTTGAATGGGGGCTAATTGTTGATATTACGCCACCAGATTATGA";
    char test9[]="GCCAAAGTGATTTACACATC";
    char test10[]="TTTTTAAAAAAAA";
    char test11[]="AAAAAACCCCCTTTTTTGGGGG";
    char test12[]="TTGGGAAAAAGTGCTTGAAATTGCTCAAGAAAAATTATCAGCTGTAAGTTACTCAACTTTCCTAAAAGAT";
    char test13[]="TGATCGTATTTTTAATCACAGGT";
    char test14[]="ACTATCATTGCAATTATTTCTGCAGTTACAGTAACTGTATTGTGTTTT";
    char test15[]="TATGTAAAATAAA";
    char test16[]="TAGCAAAAAGTCATAGAACGAGTAATG";
    char test17[]="GCAAGACGTTGAAGTATTAATT";
    char test18[]="AATCTGATACGCTCACATGCCTG";
    char test19[]="ATCACATTTAGCATTAGCA";
    char test20[]="GAACGTATTATACCGATAATCC";
    char test21[]="TTACACATGATCGTCAATTTC";
    char test22[]="AATACGGGATAATTATGATGAAC";
    char test23[]="CTGACGAAACGTTTGGCGTCGCCATTA";
    char test24[]="GAAAGAACAATGACAAATTACACAGTAGAT";
    char test25[]="TAATCAGAAAATTCTGATATACAAATCGTCTATGTTAAGATTGG";
    char test26[]="CATTATTCAACAGACGCCTCATGGTGAGGGGTATACATTAAACATCCCTTACATTATCGCGCTCATTCCG";
    char test27[]="AAGGAGGAAAGAACAATGACAAATT";
    char test28[]="CTATATTCGTATTAGGAAAACCTGTTGGTAT";
    char test29[]="ACACAAACATCATCACTTAGAAAGCACCATT";
    char test30[]="CCAAATGAATTTAACGTGGTCGCTACTCAAG";
    //test 1
    int t=(sizeof(test1)/sizeof(test1[0]))-1;//size of the char array
    sizee=t;//size of the char array
    te=test1;
    outputconsole(test1);
    //test 2
    t=(sizeof(test2)/sizeof(test2[0]))-1;
    sizee=t;
    te=test2;
    outputconsole(test2);
    //test 3
    t=(sizeof(test3)/sizeof(test3[0]))-1;
    sizee=t;
    te=test3;
    outputconsole(test3);
    //test 4
    t=(sizeof(test4)/sizeof(test4[0]))-1;
    sizee=t;
    te=test4;
    outputconsole(test4);
    //test 5
    t=(sizeof(test5)/sizeof(test5[0]))-1;
    sizee=t;
    te=test5;
    outputconsole(test5);
    //test 6
    t=(sizeof(test6)/sizeof(test6[0]))-1;
    sizee=t;
    te=test6;
    outputconsole(test6);
    //test 7
    t=(sizeof(test7)/sizeof(test7[0]))-1;
    sizee=t;
    te=test7;
    outputconsole(test7);
    //test 8
    t=(sizeof(test8)/sizeof(test8[0]))-1;
    sizee=t;
    te=test8;
    outputconsole(test8);
    //test 9
    t=(sizeof(test9)/sizeof(test9[0]))-1;
    sizee=t;
    te=test9;
    outputconsole(test9);
    //test 10
    t=(sizeof(test10)/sizeof(test10[0]))-1;
    sizee=t;
    te=test10;
    outputconsole(test10);
    //test 11
    t=(sizeof(test11)/sizeof(test11[0]))-1;
    sizee=t;
    te=test11;
    outputconsole(test11);
    //test 12
    t=(sizeof(test12)/sizeof(test12[0]))-1;
    sizee=t;
    te=test12;
    outputconsole(test12);
    //test 13
    t=(sizeof(test13)/sizeof(test13[0]))-1;
    sizee=t;
    te=test13;
    outputconsole(test13);
    //test 14
    t=(sizeof(test14)/sizeof(test14[0]))-1;
    sizee=t;
    te=test14;
    outputconsole(test14);
    //test 15
    t=(sizeof(test15)/sizeof(test15[0]))-1;
    sizee=t;
    te=test15;
    outputconsole(test15);
    //test 16
    t=(sizeof(test16)/sizeof(test16[0]))-1;
    sizee=t;
    te=test16;
    outputconsole(test16);
    //test 17
    t=(sizeof(test17)/sizeof(test17[0]))-1;
    sizee=t;
    te=test17;
    outputconsole(test17);
    //test 18
    t=(sizeof(test18)/sizeof(test18[0]))-1;
    sizee=t;
    te=test18;
    outputconsole(test18);
    //test 19
    t=(sizeof(test19)/sizeof(test19[0]))-1;
    sizee=t;
    te=test19;
    outputconsole(test19);
    //test 20
    t=(sizeof(test20)/sizeof(test20[0]))-1;
    sizee=t;
    te=test20;
    outputconsole(test20);
    //test 21
    t=(sizeof(test21)/sizeof(test21[0]))-1;
    sizee=t;
    te=test21;
    outputconsole(test21);
    //test 22
    t=(sizeof(test22)/sizeof(test22[0]))-1;
    sizee=t;
    te=test22;
    outputconsole(test22);
    //test 23
    t=(sizeof(test23)/sizeof(test23[0]))-1;
    sizee=t;
    te=test23;
    outputconsole(test23);
    //test 24
    t=(sizeof(test24)/sizeof(test24[0]))-1;
    sizee=t;
    te=test24;
    outputconsole(test24);
    //test 25
    t=(sizeof(test25)/sizeof(test25[0]))-1;
    sizee=t;
    te=test25;
    outputconsole(test25);
    //test 26
    t=(sizeof(test26)/sizeof(test26[0]))-1;
    sizee=t;
    te=test26;
    outputconsole(test26);
    //test 27
    t=(sizeof(test27)/sizeof(test27[0]))-1;
    sizee=t;
    te=test27;
    outputconsole(test27);
    //test 28
    t=(sizeof(test28)/sizeof(test28[0]))-1;
    sizee=t;
    te=test28;
    outputconsole(test28);
    //test 29
    t=(sizeof(test29)/sizeof(test29[0]))-1;
    sizee=t;
    te=test29;
    outputconsole(test29);
    //test 30
    t=(sizeof(test30)/sizeof(test30[0]))-1;
    sizee=t;
    te=test30;
    outputconsole(test30);
}
int main()
{
    //clock_t before=clock();
    functionFor10000Gene();//function 1 and 2 for 10000 gene
    functionForWholeGenome();//function 2 for whole genome
    testcases();//30 testcase
    //clock_t after=clock();
    //cout<<(after-before-0.0)/CLOCKS_PER_SEC;
    ///the time in function 1 =0.2sec
    ///the time in function 2=10sec
    return 0;
}
