
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>

using namespace std;

///【1.一些关于内存的概念问题】===================================================================================
//1.内存泄漏：一个内存被占用，但是无法寻到它。宝藏内存。
//          一般都是因为内存回收失败引起的
//          还有就是忘记回收，比如一个结构体的实例化。

//2.重复释放：释放一个已经为空的空间
            int* temp_buffer1=new int[100];
            int* temp_buffer2=temp_buffer1;
            int* temp_buffer3=temp_buffer2;

            delete[] temp_buffer1;
            delete[] temp_buffer2;
            delete[] temp_buffer3;
//          这些都是重复释放！buffer123都指向同一块区域，
//          这块区域只要释放一次就够了！

//3.坏指针问题：意思是一个指针没有按预期指位置。
//                比如一些随机的内存位置被修改了，而指针依旧。
//                所以每个指针都记得要初始化哟！！！
//                没有的话也要用NULL顶着。千万不能空

//4.超量写内存：典型的问题就像数组越界
                char *new_string(char *s){
                    int len=strlen(s)
                    char *new_s=new char[len]
                    //忽略了'\0'!这里应该是len+1
                    strcpy(new_s,s);
                    return new_s;
                }














