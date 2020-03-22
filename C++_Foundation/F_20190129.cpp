
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>

using namespace std;




///【1.基础：vector<>】==========================================================================================
//===== [(1).关于vector<>的概念 ] =====
//vector是一个动态的序列容器，相当于一个size可变的数组。
//相比于数组，vector会消耗更多的内存以有效的动态增长。
//而相比于其他动态序列容器(deques, lists and forward_lists)，
//vector能更快的索引元素(就像数组一样)，

//而且能相对高效的在尾部插入和删除元素。
//如果不是在尾部插入和删除元素，效率就没有这些容器高!!

//当需要使用vector的时候，需要包含头文件：#include <vector>，
//一般加上using namespace std;
//如果不加，则在调用时候必须用std::vector<...>这样的形式，
//即在vector前加上std::，这表示运用的是std命名空间下的vector容器。

//===== [ 2.常见用法(以int类型为例) ] =====
//单实例
vector<int> a;    //声明一个int型向量a
vector<int> a(10);    //声明一个初始大小为10的向量
vector<int> a(10, 1);    //声明一个初始大小为10且初始值都为1的向量

//参照别的vector生成
vector<int> b(a);    //声明并用向量a初始化向量b
vector<int> b(a.begin(), a.begin()+3);    //将a向量中从第0个到第2个(共3个)作为向量b的初始值

//参照数组生成:指针&引用
int n[] = {1, 2, 3, 4, 5};
vector<int> a(n, n+5);    //将数组n的前5个元素作为向量a的初值
vector<int> a(&n[1], &n[4]);    //将n[1] - n[4]范围内的元素作为向量a的初值

//关于添加元素的操作...跟栈有点类似，都是push()\pop()
vector<int> a;
a.push_back(1);    //在尾部加入一个数据
a.push_back(2);
a.pop_back();      //删除最后一个数据
a.insert(a.begin(), 0);    //在a.begin()  之前  加入0
a.erase(a.begin());    //将a.begin()的元素删除
a.erase(a.begin() + 1, a.end());    //将第二个元素以后的元素均删除

//判断vector<>是否为空
vector<int> a;
if(a.empty()){ a.push_back(1); }

//遍历访问vector<int>
vector<int> a;
for(int i = 0; i < a.size(); i++){//像数组一样以下标访问,注意这里的size()
    cout << a[i];
}

vector<int>::iterator it;//以迭代器访问,迭代器就像一个指针呀！
for(it=a.begin(); it!=a.end(); it++){
    cout<<*it<<" " ;
}

//vector排序：必须包含algorithm头文件
vector<int> a;
sort(a.begin(), a.end());

//===== [ 另外：二维数组vector<> ] =====
//创建一个10行5列的int型二维数组 相当于a[10][5];
vector<vector<int>> A(10,vector<int>(5));//错误的定义方式
vector<vector<int> > A(10,vector<int>(5));//正确的定义方式

//插入元素
//正确的插入方式
vector<vector<int> > A;
//A.push_back里必须是vector
vector<int> B;
B.push_back(0);     //不可以直接A[0].push_back(0);！！！
B.push_back(1);
B.push_back(2);
A.push_back(B);     //B成为了A[0]
B.clear();          //卧槽B清空了,注意这个clear()
B.push_back(3);     //这是A[0][1]
B.push_back(4);
B.push_back(5);
A.push_back(B);

//长度
//vector<vector<int> >A中的vector元素的个数
len = A.size();//小心一点这个size(),求长度栽过
//vector<vector<int> >A中第i个vector元素的长度
len = A[i].size();

//访问某元素的操作和二维数组是相同的
//根据前面的插入，可知输出5。
printf("%d\n", A[1][2]);




///【2.基础:迭代器】===============================================================================================

//===== [(1).关于定义和初始化 ] =====
//检查容器内元素并遍历元素的一种数据类型
//标准库为每一种标准容器（如vector）定义了一种迭代器类型，
//而只用少数容器（如vector）支持下标操作访问容器元素
vector<int>::iterator    iter;    //定义一个名为iter的变量

//每种容器都定义了一对名为begin和end的函数，是容器自带的！不是迭代器的
//用于返回迭代器。下面对迭代器进行初始化操作：
vector<int>    ivec;//要首先定义容器
vector<int>::iterator    iter1=ivec.bengin();//再定义容器的指表~
//可以理解为它好像一个指针。
//将迭代器iter1初始化为指向ivec容器的第一个元素

vector<int>::iterator   iter2=ivec.end();
//将迭代器iter2初始化为指向ivec容器的最后一个元素的下一个位置

//注意end并不指向容器的任何元素，而是指向容器的最后元素的下一位置，
//称为 (超出末端迭代器) 。
//如果vector为空，则begin返回的迭代器和end返回的迭代器相同。
//一旦向上面这样定义和初始化，就相当于把该迭代器和容器进行了某种关联，
//就像把一个指针初始化为指向某一空间地址一样。

// =====[ (2).常用操作 ]=====
//解引用：引用就是'*'/'&'，解引用就像解题。比如*p=123;
//然后，cout<<*p<<endl;就是解引用操作。会输出*p指向的值，跟解题一样。
*iter;        //对iter进行解引用，返回迭代器iter指向的元素的引用
iter->men;    //对iter进行解引用，获取指定元素中名为men的成员。
            //等效于(*iter).men
++iter;       //给iter加1，使其指向容器的下一个元素
iter++;
--iter;       //给iter减1，使其指向容器的前一个元素
iter--;
iter1==iter2; //比较两个迭代器是否相等
//当它们指向同一个容器的同一个元素
//或者都指向同同一个容器的超出末端的下一个位置时，它们相等
iter1!=iter2;

//假设已经声明一个vector<int>的ivec容器，
//下面用迭代器来遍历ivec容器，把其每个元素重置为0：
for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter)
        *iter=0;

//在C++定义的容器类型中，只有vector和queue容器提供
//迭代器算数运算和除!=和==之外的关系运算：
iter+n;     //在迭代器上加（减）整数n
iter-n;//将产生指向容器中前面（后面）第n个元素的迭代器。
//新计算出来的迭代器 必须指向容器中的元素或超出容器末端的下一个元素
//意思就是不可以越界啦

iter1+=iter2; //将iter1加上或减去iter2的运算结果赋给iter1。
iter1-=iter2;//两个迭代器依然不能越界

iter1-iter2;//两个迭代器的减法，得出两个迭代器的距离。还是不可以越界


