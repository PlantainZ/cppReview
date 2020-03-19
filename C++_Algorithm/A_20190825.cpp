///【1.插入排序】
#ifndef INSERTSORT_H
//条件指示符#ifndef 的最主要目的是防止头文件的重复包含和编译。
#define INSERTSORT_H

#include <vector>
using namespace std;

class InsertSort{
private:
    int len;
    vector<int> list;

public:
    InsertSort(vector<int> _list,int _len);
    //构造函数
    void insert_sort();
    void out();
};
#endif // INSERTSORT_H

#include "InsertSort.h"
#include <iostream>

using namespace std;

InsertSort::InsertSort(vector<int> _list,int _len){
    for(int i=0;i<_len;i++) list.push_back(_list[i]);
    this->len = _len;
}

//直接插入排序
void InsertSort::insert_sort(){
    int insertNum;
    for(int i=1;i<len;i++){
        insertNum = list[i];
        int j=i;
        while(j>0 && insertNum<list[j-1]){
            list[j]=list[j-1];
            j--;
        }
        list[j] = insertNum;
    }
}

void InsertSort::out(){
    //输出排序后的数组，此处代码略了
}








///【2.折半插入排序】
#ifndef BINARYINSERTSORT_H
//条件指示符#ifndef 的最主要目的是防止头文件的重复包含和编译。
#define BINARYINSERTSORT_H

#include <vector>
using namespace std;

class BinaryInsertSort{
private:
    int len;
    vector<int> list;

public:
    BinaryInsertSort(vector<int> _list,int _len);
    //构造函数
    void binary_insert_sort();
    void out();
};
#endif // BINARYINSERTSORT_H

#include "BinaryInsertSort.h"
#include <iostream>
using namespace std;

Binary_InsertSort::BinaryInsertSort(vector<int> _list,int _len){
    for(int i=0;i<_len;i++) list.push_back(_list[i]);
    this->len = _len;
}

//=======================此处开始不同于直接插入排序================
void BinaryInsertSort::binary_insert_sort(){
    int middle;
    for(int i=0;i<len;i++){
        int insertNum = list[i];
        int left=0;
        int right=i-1;

        while(left <= right){
            middle = (left+right)/2;
            if(insertNum > list[middle]) left = middle+1;
            else right = middle-1;
        }//记住这两边的子树，都不取中点！！

        //出来的时候，left & right互换了位置。
        //即此时right在left左1的位置
        //但是这个时候的right已经无须再用到，所以只看left就可以了
        for(int j=i;j>left;j--) list[j] = list[j-1];
        list[left]=insertNum;
        //要将i插在left的位置，所以left和它后边的都要都循环右移一格
    }
}


void BinaryInsertSort::out(){}

















