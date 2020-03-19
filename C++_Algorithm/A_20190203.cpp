#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<stdafx.h>
#include<CirList.h>

using namespace std;

///【2.约瑟夫环的问题】
//问题：15个人排成一圈，并给他们1-15的编号。
//现在从1开始报数，报数字4的人退出队列。
//余下的人从退出者下一个位置开始继续刚才的报数，
//直到整个队列中只剩下一个人为止。请问这个人是几号？
int _tmain(int argc,_TCHAR* argv[]){
    CirList<int> jos;//新建了一个循环单向链表
    //初始化:注意链表的初始化和操作方式，必须黑盒~
    for(int i=1;i<16;i++) jos.AddTail(i);
    jos.SetBegin();//把指针放到head处，表示链表的开始

    int length=jos.GetCount();
    for(int i=1;i<length;i++){
        for(int j=0;j<3;j++) jos.GetNext();
        jos.RemoveThis();//remove之后会指向原来的下一个
    }

    cout<<jo.GetNext()<<endl;//只剩下一个人喽。
    system("PAUSE");
    return 0;
}

