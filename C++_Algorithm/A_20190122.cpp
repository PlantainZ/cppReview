
#include<stdio.h>
#include<memory.h>
#include<iostream>
#include<iomanip>

using namespace std;

//【1.幻方问题：矩阵横纵斜之和皆相等】
//  N 为奇数时，最简单：
//⑴ 将1放在第一行中间一列；
//⑵ 从2开始直到n×n止各数依次按下列规则存放：
//  按 45°方向行走，如向右上
//  每一个数存放的行比前一个数的行数减1，列数加1
//⑶ 如果行列范围超出矩阵范围，则回绕。
//  例如1在第1行，则2应放在最下一行，列数同样加1;
//⑷ 如果按上面规则确定的位置上已有数，或上一个数是第1行第n列时，
//  则把下一个数放在上一个数的下面。

int main(int argc,char** argv){
    cout<<"(n is odd and bigger than 1):";
    int n=1;
    cin>>n;
    cout<<endl;
    int **a=new int*[n];//注意后边*的位置，在这里摔了
    //a的空间里边放着一个指针，指向一个指着int的指针
    //然后右边是n个指针！

    for(int i=0;i<n;i++){
        a[i]=new int[n];
        //卧槽真是高级套路了，每个指针都指一个数组
        memset(a[i],0,n*sizeof(int));
    }

    int row=0;
    int col=n/2;

    for(int i=1;i<=n*n;i++){
        a[row][col]=i;
        row--;
        col++;

        //处理综述：只需特殊处理右上角
        //以及最上一行、最右列的溢出
        //最后是碰撞问题

        //处理右上角溢出
        if(row<0&&col>=n){
            col--;
            row+=2;
        }

        //处理非角的行上溢
        else if(row<0){
            row=n-1;
        }

        //处理非角的列右溢
        else if(col>=n){
            col=0;
        }

        //解决撞数问题，放在下方。
        else if(a[row][col]!=0){
            col--;
            row+=2;
        }//特别注意：这个一定要放在最后边！否则就会出错
    }

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)    cout<<setw(6)<<a[i][j];
            cout<<endl;
        }

        for(int i=n;i>0;)   delete[] a[--i];
        //是删除指针数组里边，每个指针指向的数组
        delete[] a;
        //删除指针数组

        return 0;
}



















