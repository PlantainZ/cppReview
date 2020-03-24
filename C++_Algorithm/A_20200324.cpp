///【1.剑指offer-01】=============================================================================================

//在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，
//每一列都按照从上到下递增的顺序排序。
//请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。


/* 思路
* 矩阵是有序的，从左下角来看，向上数字递减，向右数字递增，
* 因此从左下角开始查找，当要查找数字比左下角数字大时。右移
* 要查找数字比左下角数字小时，上移
*/

class Solution {
public:
    bool Find(vector<vector<int> > array,int target) {
        int rowCount = array.size();
        int colCount = array[0].size();
        int i,j;
        for(i=rowCount-1,j=0;i>=0&&j<colCount;)
        {
            if(target == array[i][j])
                return true;
            if(target < array[i][j])
            {
                i--;
                continue;
            }
            if(target > array[i][j])
            {
                j++;
                continue;
            }
        }
        return false;
    }
};


///【剑指Offer-02】===========================================================================================
//请实现一个函数，将一个字符串中的每个空格替换成“%20”。
//例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;

template<class T> //如果不是模板类，就会报错！！！
int get_length(T& s){
    return sizeof(s)/sizeof(s[0]);
}

void replaceSpace(char *str,int length) {
    int spaceNum=0; //char* 数组可以这样访问到元素！！str[i] = *(str+i)
    for(int i=0;i<length;i++){
        if(str[i] == ' ') spaceNum++;
    }

    int newLength = length+2*spaceNum;
    for(int i=newLength-1;i>=0;i--){
        if(str[i]!=' '){
            str[i+2*spaceNum] =str[i];
        }
        else{
            str[i+2*spaceNum] = '0';
            str[i+2*spaceNum-1] = '2';
            str[i+2*spaceNum-2] = '%';
            spaceNum--;
        }
    }
}

int main(){
    char s[] = "abc def ghi";
    int len = get_length(s);
    replaceSpace(s,len);
    len = get_length(s);
    for(int i=0;i<len;i++){
        cout<<s[i];
    }

}


///【剑指offer-03】前/中遍历重建二叉树=========================================================================

/*
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
*/
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
      //为了让结构体响应new关键字
  };

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector pre,vector vin) {
        int vinlen=vin.size();
        if(vinlen==0) return NULL;
        vector pre_left, pre_right, vin_left, vin_right;
        //创建根节点，根节点肯定是前序遍历的第一个数
        TreeNode* head = new TreeNode(pre[0]);
        //找到中序遍历根节点所在位置,存放于变量gen中

        int gen=0;
        for(int i=0;i<vinlen;i++){
            if(vin[i]==pre[0]){
                gen=i;
                break;
            }
        }
        //对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边
        // 左子树
        for(int i = 0; i < gen; i++){
            vin_left.push_back(vin[i]);
            pre_left.push_back(pre[i+1]);//先序第一个为根节点
        }
        // 右子树
        for(int i = gen + 1; i < vinlen; i++){
            vin_right.push_back(vin[i]);
            pre_right.push_back(pre[i]);
        }
        //递归，执行上述步骤，区分子树的左、右子子树，直到叶节点
        head->left = reConstructBinaryTree(pre_left, vin_left);
        head->right = reConstructBinaryTree(pre_right, vin_right);
        return head;
    }
};

///【剑指Offer-04，自答】===============================================================================
//用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
class Solution
{
public:
    void push(int node) {
        int temp;
        if(!stack2.empty()){
            temp = stack2.top();
            stack2.pop();
            stack1.push(temp);
        }
        stack1.push(node);
    }

    int pop() {
        int result,temp;
        while(!stack1.empty()){
            temp = stack1.top();
            stack1.pop();
            stack2.push(temp);
        }

        result = stack2.top();
        stack2.pop();
        return result;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


///【剑指Offer-05】====================================================================================
/*把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.empty()) return 0;

        int low = 0;
        int high = rotateArray.size() - 1;
        int mid = 0;

        while(low < high){
            // 子数组是非递减的数组，10111
            // 否则左边数组必定大于右边
            if (rotateArray[low] < rotateArray[high])
                return rotateArray[low];
            mid = low + (high - low) / 2;
            if(rotateArray[mid] > rotateArray[low])
                low = mid + 1;
            else if(rotateArray[mid] < rotateArray[high])
                high = mid;
            else low++;
        }
        return rotateArray[low];
    }
private:
    // 顺序寻找最小值
    int MinOrder(vector<int> &num,int left,int right){
        int result = num[left];
        for(int i = left + 1;i < right;++i){
            if(num[i] < result){
                result = num[i];
            }//if
        }//for
        return result;
    }
};

int main(){
    Solution s;
    //vector<int> num = {0,1,2,3,4,5};
    //vector<int> num = {4,5,6,7,1,2,3};
    vector<int> num = {2,2,2,2,1,2};
    int result = s.minNumberInRotateArray(num);
    // 输出
    cout<<result<<endl;
    return 0;
}

