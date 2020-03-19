
///1.最短路径：Floyd，时间复杂度为O(n3)
// Floyd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#define MAX_VALUE 1000
#define MAX_VERTEX_COUNT 20
using namespace std;
struct MGraph
{
	int *edges[MAX_VALUE];
	int iVertexCount, iEdgeCount;
};
void ReadData(MGraph *mGraph);
void Floyd(MGraph *mGraph, int *iArrPath[MAX_VALUE]);
void PrintResult(MGraph *mGraph, int *iArrPath[MAX_VALUE]);

int main()
{
	int *iArrPath[MAX_VALUE];
	for (int i = 0; i < MAX_VALUE; i++){
		iArrPath[i] = new int[MAX_VALUE];
	}//给每个指针分配指向空间

	MGraph mGraph;
	for (int i = 0; i < MAX_VALUE; i++){
		mGraph.edges[i] = new int[MAX_VALUE];
	}
	ReadData(&mGraph);
	Floyd(&mGraph, iArrPath);
	PrintResult(&mGraph, iArrPath);
	system("pause");
	return 0;
}

void ReadData(MGraph *mGraph){

	//cout << "请输入顶点数量" << endl;
	//cin >> mGraph->iVertexCount;
	//cout << "请输入邻接矩阵数据：" << endl;
	//for (int iRow = 1; iRow <= mGraph->iVertexCount; iRow++){
	//	for (int iCol = 1; iCol <= mGraph->iVertexCount; iCol++){
	//		cin >> mGraph->edges[iRow][iCol];
	//	}
	//}
	cout << "请输入顶点数和边数" << endl;
	cin >> mGraph->iVertexCount >> mGraph->iEdgeCount;
	for (int iRow = 1; iRow <= mGraph->iVertexCount; iRow++){
		for (int iCol = 1; iCol <= mGraph->iVertexCount; iCol++){
			mGraph->edges[iRow][iCol] = MAX_VALUE;
		}
	}
	cout << "请输入邻接边及权重" << endl;
	int iRow, iCol, iWeight;
	for (int i = 1; i <= mGraph->iEdgeCount; i++){
		cin >> iRow >> iCol >> iWeight;
		mGraph->edges[iRow][iCol] = iWeight;
	}
}

void Floyd(MGraph *mGraph, int **iArrPath){

	for (int i = 1; i <= mGraph->iVertexCount; i++){
		for (int j = 1; j <= mGraph->iVertexCount; j++){
			iArrPath[i][j] = i;
		}
	}//初始化路径表

	for (int k = 1; k <= mGraph->iVertexCount; k++){
		for (int i = 1; i <= mGraph->iVertexCount; i++){
			for (int j = 1; j <= mGraph->iVertexCount; j++){
				if (mGraph->edges[i][k] + mGraph->edges[k][j] < mGraph->edges[i][j]){
					mGraph->edges[i][j] = mGraph->edges[i][k] + mGraph->edges[k][j];
					iArrPath[i][j] = iArrPath[k][j];
				}
			}
		}
	}

}

void PrintResult(MGraph *mGraph, int **iArrPath){

	cout << "Ori -> Des\tDistance\tPath" << endl;

	for (int i = 1; i <= mGraph->iVertexCount; i++){
		for (int j = 1; j <= mGraph->iVertexCount; j++){
			if (i != j){
				cout << i << "->" << j << "\t\t";
				if (mGraph->edges[i][j] == MAX_VALUE){
					cout << "无连通路径" << "\t\t" << endl;
				}
				else{
					cout << mGraph->edges[i][j] << "\t\t";
					std::stack<int> stackVertices;
					int k = j;
					do
					{
						k = iArrPath[i][k];
						stackVertices.push(k);
					} while (k != i);

					cout << stackVertices.top();
					stackVertices.pop();

					unsigned int nLength = stackVertices.size();
					for (unsigned int nIndex = 0; nIndex < nLength; nIndex++)
					{
						cout << " -> " << stackVertices.top();
						stackVertices.pop();
					}
					cout << " -> " << j << endl;
				}
			}
		}
	}
}


///2.指针知识点补充============================================================================================
//====================1）关于访问数组================================
int i, *pa, a[] = {3,4,5,6,7,3,7,4,4,6};
pa = a; /*请注意数组名 a 直接赋值给指针 pa*/
for (i = 0; i <= 9; i++) {
    std::cout <<  pa[i] << std::endl;
    std::cout << *(pa+i) <<std::endl;
}//两种输出方法都可以


//====================2）指针数组：本质是数组，数组中每一个成员是一个指针。=============================
char * pArray[] ={"apple","pear","banana","orange","pineApple"};
for(int i=0; i<sizeof(pArray)/sizeof(*pArray); i++)
    std::cout << pArray[i] << std::endl;

//===================3）指针数组名 赋给二级指针=======================================
char * pArray[] ={"apple","pear","banana","orange","pineApple"};
for(int i=0; i<sizeof(pArray)/ sizeof(*pArray); i++)
	std::cout << pArray[i] << std::endl;//输出的是数组的遍历结果

char **pArr = pArray;//是二级指针，然后pArray = &pArray[0] ←本身是char*型
for(int i=0; i<sizeof(pArray)/ sizeof(*pArray); i++)
	std::cout << pArr[i] << std::endl;//输出的还是数组的遍历结果

//====================4）可以不要维度==================================================
char *str = "china";
	while(*str)
	{
		std::cout << *str++ << std::endl;
	}

	char * pArray[] ={"apple","pear","banana","orange","pineApple",NULL};
	char **pa = pArray;
	while(*pa != NULL)
	{
		std::cout << *pa++ << std::endl;
	}

//===================5）分配二维空间===================================================
int (*p)[5] = alloc2dSpace(sizeof(int),3,5);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<5; j++)
		{
			p[i][j] = i+j;
		}
	}
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("%d ",*(*(p+i)+j));
		}
		putchar(10);
	}

//====================6）修改常变量===================================================
const int a = 200; //定义的时候必须初始化
printf("a = %d\n",a);// a = 200
int *p = &a; //
*p = 300;
printf("a = %d\n",a);// a = 300
return 0;

//====================7）常指针变量是不可修改它的指向的========================================
//基础知识补充：符号常量
const int ac=12;
int const bc=13; //这两个语句是等效的。
//ac=20 ←这样是不可以的，前边有const的变量在后续是拒绝修改的

int a = 2;
int * const p = &a;
int b  = 3;
//p = &b;    //指针常量无法修改，编译不过
printf("%d\n",*p);
//常用于修饰入参指针，表示其指向的内容不可以修改。这样，可以增加程序的键壮性。
//如果用户不小心发生了修改行为，则会用编译警告来提示，而不是用运行的错误来提示。
//例如：
char * strcpy ( char * destination, const char * source );
char * strcat ( char * destination, const char * source );


//注意区分：常指针
int a = 2;
const int * p = &a;
printf("p = %p\n",p);
int b ;
p = &b;  //可以指别的变量。
printf("p = %p\n",p);
//*p = 200;              //编译不过，因为它所指的变量内容不可修改。
const int *const q = &a;
//q = &b;                //编译不过
// *q = 200;              //编译不过
return 0;



//还有一种误区：先出生的const常量不能被指针指向。
const int i1 = 40;
int *pi;
//pi = &i1; /* 这样可以吗？不行，编译错误
const int i1=40;
const int * pi;
 pi=&i1;/* 两个类型相同，可以这样赋值。只是两个值都不能修改。 */

//还有这样是可以的哦！
int i = 20;
const int * const pi=&i;


//===========================================8）函数指针=====================================================
#include <stdio.h>
void print() {printf("china\n");}
void dis() {printf("china\n");}

typedef void (*PFUNC)() ;//关于函数指针类型的定义

int main()
{
    void (*pf)() = print; //void (*pf)() = &print;
    pf(); //(*pf)();
    pf = dis;
    pf();
    return 0;

    //指针类型
    PFUNC pf= print;
    pf();
    pf = dis;
    pf();
    return 0;
}





///3.指针应用：序列加密============================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
buf[] = "china is great";
//chi
//na
//is
//gre
//at

//cniga
//hasrt
//i e
#endif
char * encode(char *buf, int line)
{
    int len = strlen(buf);
    int nlen;
    if(len%line!=0)
    {
        nlen = len + (line - len%line);
    }
    else
    {
        nlen = len;
    }
    char * tmp = (char *)malloc(nlen+1);
    char * secret = (char*)malloc(nlen+1);
    char *psecret = secret;
    strcpy(tmp,buf);
    int n = strlen(tmp);
    for(; n<nlen; n++)
    {
        tmp[n] = ' ';
    }
    tmp[nlen] = '\0';
    int row = nlen/line;
    char (*ptmp)[line] =tmp;
    int i = 0;
    int j = 0;
    for(; i<line; i++)
    {
        for(; j<row; j++)
        {
            *psecret++ = ptmp[j][i];
        }
    }
    *psecret = '\0';
    free(tmp);
    return secret;
}
char * decode(char* buf, int line)
{
    int len = strlen(buf);
    int nline = len/line;
    int row = line;
    char * desecret = (char*)malloc(len+1);
    char *pd = desecret;
    char (*p)[nline] = buf;
    int i = 0;
    int j = 0;
    for(;i<nline; i++)
    {
        for(; j<row; j++)
        {
            *pd++ = p[j][i];
        }
    }
    *pd= '\0';
    while(*(--pd) == 32)
    {
        *pd= '\0';
    }

    return desecret;
}

int main(void)
{
    char buf[] = "china is great";
    printf("%s\n","*****明文*****");
    printf("%s\n",buf);

    char * secret = encode(buf,3);
    printf("%s\n","*****密文*****");
    printf("%s\n",secret);
    char * desecret = decode(secret,3);
    printf("%s\n",desecret);
    free(secret);
    free(desecret);
    return 0;
}


///5.函数指针应用：记录用户选择=================================================================================
///函数指针的一个用法出现在 菜单驱动系统中。
///例如程序可以提示用户输入一个整数值来选择菜单中的一个选项。
///用户的选择可以做函数指针数组的下标，而数组中的指针可以用来调用函数。
#include <stdio.h>
void function0(int);
void function1(int);
void function2(int);
int main()
{
    void (*f[3])(int) = {function0,function1,function2};
    //将这 3 个函数指针保存在数组 f 中
    int choice;
    printf("Enter a number between 0 and 2, 3 to end: ");
    scanf("%d",&choice);
    while ((choice >= 0) && (choice <3))
    {
        (*f[choice])(choice);
        //f[choice]选择在数组中位置为 choice 的指针。
        //指针被解除引用，以调用函数，并且 choice 作为实参传递给这个函数。
        printf("Enter a number between 0 and 2,3 to end: ");
        scanf("%d",&choice);
    }
    printf("Program execution completed.");
    return 0;
}
void function0(int a)
{
    printf("You entered %d so function0 was called\n",a);
}
void function1(int b)
{
    printf("You entered %d so function1 was called\n",b);
}
void function2(int c)
{
    printf("You entered %d so function2 was called\n",c);
}



///6.函数指针应用：回调函数============================================================================================
#include <stdio.h>
int callBackCompare(int a,int b) {return a<b?1:0;}
void selectSort(int *p, int n,int(*pf)(int,int))
{
    for(int i=0; i<n-1 ;i ++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(pf(p[i],p[j]))
            {
                p[i] = p[i]^p[j];
                p[j] = p[i]^p[j];
                p[i] = p[i]^p[j];
            }
        }
    }
}
int main(void)
{
    int arr[10] = {6,5,4,3,2,1,7,8,9,0};
    selectSort(arr,10,callBackCompare);
    for(int i=0; i<10; i++)
    {
        printf("%d\n",arr[i]);
    }
    return 0;
}






