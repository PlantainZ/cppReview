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
