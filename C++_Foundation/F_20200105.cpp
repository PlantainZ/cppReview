
///【1.关于注释的补充】=========================================================================================
#if 0
   code
#endif
// #if 0 改成 #if 1 ，code 就会执行！！
// 测试时使用 #if 1 来执行测试代码，发布后使用 #if 0 来屏蔽测试代码。
//-------------------------------------------------------------------------------
#if condition
  code1
#else
  code2
#endif
//#if 后可以是任意的条件语句。
//如果 condition 条件为 true 执行 code1 ，否则执行 code2。
//--------------------------------------------------------------------------------




///【2.数据类型：枚举】===========================================================================================
enum color { red, green, blue } c;
c = blue;
//默认情况下，第一个名称的值为 0，第二个名称的值为 1，第三个名称的值为 2，以此类推。

//可以给名称赋予一个特殊的值，只需要添加一个初始值即可。比如下方green初始值 = 5
enum color { red, green=5, blue };
//blue 的值为 6，默认情况下，每个名称都会比它前面一个名称大 1。
//但 red 的值依然为 0。



///【3.变量声明:函数】===========================================================================================
//函数声明时，提供一个函数名，而函数的实际定义则可以在任何地方进行。

int func();// 函数声明
int main() { int i = func(); }// 函数调用
int func() { return 0; }// 函数定义




///【4.重修：存储类 关键字】===========================================================================================
//全局变量对所有的程序文件都是可见的。
//关于static==============================================================
/*static 存储类指示编译器在程序的生命周期内保持局部变量的存在，
而不需要在每次它进入和离开作用域时进行创建和销毁。
因此，使用 static 修饰局部变量可以在函数调用之间保持局部变量的值。

static 修饰符也可以应用于全局变量。
当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。

当 static 用在类数据成员上时，会导致仅有一个该成员的副本被类的所有对象共享。*/


//关于extern==================================================================
/*extern 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。
使用 'extern' 时，对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置。

有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，
可以在其他文件中使用 extern 来得到已定义的变量或函数的引用。
可以这么理解，extern 是用来在另一个文件中声明一个全局变量或函数。*/

//第一个文件：
#include <iostream>

int count ;
extern void write_extern();

int main()
{
   count = 5;
   write_extern();
}

//第二个文件：
#include <iostream>

extern int count;

void write_extern(void) {std::cout << "Count is " << count << std::endl;}


//关于thread_local================================================================
/*使用 thread_local 说明符声明的变量仅可在它在其上创建的线程上访问。
变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本。

thread_local 说明符可以与 static 或 extern 合并。
可以将 thread_local 仅应用于数据声明和定义，
thread_local 不能用于函数声明或定义。*/

thread_local int x;  // 命名空间下的全局变量
class X { static thread_local std::string s; };// 类的static成员变量
static thread_local std::string X::s;  // X::s 是需要定义的

void foo() { thread_local std::vector<int> v; } // 本地变量


///【5.Lambda匿名函数】
//格式：[capture](parameters)->return-type{body}

[](int x, int y){ return x < y ; }
//[]是匿名函数的标识符

[]{ ++global_x; } //没有返回值!

[](int x, int y) -> int { int z = x + y; return z + x; }
//一个临时的参数 z 被创建用来存储中间结果。
//如同一般的函数，z 的值不会保留到下一次该不具名函数再次被调用时。
//如果 lambda 函数没有传回值（例如 void），其返回类型可被完全忽略。

//Lambda表达式内可以访问当前作用域的变量，这是Lambda表达式的闭包（Closure）行为。
//与JavaScript闭包不同，C++变量传递有传值和传引用的区别。可以通过前面的[]来指定：

[]      // 沒有定义任何变量。使用未定义变量会引发错误。
[x, &y] // x以传值方式传入（默认），y以引用方式传入。
[&, x]  // x显式地以传值方式加以引用。其余变量以引用方式加以引用。
[=, &z] // z显式地以引用方式加以引用。其余变量以传值方式加以引用。

[&]     // 任何被使用到的外部变量都隐式地以引用方式加以引用。
[=]     // 任何被使用到的外部变量都隐式地以传值方式加以引用。
[this]() { this->someFunc(); }();
//注意：对于[=]或[&]的形式，lambda 表达式可以直接使用 this 指针。
//但是，对于[]的形式，如果要使用 this 指针，必须显式传入。




///【6.随机数】======================================================================================================================
//要先设置随机数种子，才能进行随机数获取
int i,j;
srand( (unsigned)time( NULL ) );// 设置种子

/* 生成 10 个随机数 */
for( i = 0; i < 10; i++ ){
  // 生成实际的随机数
  j= rand();
  cout <<"随机数： " << j << endl;
}




///【7.函数返回数组唯一方法：指针】================================================================================================
// 要生成和返回随机数的函数
int * getRandom( )
{
  static int  r[10];

  // 设置种子
  srand( (unsigned)time( NULL ) );
  for (int i = 0; i < 10; ++i)
  {
    r[i] = rand();
    cout << r[i] << endl;
  }

  return r;
}

// 要调用上面定义函数的主函数
int main (){
   // 一个指向整数的指针
   int *p;

   p = getRandom();
   for ( int i = 0; i < 10; i++ ){
       cout << "*(p + " << i << ") : ";
       cout << *(p + i) << endl;
   }

   return 0;
}




///【8.从函数返回指针】===================================================================================================================
//C++不支持在函数外返回局部变量的地址，除非定义局部变量为 static 变量。
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// 要生成和返回随机数的函数
int * getRandom( ){
//会生成 10 个随机数，并使用表示指针的数组名（即第一个数组元素的地址）来返回它们
  static int  r[10];

  // 设置种子
  srand( (unsigned)time( NULL ) );
  for (int i = 0; i < 10; ++i){
    r[i] = rand();
    cout << r[i] << endl;
  }

  return r;
}

// 要调用上面定义函数的主函数
int main (){
   // 一个指向整数的指针
   int *p;

   p = getRandom();
   for ( int i = 0; i < 10; i++ ){
       cout << "*(p + " << i << ") : ";
       cout << *(p + i) << endl;
   }

   return 0;
}




///【9.返回引用的函数】===============================================================================
#include <iostream>
using namespace std;
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double& setValues( int i ) { return vals[i]; }  // 返回第 i 个元素的引用

// 要调用上面定义函数的主函数
int main (){
   cout << "改变前的值" << endl;
   for ( int i = 0; i < 5; i++ ) { cout << "vals[" << i << "] = "<< vals[i] << endl; }

   setValues(1) = 20.23; // 改变第 2 个元素，放在等号前边哦！！！
   setValues(3) = 70.8;  // 改变第 4 个元素

   cout << "改变后的值" << endl;
   for ( int i = 0; i < 5; i++ ){
       cout << "vals[" << i << "] = ";
       cout << vals[i] << endl;
   }
   return 0;
}



///【10.函数：虚继承】==========================================================================================
#include <iostream>

using namespace std;
//基类

class D
{
public:
    D(){cout<<"D()"<<endl;}
    ~D(){cout<<"~D()"<<endl;}
protected:
    int d;
};

class B:virtual public D
{
public:
    B(){cout<<"B()"<<endl;}
    ~B(){cout<<"~B()"<<endl;}
protected:
    int b;
};

class A:virtual public D
{
public:
    A(){cout<<"A()"<<endl;}
    ~A(){cout<<"~A()"<<endl;}
protected:
    int a;
};

class C:public B, public A
{
public:
    C(){cout<<"C()"<<endl;}
    ~C(){cout<<"~C()"<<endl;}
protected:
    int c;
};

int main()
{
    cout << "Hello World!" << endl;
    C c;   //D, B, A ,C
    cout<<sizeof(c)<<endl;
    return 0;
}



///【11.函数：拷贝构造函数】==========================================================================================
class Line
{
   public:
      int getLength( void );
      Line( int len );             // 简单的构造函数
      Line( const Line &obj);      // 拷贝构造函数
      ~Line();                     // 析构函数

   private:
      int *ptr;
};

// 成员函数定义，包括构造函数
Line::Line(int len)
{
    cout << "调用构造函数" << endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
}

Line::Line(const Line &obj)
{
    cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
    ptr = new int;
    *ptr = *obj.ptr; // 拷贝值
}


