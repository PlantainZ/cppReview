#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>

///【1.基础：template||ListNode类】
/*
通用类型标示符，例如这里的T，称为类型参数，
这意味着它们类似于变量，但赋给他们的不能是数字，
而只能是类型。

为容器类提供可重用代码是引入模版的主要动机。
*/
// function template,函数模板
template <class T>
T GetMax (T a, T b) {
    T result;
    result = (a>b)? a : b;
    return (result);
}

int main () {
    int i=5, j=6, k;
    long l=10, m=5, n;
    k=GetMax(i,j); //传入的是两个int,即T此时为int
    n=GetMax(l,m); //传入的是两个long，即T此时为long

    cout << k << endl; //6
    cout << n << endl; //10
    return 0;
}


//这里解释模板类
template <class T>
class test{
private:
    T a,b;
public:
    test(T m,T n){
        a=m;
        b=n;
    }

    T max(){return (a>b)?a:b;}
    T min();
};

template<class T>
T test<T>::min(){
    return (a>b)?b:a;
};

int _tmain(int argc, _TCHAR* argv[])
{
    test <int> test1(2,3);
    cout<<test1.max()<<endl;
    cout<<test1.min()<<endl;
    test<float> test2(32.12,12.458);
    cout<<test2.max()<<endl;
    cout<<test2.min()<<endl;
    test<char> test3('a','A');
    cout<<test3.max()<<endl;
    cout<<test3.min()<<endl;
    return 0;
}


//然后更复杂的：
template<class T>//声明一个类模板，虚拟类型名为T
//实现类的成员函数的复用而不用受数据类型的影响
class ListNode{//类模板名为ListNode
    T data;
    ListNode<T> *link;//getter & setter 传进来传出去的都是指针
    //因为这里本来就是指针呀！

public:
    ListNode():link(NULL){}//小心！构造函数有参数，这里是不用分号的！！
    //只要用户设置过自己的构造函数，无论是有参数还是没参数
    //系统都不会再为用户生成构造函数啦。
    //它不可以有返回值,void也不行
    //由于构造函数设计的初衷是为对象初始化，
    //即初始化对象的数据成员，因此构造函数不能声明为const
    ListNode(T value):link(NULL),data(value){}
    //同时也可以定义多个构造函数（高逼格说法：构造函数允许重载）
    //构造函数初始化列表在构造函数名后添加一个冒号，
    //冒号后是以逗号分隔的数据成员列表，
    //每个数据成员后跟一个放在圆括号中的初始化形式。

    //如果类包含内置或复合类型的成员，则不能依赖编译器来合成默认构造函数，
    //因为编译器无法初始化复合类型的成员
    ~ListNode(){};

    void SetLink(ListNode<T> *next);//1.指向别的指针~
    void SetData(T value);//2.
    ListNode<T> *GetLink();//这里是返回下一个的意思~~~返回一个指针。
    T& GetData();//4.在函数返回区里的多是引用和指针，这里返回一个引用
    //返回一个引用之后，对面就能接受到这个数据的别称
    //就可以进行输出！
    //注意区分：  &T是T的地址，T&是T的引用~
};

//1.补充知识点：每个函数前都要加template<T>,是因为
//要给类做模板声明，让编译器明白，ListNode<T>是一个模板类
template<class T>//小心!除了类型，其它都要放到母类后边~~
//记得母类不可以忘记 [ <T> ] !!
void ListNode<T>::SetLink(ListNode<T> *next){
    link=next;
}
//2.
template<class T>
void ListNode<T>::SetData(T value){
    data=value;
}
//3.
template<class T>
ListNode<T>* ListNode<T>::GetLink(){
    return link;
}
//4.这里的T& 就相当于返回相应的类型啊。
//因为毕竟没办法把类型实例化嘛，是吧只能用&了
template<class T>
T& ListNode<T>::GetData(){
    return data;
}

int main(){
    listNode<int> a,b;
//    listNode<int> *c=&b;
    a.setData(5);
    b.setData(9);
    a.setLink(&b); //参数指定是指针，所以传入b的地址生成指针。
    cout<<a.getData()<<endl;
    cout<<a.getLink()->getData()<<endl; //getLink()之后返回的是一个指针。
    //注意->代表：通过指针访问所指对象，然后调用对象的函数的意思。
    //注意这里ListNode<T> & ListNode<T>* 的区别，传入和放出都是些什么。
}


///【2.List类的定义】
//list类很特别哦，封装的数据成员有表头指针和表尾指针
template<class T>
class List{
    ListNode<T> *head;
    ListNode<T> *tail;

public:
    List();
    ~List();

    bool AddTail(T value);
    bool RemoveTail();
    bool InsertAt(int index,T value);
    bool RemoveAt(int index);

    T& GetAt(int index);
    bool IsEmpty();
    int GetCount();
    void RemoveAll();

    ListNode<T>* GetHead();
    ListNode<T>* GetTail();
    ListNode<T>* GetNodeAt(int index);
    ListNode<T>* GetCur();
    ListNode<T>* TowardCur();
};

//首先是向表尾加入新结点的成员函数:
template<class T>
bool List<T>::AddTail(T value){
    ListNode<T>* add=new ListNode<T> (value);//初始化一个指针，指向一个链表空间
    tail->SetLink(add);//然后使尾巴指向它
    tail=tail->GetLink();//尾巴移动
    tail->SetLink(NULL)；
    if(tail!=NULL) return true;
    else return false;
}

///【3.有序链表的合并算法】
List<int> listFirst;
List<int> listSecond;
//初始化链表listFirst;
listFirst.AddTail(1);
listFirst.AddTail(6);
listFirst.AddTail(7);
listFirst.AddTail(9);
listFirst.AddTail(13);
//初始化链表listSecond；
listSecond.AddTail(0);
listSecond.AddTail(3);
listSecond.AddTail(4);
listSecond.AddTail(10);

while(listSecond.GetCount()!=0){//要拆出来插入别的列表，
    //所以主要还是看它还有没有剩余，listFirst是从大到小排
    //步骤：被插链表指针-比大小，往后移动。
    //没到尾巴就插入，到了尾巴就向尾巴上加
    int indexFirst=0;
    //每次把listSecond的第一个数按序插入到listFirst中，
    //while循环语句寻找插入位置
    while(listSecond.GetAt(0)>listFirst.GetAt(indexFirst)){

        ++indexFirst;
        if(indexFirst==listFirst.GetCount()) break;
        //如果已经到表尾，就结束循环
    }

    if(indexFirst==listFirst.GetCount()){//插入在firstList链尾
        listFirst.AddTail(listSecond.GetAt(0));
        //listSecond的首部元素插入listFirst的尾部
        listSecond.RemoveAt(0);
    }else{
        listFirst.InsertAt(indexFirst,listSecond.GetAt(0));
        listSecond.RemoveAt(0);
    }
}









