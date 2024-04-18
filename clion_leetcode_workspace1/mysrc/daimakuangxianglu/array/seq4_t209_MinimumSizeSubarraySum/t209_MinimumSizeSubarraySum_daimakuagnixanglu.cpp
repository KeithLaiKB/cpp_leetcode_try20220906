#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given an array of positive integers nums and a positive integer target,
 * return the minimal length of a subarray whose sum is greater than or equal to target.
 * If there is no such subarray, return 0 instead.
 *
 * Example:
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem constraint.
 * 7=4+3
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = INT32_MAX;
        int sum = 0; // 滑动窗口数值之和
        int i = 0; // 滑动窗口起始位置
        int subLength = 0; // 滑动窗口的长度
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            // 注意这里使用while，每次更新 i（起始位置），并不断比较子序列是否符合条件
            for(int myloadi=i;myloadi<=j;myloadi++){
                cout<<nums[myloadi]<<"\t";
                if(myloadi==j){
                    cout<<endl;
                }
            }
            while (sum >= target) {
                subLength = (j - i + 1); // 取子序列的长度
                result = result < subLength ? result : subLength;
                sum -= nums[i++]; // 这里体现出滑动窗口的精髓之处，不断变更i（子序列的起始位置）

                for(int myloadi=i;myloadi<=j;myloadi++){
                    cout<<nums[myloadi]<<"\t";
                    if(myloadi==j){
                        cout<<endl;
                    }
                }
            }
        }
        // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
        return result == INT32_MAX ? 0 : result;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();
    vector<int> intvec={3,3,2,1,4,3};
    //vector<int> intvec={-2,3,1,2,4,3};
    intvec.reserve(100000);  //这是题目要求里length说的. 虽然暂时没有100000个
    //vector<int> intvec={3,2,2,3};

    int mytarget = 7;
    //int mytarget = 3;


    int result= solut1->minSubArrayLen(mytarget,intvec);
    cout<<"result"<<result<<endl;

    /*for(int i=0;i<=intvec_result.size()-1;i++){
        cout<<intvec_result[i]<<"\t";
        if(i==intvec_result.size()-1){
            cout<<endl;
        }
    }*/



    return 0;
}


