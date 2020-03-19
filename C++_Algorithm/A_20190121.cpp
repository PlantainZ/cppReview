
#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<memory.h>
using namespace std;

//【1.大整数乘法】
#define SIZE 14
//返回位数为size1+size2
int* multi(int* num1,int size1,int* num2,int size2){
    //这里如果传数组进来，参数一定要这样写：int num1[]
    int size=size1+size2;
//申请空间建立一个int型的长度为120数组,a 指向数组第一个元素的地址
    int* ret=new int[size];     //这是积数组,woc注意形式，死在这里！
    //记得即便是数组，指针分配的时候也只有在右边才写长度
    //是个指针呢！！！！只有指针才能这样赋值啦！！！！
    int i=0;

    memset(ret,0,sizeof(int) *size);//把ret所在内存块的前size个字节全都初始化为0
    //memset操作经常用于数组\结构体初始化，记得它在memory.h
    //sizeof(int *p),表示计算指向整型的指针变量p所占的字节数
    //Here,the【sizeof(int)*size】,这里的*是表示乘法的意思,
    //表示大小为size个int
    for(i=0;i<size2;i++){
        int k=i;
        for(int j=0;j<size1;++j)    ret[k++]+=num2[i]*num1[j];
        //每个乘数与被乘数相乘，积数组的每一位都会有得数
    }

    for(i=0;i<size;++i){
        if(ret[i]>=10){
            ret[i+1]+=ret[i]/10;
            ret[i]%=10;
        }
    }
    return ret;

}

int main(int argc,char**argv){
    int num1[SIZE]={1,2,3,4,5,6,7,8,9,1,1,1,1,1};//第一个大整数，倒着读
    int num2[SIZE]={1,1,1,2,2,2,3,3,3,4,4,4,5,5};//第二个大整数，倒着读

    //倒着输入乘数和被乘数的时候栽过！！！
    //倒着输出result的时候又栽过！！！

    //如果想要求int[]的长度呢，其实可以这样：
    //cout<<sizeof(num1)/sizeof(*num1)<<endl;

    int* ret=multi(num1,SIZE,num2,SIZE);
    //woc我竟然在ret数组的大小上卡了一下
    for(int i=SIZE*2-1;i>=0;i--)    //此处捕获！倒着输出的标准：i>=0
    cout<<ret[i];         //不换行的写法！get
    delete[] ret;  //释放内存

    return 0;
}










