///【1.内联函数】
#include <stdio.h>
#define FUN(a,b) ((a) < (b) ? (a) : (b))

inline int fun(int a,int b){
    return a < b ? a : b; //如果a<b  成立 a=a 否则a=b
}//一般的不写inline开头的函数都默认是内联的！别紧张！

int main(int argc, char *argv[]){
    int a = 1,b=3;
    int val = FUN(++a,b);
//如果调用宏FUN int val = FUN(++a,b);
//展开就是  int val = ((++a = 2) < (b) ? (++a = 3) : (b));  这里的Val = 3

//而调用 fun 这个函数  int val = 2
//从而说明 宏代码块有一个缺点就是宏代码块只是做内容的替换。
    printf("Begin...\n");
    printf("val = %d\n",val);
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    printf("End...\n");
    return 0;
}

//inline fun不能...1.存在任何形式的循环语句 / 2.过多的条件判断语句 / 3.对该函数进行取地址操作

//C++编译器直接将函数体插入函数调用的地方，从而内联函数没有普通函数调用时的额外开销。（压栈、跳转、返回）。
//注意：C++编译器不一定满足函数的内联请求，
//也就是说使用inline 关键字声明内联函数可能会被编译器拒绝。从而建立内联失败




///【2.虚函数·实践题目】===========================================================================================
#include <stdio.h>
#include <iostream>
using namespace std;
class A{
public:
    void virtual print(){
      cout << "A" << endl;
    }
};

class B : public A{
public:
    void virtual print(){
        cout << "B" << endl;
    }
};

int main()
{
    A* pA = new A(); //初始化一个A的指针，并生成对象
    pA->print(); //->:调用所指对象的函数
    B* pB = (B*)pA; //初始化一个B类的指针，叫pB，并且将pA强制转型为 A派生的B指针类
    pB->print();
    delete pA, pB;

    pA = new B(); //pA生成一个B类
    pA->print(); //调用对象的函数
    pB = (B*)pA; //然后转型成B类型的指针。返回的是指针值。
    pB->print();
    cout<<pA<<endl;
    cout<<pB<<endl;
}//输出：AABB

//对了，还有一个函数叫做isalpha(a)，是判断a是否是字符的，返回1/0
//当然还有对应的函数isdigit(b)；




///【3.复制构造函数：用现成对象来初始化另一个对象】=========================================================
point pt1(3,4); //构造函数 p
point pt2(pt1); //复制构造函数,相当于下面这句话。
point pt3 = pt1;//复制构造函数
//当我们自己定义了有参构造函数时，系统不再提供默认构造函数


/* 拷贝构造函数在以下三种情况会自动调用：
　　1.当把一个已经存在的对象赋值给另一个新的对象时。
　　2.当实参和形参都是对象，进行形参和实参的结合时。
　　3.当函数的返回值是对象，函数调用完成返回时。
*/

#include <iostream>
using namespace std;
class point{
private:
    int xPos;
    int yPos;
public:
    point(int x = 0, int y = 0){
        cout << "调用构造函数" << endl;
        xPos = x;
        yPos = y;
    }

    point(const point & pt){//复制构造函数的定义及实现
        cout << "调用复制构造函数" << endl;
        xPos = pt.xPos;
        yPos = pt.yPos;
    }

    void print(){
        cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
    }
};


#include "point.h"

int main()
{
    point pt1(3, 4);
    pt1.print();

    point pt2 = pt1; //等价于point pt2(pt1)，调用复制构造函数
    pt2.print();

    point pt3;
    pt3.print();

    point pt4(pt3); //等价于point pt4＝pt3，调用复制构造函数
    pt4.print();

//  pt2 = pt1;      //调用默认的赋值运算符重载函数
//  pt2.print();
    return 0;
}


#include <iostream>
using namespace std;

class CPoint
{
private:
    int x;
    int y;

public:
    //缺省构造函数,如果定义类时未指定任何构造函数，
    //系统将自动生成不带参数的缺省构造函数
    CPoint()
    {
        cout << "默认构造函数 " << this << " " << endl;
        x = 0;
        y = 0;
    }

    //带一个参数的可用于类型转换的构造函数
    CPoint(int ix)
    {
        cout << "1参数构造函数 " << this << " " << endl;
        x = ix;
        y = 0;
    }

    //带参数的构造函数
    CPoint(int ix, int iy)
    {
        cout << "2参数构造函数 " << this << " " << endl;
        x = ix;
        y = iy;
    }

    //拷贝构造函数,如果此函数不定义，系统将生成缺省拷贝构造函数功能,
    //缺省拷贝构造函数的行为是：用传入的对象参数的成员初始化正要建立的对象的相应成员
    CPoint(const CPoint &cp){
        cout << "拷贝构造函数 " << this << " " << endl;
        x = cp.x;
        y = cp.y;
    }

    CPoint &operator=(const CPoint &cp){
        cout << "赋值重载函数 " << this << " " << endl;
        if (this != &cp){
            x = cp.x;
            y = cp.y;
        }
        return (*this);
    }

    //析构函数，一个类中只能有一个析构函数,如果用户没有定义析构函数，
    //系统会自动未类生成一个缺省的析构函数
    ~CPoint(){
        cout << "析构函数 " << this << " " << endl;
    }
};

void fun1(CPoint pt){}

CPoint fun2(){
    CPoint a;
    return a;
}

CPoint fun(CPoint a){
    return a;
}

int main(int argc, char* argv[])
{
    //第1类
//  CPoint pt1 = CPoint();
    //当有析构函数的时候，CPoint()不会生成调用构造函数生成临时的匿名对象。
    //当没有析构函数的时候，CPoint()会生成一个临时的匿名对象，等价于CPoint pt1;这句话只会调用无参构造函数，不会调用拷贝构造函数

//  CPoint pt2 = CPoint(1);
    //当有析构函数的时候，CPoint(1)不会生成调用构造函数生成临时的匿名对象。
    //当没有析构函数的时候，CPoint()会生成一个临时的匿名对象，等价于CPoint pt(1);这句话只会调用一个参数的构造函数，不会调用拷贝构造函数

//  CPoint pt3 = 1;
    //普通数据类型转换为类类型，利用相应的构造函数就可以实现。等价于CPoint pt(1);

    //第2类
    /*拷贝构造函数与赋值运算符重载函数的区别:
        1. 拷贝构造函数是用已经存在的对象的各成员的当前值来创建一个相同的新对象。
           在下述3种情况中，系统会自动调用所属类的拷贝构造函数。
             1.1  当说明新的类对象的同时，要给它赋值另一个已经存在对象的各成员当前值。
             1.2  当对象作为函数的赋值参数而对函数进行调用要进行实参和形参的结合时。
             1.3  当函数的返回值是类的对象，在函数调用结束后返回主调函数处的时候。
        2. 赋值运算符重载函数要把一个已经存在对象的各成员当前值赋值给另一个已经存在的同类对象
    */
    CPoint pt4;         //调用无参构造函数
//  CPoint pt5 = pt4;   //调用拷贝构造函数  属于1.1
//  fun1(pt4);          //调用拷贝构造函数  属于1.2
//  fun2();             //调用拷贝构造函数  属于1.3

//  CPoint pt6 = fun2();//调用无参构造函数，拷贝构造函数，此处如果没有写析构函数，则还会调用一次拷贝构造函数
    //因为函数返回会生成一个临时对象，然后再将这个临时对象赋值给pt6，所以多调用一次拷贝构造函数；如果有析构函数
    //则不会生成中间的临时变量，所以少一次拷贝构造函数的调用

    //还可以通过下面函数验证
//  CPoint pt7 = fun(pt4);
    //如果没有析构函数，会调用3次拷贝构造函数

    return 0;
}






