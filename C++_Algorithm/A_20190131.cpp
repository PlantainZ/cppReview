
#include<stdio.h>
#include<iostream>
#include <vector>
#include <string>
#include <cmath>

#define  min(a,b) ((a<b)?a:b)//真是太帅气了噢这种方式
using namespace std;

///【1.模糊匹配:编辑距离算法-Levenshtein Distance】
//1.编辑距离：两个字符串之间，由一个转换成另一个所需的最少编辑的次数。
//            可以替换插入删除。
int ldistance(const string target,const string sourcee)
{
    int i,j,cost;
    int tarlen=target.length();//这是目的串长
    int soulen=sourcee.length();//这是源串长
    if(tarlen==0||soulen==0) return -1;

    vector<vector<int> > distMatrix(soulen+1);
    //恩 二维矩阵出来啦
    for(i=0;i<soulen+1;i++) distMatrix[i].resize(tarlen+1);
    //调整每行的长度为m+1，填充值默认为0
	//要记得用的是resize,不能=New vector<int>(m+1)！！

    for(i=0;i<tarlen+1;i++) distMatrix[0][i]=i;
    for(i=0;i<soulen+1;i++) distMatrix[i][0]=i;
    //填充第一行&第一列 为下标数值

    for(i=1;i<=soulen;i++)
    {
        const int so=sourcee[i-1];
        //源串的第i-1个，竖着的，为了[i][j]
        for(j=1;j<=tarlen;j++)
        {
            const int ta=target[j-1];

            if(so==ta) cost=0;
            else cost=1;
            //设定匹配就+0，不匹配+1

            const int upleft=distMatrix[i-1][j-1]+cost;
            //从左上角推出的，该格的值
            //+的1是删除操作
			//就是 上边的值+1.source加长，target不变
			//比如 j->ja : j
			//source->target 必须要把加长的一个删除。
            const int left=distMatrix[i][j-1]+1;
            //从左边格子推出的，该格子的值
            //+的1是插入操作
			//就是 左边的值+1,source不变，target加长
			//比如 j : j->ja
			//source->target 必须要插入一个才能等于target
            const int up=distMatrix[i-1][j]+1;
            //就是 左上角的值+1
            distMatrix[i][j]=min(upleft,min(left,up));
        }
    }
    for(i=0;i<soulen+1;i++){
        for(j=0;j<tarlen+1;j++){cout<<setw(6)<<distMatrix[i][j];}
        cout<<endl;
    }
    return distMatrix[soulen][tarlen];

}

int main(int argc,char** argv){
    int dist;
    string sourcee="abc";
    string target="abcd";
    dist=ldistance(target,sourcee);
    cout<<"The dist is:"<<dist<<endl;
}
