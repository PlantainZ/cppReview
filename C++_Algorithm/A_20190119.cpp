///【1.转置矩阵】
///【2.Z字形实现】

#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;

///【1.转置矩阵】
int main(){
    int i,j=0,tmp;
    int a[4][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};

    for(i=0;i<4;i++){
        for(;j<4;j++){
            tmp=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=tmp;
        }
        j=i+1;      //死在这里啦！！woc真是好心机啊我的天
    }

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            cout<<a[i][j]<<"-"<<endl;
        }
    }
}



///【2.Z字形实现】
#define SIZE 8
int main(int argc,char** argv){
    int matrix[SIZE][SIZE]={0};
    int a[SIZE][SIZE]={0};

    int i,j,x,y,value=0;
    int *p;
    p=matrix[0];      //来个指针，然后一个一个指过去

    //初始化矩阵
    for(i=0;i<SIZE * SIZE;i++){
        *p++=i;       //体会一下这个妙处了,知识点1
    }

    //打印原始矩阵
    cout<<"原始矩阵如下："<<endl;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            //C++中，setw(int n)用来控制输出间隔。
            //另外这里的*(*(matrix+i)+j),知识点二
            cout<<setw(4)<<*((matrix+i)+j);
            cout<<endl;
        }
    }

    i=0;j=0;
    //开始进行Z字编排
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            *(*(a+i)+j)=*(*(matrix+x)+y);

            //这里是第一行和最后一行的处理
            if((i==SIZE-1||i==0)&&j%2==0){
                j++;
                continue;
            }

            //第一列和最后一列的处理
            if((j==0 ||j==SIZE-1)&&i%2==1){
                i++;
                continue;
            }

            //一个斜行斜向上，行列相加一直相等
            if((i+j)%2==0){
                i--;
                j++;
            }
            //同理，斜向下的行，行列相加也一直相等
            else if((i+j)%2==1){
                i++;
                j--;
            }
        }
    }

    cout<<"经过Z字形编排后的矩阵如下："<<endl;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++)
            cout<<setw(4)<<*(*(a+i)+j);
            cout<<endl;
    }

}
