#include<memory>
#include <map>
///【1.auto_ptr类：用于管理动态内存分配】========================================================================
/*如果使用 new() 函数分配堆中的内存，而又不记得回收这部分内存，会导致内存泄漏。
因此必须使用 delete 语句释放该内存块。

auto_ptr 模板定义了类似指针的对象，将 new 获得的地址赋给该对象。
当 auto_ptr 对象过期时，析构函数将使用 delete 来释放内存。
如果将 new 返回的地址赋值给 auto_ptr 对象，无须记住还需要释放这些内存。
在 auto_ptr 对象过期时，内存将自动被释放。

在 C++ 语言中，要使用 STL 中的 auto_ptr 对象，必须包含头文件 <memory>，该文件包括 auto_ptr 模板。
使用通常的模板句法来实例化所需类型的指针。auto_ptr 构造函数是显式的，不存在从指针到 auto_ptr 对象的隐式类型转换。*/
auto_ptr <double> pd;
double *p_reg = new double;
pd = p_reg; // 不允许
pd = auto_ptr <double> (p_reg); //允许
auto_ptr <double> panto =p_reg; //不允许
auto_ptr <double> pauto (p_reg); //允许
//在使用 auto_ptr 时，只能配对使用 new 和 delete。
//提示，只能对 new 分配的内存使用 auto_ptr 对象，不要对由 new() 分配的或通过声明变量分配的内存使用它。




///【2.map类】==================================================================================================
map<int, string> mapStudent;
//map对象是模板类，需要关键字和存储对象两个模板参数

//关于三种插入的方法--------------------------------------
//1.关于insert的使用：用insert函数插入pair数据
mapStudent.insert(pair<int, string>(1, "student_one"));
mapStudent.insert(pair<int, string>(2, "student_two"));
mapStudent.insert(pair<int, string>(3, "student_three"));

//2.用insert函数插入value_type数据：
mapStudent.insert(map<int, string>::value_type (1, "student_one"));
mapStudent.insert(map<int, string>::value_type (2, "student_two"));
mapStudent.insert(map<int, string>::value_type (3, "student_three"));

//3.用数组方式插入：注意，如果有重复元素在，就会覆盖。
//上两种如果有重复元素在，不会覆盖，就是没法插入。
mapStudent[1] = "student_one";
mapStudent[2] = "student_two";
mapStudent[3] = "student_three";


//可以用pair来获得是否插入成功
pair<map<int, string>::iterator, bool> Insert_Pair;
Insert_Pair = mapStudent.insert(map<int, string>::value_type (1, "student_one"));
if(Insert_Pair.second == true)
    cout<<"Insert Successfully"<<endl;
else
    cout<<"Insert Failure"<<endl;

//得到map的大小
int nSize = mapStudent.size();


//展示map内容--------------------------------------
//1.用迭代器的方法
map<int, string>::iterator iter;
for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
    cout<<iter->first<<' '<<iter->second<<endl;

//2.用数组的办法
for(int nindex = 1; nindex <= nSize; nindex++)
  cout<<mapStudent[nindex]<<endl;


//查找并获得map中的元素（判定key是否在map中出现）--------------------
//1.用count函数：key是否出现？返回值为0/1

//2.用find函数：定位数据出现的位置，返回一个迭代器。
iter = mapStudent.find(1);
if(iter != mapStudent.end())
    cout<<"Find, the value is "<<iter->second<<endl;
else
    cout<<"Do not Find"<<endl;
//通过map对象的方法获取的iterator数据类型是一个std::pair对象，
//包括两个数据 iterator->first和 iterator->second分别代表关键字和存储的数据。

//3.高级用法：lower_bound() & upper-bound()
/* map中已经插入了1，2，3，4的话，
如果lower_bound(2)的话，返回的2，
而upper-bound（2）的话，返回的就是3 */

/* Equal_range函数返回一个pair，
pair里面第一个变量是Lower_bound返回的迭代器，
pair里面第二个迭代器是Upper_bound返回的迭代器，
如果这两个迭代器相等的话，则说明map中不出现这个关键字 */

iter = mapStudent.lower_bound(1);  //返回的是下界1的迭代器
cout<<iter->second<<endl;  //输出iter所指的值
iter = mapStudent.lower_bound(2);  //返回的是下界3的迭代器
cout<<iter->second<<endl;
iter = mapStudent.lower_bound(3);  //返回的是下界3的迭代器
cout<<iter->second<<endl;
iter = mapStudent.upper_bound(2);  //返回的是上界3的迭代器
cout<<iter->second<<endl;
iter = mapStudent.upper_bound(3);  //返回的是上界5的迭代器
cout<<iter->second<<endl;

pair<map<int, string>::iterator, map<int, string>::iterator> mappair;  //这是两个pair<it,it>
mappair = mapStudent.equal_range(2);
if(mappair.first == mappair.second)
    cout<<"Do not Find"<<endl;
else
    cout<<"Find"<<endl;

mappair = mapStudent.equal_range(3);
if(mappair.first == mappair.second)
    cout<<"Do not Find"<<endl;
else
    cout<<"Find"<<endl;


//map中删除元素--------------------------------------

//如果要删除1,用迭代器删除

map<int, string>::iterator iter;
iter = mapStudent.find(1);
mapStudent.erase(iter);

//如果要删除1，用关键字删除
int n = mapStudent.erase(1);//如果删除了会返回1，否则返回0

//用迭代器，成片的删除，一下代码把整个map清空
mapStudent.erase( mapStudent.begin(), mapStudent.end() );
//成片删除要注意的是，也是STL的特性，删除区间是一个前闭后开的集合
//自个加上遍历代码，打印输出吧


//注意map中的swap不是一个容器中的元素交换，而是两个容器所有元素的交换。


//map中sort问题--------------------------------------
/* 存在问题：map中的元素是自动按Key升序排序，所以不能对map用sort函数
STL中默认是采用小于号来排序的，以上代码在排序上是不存在任何问题的，
因为上面的关键字是int 型，它本身支持小于号运算，
在一些特殊情况，比如关键字是一个结构体，涉及到排序就会出现问题，
因为它没有小于号操作，insert等函数在编译的时候过 不去 */

//解决方法1：小于号重载，程序举例：
typedef struct tagStudentinfo{
    int      niD;
    string   strName;

    bool operator < (tagStudentinfo const& _A) const{
//这个函数指定排序策略，按niD排序，如果niD相等的话，按strName排序
        if(niD < _A.niD) return true;
        if(niD == _A.niD) return strName.compare(_A.strName) < 0;
        return false;
    }
} Studentinfo, *PStudentinfo; //学生信息

int main()
{

    int nSize;   //用学生信息映射分数
    map<Studentinfo, int>mapStudent;
    map<Studentinfo, int>::iterator iter;
    Studentinfo studentinfo;

    studentinfo.niD = 1;
    studentinfo.strName = "student_one";
    mapStudent.insert(pair<Studentinfo, int>(studentinfo, 90));

    studentinfo.niD = 2;
    studentinfo.strName = "student_two";
    mapStudent.insert(pair<Studentinfo, int>(studentinfo, 80));

    for (iter=mapStudent.begin(); iter!=mapStudent.end(); iter++)
        cout<<iter->first.niD<<' '<<iter->first.strName<<' '<<iter->second<<endl;
    return 0;
}

//解决方法2：第二种：仿函数的应用
//这个时候结构体中没有直接的小于号重载
typedef struct tagStudentinfo{
    int      niD;
    string   strName;
} Studentinfo, *PStudentinfo; //学生信息

class sort{
public:
    bool operator() (Studentinfo const &_A, Studentinfo const &_B) const{
        if(_A.niD < _B.niD) return true;
        if(_A.niD == _B.niD) return _A.strName.compare(_B.strName) < 0;
        return false;
    }
};

int main()
{
    //用学生信息映射分数
    map<Studentinfo, int, sort>mapStudent;
    map<Studentinfo, int>::iterator iter;
    Studentinfo studentinfo;

    studentinfo.niD = 1;
    studentinfo.strName = "student_one";
    mapStudent.insert(pair<Studentinfo, int>(studentinfo, 90));

    studentinfo.niD = 2;
    studentinfo.strName = "student_two";
    mapStudent.insert(pair<Studentinfo, int>(studentinfo, 80));

    for (iter=mapStudent.begin(); iter!=mapStudent.end(); iter++)
        cout<<iter->first.niD<<' '<<iter->first.strName<<' '<<iter->second<<endl;
}

















