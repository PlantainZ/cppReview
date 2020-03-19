///【1.C++读取 & 写入】
#include <fstream>
#include <iostream>
using namespace std;

int main ()
{
   char data[100];

   // 以写模式打开文件
   ofstream outfile;
   outfile.open("afile.dat");

   cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.getline(data, 100);

   // 向文件写入用户输入的数据
   outfile << data << endl;

   cout << "Enter your age: ";
   cin >> data;
   cin.ignore();

   // 再次向文件写入用户输入的数据
   outfile << data << endl;

   // 关闭打开的文件
   outfile.close();

   // 以读模式打开文件
   ifstream infile;
   infile.open("afile.dat");

   cout << "Reading from the file" << endl;
   infile >> data;

   // 在屏幕上写入数据
   cout << data << endl;

   // 再次从文件读取数据，并显示它
   infile >> data;
   cout << data << endl;

   // 关闭打开的文件
   infile.close();

   return 0;
}


///【2.文件位置指针】
// 定位到 fileObject 的第 n 个字节（假设是 ios::beg）
fileObject.seekg( n );

// 把文件的读指针从 fileObject 当前位置向后移 n 个字节
fileObject.seekg( n, ios::cur );

// 把文件的读指针从 fileObject 末尾往回移 n 个字节
fileObject.seekg( n, ios::end );

// 定位到 fileObject 的末尾
fileObject.seekg( 0, ios::end );




///【3.自定义异常】
#include <iostream>
#include <exception>
using namespace std;

struct MyException : public exception
{
  const char * what () const throw ()
  {//what()是异常类提供的一个公共方法，已被所有子异常类重载
    //返回异常产生的原因！
    return "C++ Exception";
  }
};

int main()
{
  try
  {
    throw MyException();
  }
  catch(MyException& e)
  {
    std::cout << "MyException caught" << std::endl;
    std::cout << e.what() << std::endl;
  }
  catch(std::exception& e)
  {
    //其他的错误
  }
}



///【4.内存动态分配：警惕自由存储区用完】
double* pvalue  = NULL;
if( !(pvalue  = new double ))
{
   cout << "Error: out of memory." <<endl;
   exit(1);

}
/*malloc() 函数在 C 语言中就出现了，在 C++ 中仍然存在。
但建议尽量不要使用 malloc() 函数。
new 与 malloc() 函数相比，其主要的优点是，new 不只是分配了内存，它还创建了对象。*/



///【5.内存动态分配：各维度数组】
//这是一维数组-------------------------
// 动态分配,数组长度为 m
int *array=new int [m]；

//释放内存
delete [] array;


//二维数组-------------------------------
#include <iostream>
using namespace std;

int main()
{
    int **p;
    int i,j;   //p[4][8]
    //开始分配4行8列的二维数据
    p = new int *[4];
    for(i=0;i<4;i++){
        p[i]=new int [8];
    }

    for(i=0; i<4; i++){
        for(j=0; j<8; j++){
            p[i][j] = j*i;
        }
    }
    //打印数据
    for(i=0; i<4; i++){
        for(j=0; j<8; j++)
        {
            if(j==0) cout<<endl;
            cout<<p[i][j]<<"\t";
        }
    }
    //开始释放申请的堆
    for(i=0; i<4; i++){
        delete [] p[i];
    }
    delete [] p;
    return 0;
}


//三维数组-------------------------------
#include <iostream>
using namespace std;

int main()
{
    int i,j,k;   // p[2][3][4]

    int ***p;
    p = new int **[2];
    for(i=0; i<2; i++)
    {
        p[i]=new int *[3];
        for(j=0; j<3; j++)
            p[i][j]=new int[4];
    }

    //输出 p[i][j][k] 三维数据
    for(i=0; i<2; i++)
    {
        for(j=0; j<3; j++)
        {
            for(k=0;k<4;k++)
            {
                p[i][j][k]=i+j+k;
                cout<<p[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    // 释放内存
    for(i=0; i<2; i++)
    {
        for(j=0; j<3; j++)
        {
            delete [] p[i][j];
        }
    }
    for(i=0; i<2; i++)
    {
        delete [] p[i];
    }
    delete [] p;
    return 0;
}


/*
    也并不一定就要用官方定义的数组类型，可以用自己定义的类型搞数组。
    如果要为一个包含四个自定义对象的数组分配内存，构造函数将被调用 4 次，
    同样地，当删除这些对象时，析构函数也将被调用相同的次数（4次）。
*/




///【6.命名空间的使用】
#include <iostream>
using namespace std;

// 第一个命名空间
namespace first_space{
   void func(){
      cout << "Inside first_space" << endl;
   }
}
// 第二个命名空间
namespace second_space{
   void func(){
      cout << "Inside second_space" << endl;
   }
}
int main ()
{

   // 调用第一个命名空间中的函数
   first_space::func();

   // 调用第二个命名空间中的函数
   second_space::func();

   return 0;
}


//当然也可以指定更小范围的空间：
#include <iostream>
using std::cout;

int main ()
{

   cout << "std::endl is used with std!" << std::endl;

   return 0;
}


///【7.函数模板】
#include <iostream>
#include <string>

using namespace std;

template <typename T>//返回两数最大值
inline T const& Max (T const& a, T const& b)
{
    return a < b ? b:a;
}
int main ()
{

    int i = 39;
    int j = 20;
    cout << "Max(i, j): " << Max(i, j) << endl;

    double f1 = 13.5;
    double f2 = 20.7;
    cout << "Max(f1, f2): " << Max(f1, f2) << endl;

    string s1 = "Hello";
    string s2 = "World";
    cout << "Max(s1, s2): " << Max(s1, s2) << endl;

   return 0;
}



///【8.预处理器】
#ifdef DEBUG
   cerr <<"Variable x = " << x << endl;
#endif
//--------------------------------------
#if 0
   不进行编译的代码
#endif
