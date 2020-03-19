//content:
//【1.基础：class】
//【2.基础：关于引用符号&】
//【3.基础：补上char**，多维指针这个知识点】
//【4.找出第一个大于参考值的数字】
//===============================================
#include<stdio.h>
#include<iostream>
using namespace std;

//chapter 1!!!
///【1.基础：class】===============================================================================================
class Student{
    //这两个变量也可以放进public里边，只是如果不声明保护程度
    //它们就会被默认为私有类型。
    //另外，类可以这样继承：class Student2:public Student{..}
    //上边的public可以替换为Protected private，表示父类变量的最低保护程度
    string name;
    int age;

//关于protected 和private,这里解释：
//保护成员和私有成员很相似，但是就是在子类中，
//可以访问父类的protected成员，外部不可以哦！！！
//public是外部都可以访问！
//而私有成员是父类独有的，只能由父类自己定义的函数访问。

//等级划分也就是外部>>子类>>自己类
public:
    Student():name(""),age(0) {}    //应该可以叫做构造函数吧！设置初始数据
//    Student();    //是构造函数声明！
//    ~Student();   //是析构函数声明！

    void setAge(int age){this->age=age;}
    int getAge(){return age;}
    void set_name(string name){this->name=name;}
    string getName(){return name;}
};//这里！！！踏马的！！！卡了1小时！！！
//沃靠，我要找侯爷给它头砍爆！！记得加踏lailai的分号！！



//c++有个东西叫做范围解析符号！可以这样使用：
int Student::getAge(){  return age; }
//Student::Student(){xxx}   //这是写构造函数呦！
//尼玛，构造和析构函数一定要放在Public里边才能搞定！
//析构函数：就是当删除所创建的对象时候就会执行。好规范的样子！
//Student::~Student(){  cout <<"the object is being deleted!"<<endl;}

void increment_age(Student s){
    s.setAge(s.getAge()+1);
}

int main(){
    Student s;
    s.set_name("Nancy");
//    s.set_name("WUmingshi");
//    s.setAge(20);

//    increment_age(s);
    cout << "student's name="<<s.getName()<<endl;
    return 0;

}



///【2.基础：关于引用符号&】=======================================================================================
//这里的&不是取地址符号，而是引用符号，是C++对C的一个重要补充。
//系统没有为这个新变量分配空间，而是使用传给它变量的空间
//在这个函数里，传进来的变量就叫r这个新名字，就是旧变量的别名啦！
//
//int &a=b;这样是声明a是变量b的引用
//如果是int &a;这样就是错的，没有指定a代表哪一个变量。
//单纯用变量名作为实参，DATA传递是单向的，但是引用可以是双向哒！！
//
//在c语言中不是有指针吗，用指针进行参数传递不也是双向的吗？
//其实其本质上也是值传递，只不过是将变量的地址传给指针，
//通过指针获取变量的值，这样做虽能得到结果，
//但通过指针运算符去访问有关变量，比较麻烦。
//指针变量要另外开辟内存单元，其内容是地址。
//而引用不是一个独立的变量，并不占用内存单元
//
//这样设置之后，以后引用这个函数，就不用再写&a了，
//而是直接传a,系统默认传的是它的地址

//平时定义变量如果使用引用，就以后搞指针的地方再也不用写
//指针运算符*啦！直接写a！它会知道哒！
//
//但是要注意哦，char c[6]="hello";
//char &rc=c;//错误的！！！！
//因为数组是一串地址，它并不是一个变量
//必须int (&b)[6] = c
void xAdd(int& r){
    int a=2;

    int &b=a;//这个声明语句中的&是一个引用
    int *p=&b;//这个指针初始化语句中的&是取地址运算符
//     上面一行等价于 int *p=&a;
    int *ptr=&a;
    int *&new_ptr=ptr;
    //&与p靠得最近，所以p是一个引用，这个引用的类型是int*，
    //也就是一个指针变量的引用，但是必须初始化，否则也错。
    cout<<&ptr<<" "<<&new_ptr<<endl;
//    但是不能定义指向引用类型的指针变量，不能写成
    int &*w=&a;//企图定义指向引用类型的指针变量p，错误
//    因为引用不是一种独立的数据类型，因此不能建立指向引用类型的指针变量。
//
//    可以建立指针变量的引用如
    int i=5;
    int *s=&i;
    int * &pt=s;//建立指针变量p的引用pt
//引用变量pt代表一个int *类型的数据对象(即指针变量)
//
//
//}

//另外关于返回引用值的函数
float temp; //定义全局变量temp
float fn1(float r); //声明函数fn1
float &fn2(float r); //声明函数fn2

float fn1(float r) //定义函数fn1，它以返回值的方法返回函数值
{
　temp=(float)(r*r*3.14);
　return temp;
}//返回float型数

float &fn2(float r) //定义函数fn2，它以引用方式返回函数值
{
　temp=(float)(r*r*3.14);
　return temp;
}//返回float引用数

void main() //主函数
{
　float a=fn1(10.0); //第1种情况，系统生成要返回值的副本（即临时变量）
　float &b=fn1(10.0); //第2种情况，可能会出错（不同 C++系统有不同规定）
　//不能从被调函数中返回一个临时变量或局部变量的引用
　float c=fn2(10.0); //第3种情况，系统不生成返回值的副本
　//可以从被调函数中返回一个全局变量的引用
　float &d=fn2(10.0); //第4种情况，系统不生成返回值的副本
　//可以从被调函数中返回一个全局变量的引用
　cout<<a<<c<<d;
}



///【3.基础：补上char**，多维指针这个知识点】=====================================================================
int main(int argc,char **argv){}
//char **x ； 定义一个二维指针变量x，x中可以存储一个char *类型变量的地址
//char *x ; 定义一个一维指针变量x，x中可以存储一个char类型变量的地址
//一维指针：通过指针变量x的值（地址），可以找到数据
//二维指针：通过指针变量x的值（地址），找到的还是个地址值，再通过这个新的地址值，才能找到数据

///【4.找出第一个大于参考值的数字】================================================================================
void first_bigger(int*& p,int threshold){
    while(*p <=threshold){p++;}   //这是个引用指针
}

int main(int argc,char** argv){
    int numbers[]={0,12,32,44,33,5,85,45,100,75};
    char tmp[8]={'c','d','e','f','a','g'};//自己注意字符数组的格式
    int* result=&numbers[0];

    cout<<"Begin at:"<<*result<<endl;
    first_bigger(result,60);  //正片是个指针
    cout<<"Result is:"<<*result<<endl;
    return 0;
}











