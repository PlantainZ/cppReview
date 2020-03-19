
///【1.unordered_maps 如何使用================================================================================】
#include <iostream>
#include <string>
#include<algorithm>
#include <unordered_map>
using namespace std;

typedef unordered_map<string,string> stringmap;

stringmap merge (stringmap a,stringmap b) {
  stringmap temp(a); temp.insert(b.begin(),b.end()); return temp;
}


int main ()
{
  stringmap first;                              // 空
  stringmap second ( {{"apple","red"},{"lemon","yellow"}} );       // 用数组初始
  stringmap third ( {{"orange","orange"},{"strawberry","red"}} );  // 用数组初始
  stringmap fourth (second);                    // 复制初始化
  stringmap fifth (merge(third,fourth));        // 移动初始化
  stringmap sixth (fifth.begin(),fifth.end());  // 范围初始化

  cout << "sixth contains:";
  for (auto& x: sixth) cout << " " << x.first << ":" << x.second;
  cout << endl;

  return 0;
}//输出结果：sixth contains: apple:red lemon:yellow orange:orange strawberry:red


// unordered_map::insert
void display(unordered_map<string,double> myrecipe,string str)
{
    cout << str << endl;
    for (auto& x: myrecipe)
        cout << x.first << ": " << x.second << endl;
    cout << endl;
}





///【2.unordered_map操作 =========================================================================================】
int main ()
{
    unordered_map<string,double>
    myrecipe,
    mypantry = {{"milk",2.0},{"flour",1.5}};
    /****************插入*****************/
    pair<string,double> myshopping ("baking powder",0.3);
    myrecipe.insert (myshopping);                        // 复制插入
    myrecipe.insert (make_pair<string,double>("eggs",6.0)); // 移动插入
    myrecipe.insert (mypantry.begin(), mypantry.end());  // 范围插入
    myrecipe.insert ({{"sugar",0.8},{"salt",0.1}});    // 初始化数组插入(可以用二维一次插入多个元素，也可以用一维插入一个元素)
    myrecipe["coffee"] = 10.0;  //数组形式插入

    display(myrecipe,"myrecipe contains:");
/*
插入有几种方式：
- 复制插入(复制一个已有的pair的内容)
- 数组插入（直接插入一个二维数组）
- 范围插入（复制一个起始迭代器和终止迭代器中间的内容）↑
- 数组访问模式插入(和数组的[]操作很相似)

输出结果
myrecipe contains:
salt: 0.1
milk: 2
flour: 1.5
coffee: 10
eggs: 6
sugar: 0.8
baking powder: 0.3
*/

    /****************查找*****************/
    unordered_map<string,double>::const_iterator got = myrecipe.find ("coffee");

    if ( got == myrecipe.end() )
        cout << "not found";
    else
        cout << "found "<<got->first << " is " << got->second<<"\n\n";
    /*
found coffee is 10
    */

    /****************修改*****************/
    myrecipe.at("coffee") = 9.0;
    myrecipe["milk"] = 3.0;
    display(myrecipe,"After modify myrecipe contains:");
    /*
After modify myrecipe contains:
salt: 0.1
milk: 3
flour: 1.5
coffee: 9
eggs: 6
sugar: 0.8
baking powder: 0.3
    */
    /****************擦除*****************/
    myrecipe.erase(myrecipe.begin());  //通过位置
    myrecipe.erase("milk");    //通过key
    display(myrecipe,"After erase myrecipe contains:");
/*
After erase myrecipe contains:
flour: 1.5
coffee: 9
eggs: 6
sugar: 0.8
baking powder: 0.3
*/
    /****************交换*****************/
    myrecipe.swap(mypantry);
    display(myrecipe,"After swap with mypantry, myrecipe contains:");
/*
After swap with mypantry, myrecipe contains:
flour: 1.5
milk: 2
*/
    /****************清空*****************/
    myrecipe.clear();
    display(myrecipe,"After clear, myrecipe contains:");
    return 0;
    /* 输出为空 */
}


///【3.unordered_map 操作系列2=========================================================================】
// unordered_map::bucket_count
int main ()
{
    unordered_map<string,string> mymap =
    {
        {"house","maison"},
        {"apple","pomme"},
        {"tree","arbre"},
        {"book","livre"},
        {"door","porte"},
        {"grapefruit","pamplemousse"}
    };
    /************begin和end迭代器***************/
    cout << "mymap contains:";
    for ( auto it = mymap.begin(); it != mymap.end(); ++it )
        cout << " " << it->first << ":" << it->second;
    cout << endl;·
    /************bucket操作***************/
     unsigned n = mymap.bucket_count();

    cout << "mymap has " << n << " buckets.\n";

    for (unsigned i=0; i<n; ++i)
    {
        cout << "bucket #" << i << "'s size:"<<mymap.bucket_size(i)<<" contains: ";
        for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
            cout << "[" << it->first << ":" << it->second << "] ";
        cout << "\n";
    }

    cout <<"\nkey:'apple' is in bucket #" << mymap.bucket("apple") <<endl;
    cout <<"\nkey:'computer' is in bucket #" << mymap.bucket("computer") <<endl;

    return 0;
}

/*输出结果：
mymap contains: door:porte grapefruit:pamplemousse tree:arbre apple:pomme book:livre house:maison
mymap has 7 buckets.
bucket #0's size:2 contains: [book:livre] [house:maison]
bucket #1's size:0 contains:
bucket #2's size:0 contains:
bucket #3's size:2 contains: [grapefruit:pamplemousse] [tree:arbre]
bucket #4's size:0 contains:
bucket #5's size:1 contains: [apple:pomme]
bucket #6's size:1 contains: [door:porte]

key:'apple' is in bucket #5

key:'computer' is in bucket #6
*/
