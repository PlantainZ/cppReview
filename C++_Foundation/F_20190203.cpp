
#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<stdafx.h>
#include<CirList.h>

using namespace std;

///【1.cirList的定义】
template<class t>
class CirList{
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* cur;

public:
    CirList();
    ~CirList();

    bool AddTail(T value);
    void RemoveThis();
    void RemoveAll();
    void SetBegin();
    int GetCount();
    ListNode<T>* GetCur();

    bool IsEmpty();
    T GetNext();    //注意这个getNext()，应该这样读：get,next.
    //表示返回cur指向的结点中存储的数据，
    //并在返回数据后将cur自动后移一个结点。
    //如果对表尾的话，会返回表尾的值，然后回到表头哟！
}
