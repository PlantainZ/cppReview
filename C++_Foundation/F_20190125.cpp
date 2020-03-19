
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>

using namespace std;

///chapter 2!!!

///【1.分割字符串，输出词语】=====================================================================================
int main(int argc,char** argv){
    string str="高娜德 美国 计算机科学家 计算机程序设计艺术";
    string str_temp="";
    //===================知识点：assign()
    str_temp.assign(str);//这东西能copy str的内容。

    string result[4]={"","","",""};
    int position=0;

    //======================知识点：find() & substr() & length()
    for(int i=0;i<3;i++){//这里是为了填result做计数。
        position=str_temp.find(" ");//找到str_tmp中第一个空格的位置
        result[i]=str_temp.substr(0,position);//substr:第0位开始，长度
        str_temp=str_temp.substr(position+1,str_temp.length()-position);//更新str_temp的内容
    }
//Length()类似于size()计算的是元素的个数（只用于string）,比如abcabc，就输出6
//Strlen():用于字符数组或者字符指针（char,char*）
//如果指定大小但没有初始化/初始化了没指定大小，会给一个比设定大的初始大小。
//指定大小&初始化之后，会得出length一样，算元素个数。

    result[3]=str_temp;//好好体会下这个骚操作啦！！！

    cout<<"姓名"<<setw(8)<<result[0]<<endl;
    cout<<"国籍"<<setw(6)<<result[1]<<endl;
    cout<<"职业"<<setw(14)<<result[2]<<endl;
    cout<<"代表作"<<setw(18)<<result[3]<<endl;

//至此分割完毕，下面是拼合字符串，验证它们和原字符串是否匹配的操作

    //========================知识点：swap()
    str_temp.swap(result[0]);//swap:可以保留精度，还能交换结构体
//这里是str_temp & result[0]交换的意思！
//就把第一个字符串又撵回去了。。。
    for(int j=1;j<4;j++){//然后继续撵字符串
        str_temp+=" ";//焦点这个操作！！！死在这里过一回
        str_temp.append(result[j]);
    }

    //========================知识点：compare()
    // if(str1.compare(6, 5, str2, 4, 5) == 0){xxx}
    // 这里，那些数字都是表示-从第几位开始，长度。
    //若匹配，就返回0，否则返回1
    int equal=str.compare(str_temp);

    if(equal==0) cout<<"Successful matching!"<<endl;
    else cout<<"UNsuccessful matching!!"<<endl;

    return 0;


///【2.字符串·抽象数据类型的类定义】===============================================================================
//======================知识点：const
//表示在以后，这个值都是固定不变的值
const int maxLen=128;
class String{
    int curLen;     //字符串的长度
    char *c;        //字符串的存储数组

public:
    //构造函数
    String(const String& ob);
    String(const char *init);
    String();
    //析构函数
    ~String[] {delete[] c;}

    int Length() const {return curLen;}
    int Find(String& pat) const;

    //=========================知识点2：函数const
//    class Point{
//      public :
//         int x;

//          void modify_x(int _x){
//              x=_x;
//          }

//      Point(int _x):x(_x){}

//      void testConstFunction(int _x) const{
//
//          //错误，在const成员函数中，不能修改任何类成员变量
//         x=_x;
//
//         //错误，const成员函数不能调用非onst成员函数，因为非const成员函数可以会修改成员变量
//         modify_x(_x);
//     }
// };

    //取当前字符串中从pos开始的len个字符组成的子字符串
    String &operator() (int pos,int len);

    //判断当前字符串与对象串ob是否相等
    int operator==(const String &ob)const{
        return strcmp(ch,ob.ch)==0;
    }

    //判断当前字符串与对象串ob是否不等
    //可以不写函数名，只写函数变量
    int operator!=(const String &ob)const{
        return strcmp(ch,ob.ch)!=0;
    }

    //判断当前字符是否为空
    int operator!() const{return curLen==0;}

    //字符串ob赋给当前字符串
    String &operator=(String &ob);
    //将字符串ob连接到当前字符串之后
    String &operator+=(String &ob);
    //取当前字符串的第i个字符
    char &operator[] (int i);
}
