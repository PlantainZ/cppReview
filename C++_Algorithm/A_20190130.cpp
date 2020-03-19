
#include<stdio.h>
#include<iostream>
#include <vector>
#include <string>
#include <math>

#define  MAXCHAR 256
using namespace std;

///【1.BMH算法】
void preProcess(const char *patt,int m,int bmBc[]){
    //大傻瓜！！！匹配的时候一定要写成char *!!!!!
    int k=0;        //这里的m是patt的长~
    for(k=0;k<MAXCHAR;k++)  bmBc[k]=m;  //一共有256个呢
    for(k=0;k<m-1;k++)  bmBc[patt[k]]=m-1-k;  //注意只写到最后一个字符的前面
    //模式串最后一个字符的bmBc依然是m啊~
}

int BMH(string s,string p)
{
    int bmBc[MAXCHAR];
    int m=p.length();
    int n=s.length();

    if(m>n) return -1;

    const char *patt=p.c_str();
    const char *text=s.c_str();
    //注意 传入函数的变量，类型要一一对应
    preProcess(patt,m,bmBc);

    int k=m-1;
    while(k<n){
        int j=m-1;
        int i=k;
        while(j>=0 && text[i]==patt[j]){j--;i--;}
        //如果都相等，那么都继续往前匹配

        if(j=-1) return i+1; //如果匹配能够结束
        //那么就返回文本指针的，能够匹配的上的第一个字符的位置
        k+=bmBc[text[i]];//匹配不上，就找一下长串当前失配字母的bmBc[]
    }
    //如果写成了函数：千万不能在这里加return -1!!!!!
}














