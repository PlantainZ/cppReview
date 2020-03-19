
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>

using namespace std;

///【1.KMP算法】
void preKmp(const char *x,int m,int kmpNext[]){
    int i,j;
    i=0;
    j=kmpNext[0]=-1;
    while(i<m){//i是寻找指针，j是命令指针
        while(j>-1 && x[i]!=x[j])   j=kmpNext[j];
        //老手法，如果不匹配，就直接等价于在j处不匹配
        //这一对不匹配的时候，和前边一个还能比一下，
        i++;j++;//抬走，下一对
        if(x[i]==x[j]) kmpNext[i]=kmpNext[j];
        //遇到的下一对是一样的。
        //如果它们不匹配，直接把MP算法会干的“回溯，再匹”
        //的结果直接干了。
        //比如abc abd，到d时MP会回溯到c，然后又不匹配，
        //直接撵回，和第一个a比
        else    kmpNext[i]=j;
        //遇到的下一对不相同，还是继续看j吧。
    }
}

void KMP(string p,string t){//和mp完全一样的操作
    int m=p.length();
    int n=t.length();

    if(m>n){
        cerr<<"Unsuccessful match!"<<endl;
        return;
    }

    const char *x=p.c_str();
    const char *y=t.c_str();
    //一定要复制！！啊const指针！

    int i=0,j=0,kmpNext[m+1];
    memset(kmpNext,0,sizeof(int)*(m+1));

    preKmp(x,m,kmpNext);

    i=j=0;
    while(j<n){
        while(i>-1 && x[i]!=y[j]) i=kmpNext[i];
        i++;j++;
        if(i>=m){
            cout<<"Matching index found at:"<<j-i<<endl;
            i=kmpNext[i];
        }
    }
}










