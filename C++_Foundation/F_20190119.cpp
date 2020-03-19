//会了会了，可以删了
#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;

///【1.使用引用，找出比threshold大的数。】========================================================================
void compareNum(int*& p,int threshold){
    //这里，int*&是指针变量的引用，它有个规定就是必须初始化
    //另外补充：int &*p； 是不正确的，*与p靠得最近，所以p是一个指针，
    //但是这个指针的类型是int &,所以这个是错误的，
    // 因为不能创建引用的指针。
    while(*p<=threshold){p++;}    //就是给了这个指针另一个名字而已
}

int main(){
    int num[]={1,32,45,56,78,89,123,456};
    int* p=num;                 //要注意，这里是*p
    cout<<"*p="<<*p<<endl;
    compareNum(p,60);           //传进去也是指针
    //注意，这里传进去的是p，而不是*p
    cout<<"*p="<<*p<<endl;
}
