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
