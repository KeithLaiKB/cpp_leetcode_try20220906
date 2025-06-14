#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

/**
 *
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 *
 *
 *
 * Example1:
 * Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
 * Output: 6
 * Explanation: The subarray [4,-1,2,1] has the largest sum 6.
 *
 * Example2:
 * Input: nums = [1]
 * Output: 1
 * Explanation: The subarray [1] has the largest sum 1.
 *
 * Example3:
 * Input: nums = [5,4,-1,7,8]
 * Output: 23
 * Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
 *
 * 局部最优:
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    bool static mycomp(const int &a, const int &b){
        return a<b;
    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    // 首先这种就是分钟类
    //
    // 当前区间的总值
    // 如果当强区间的总值是负数   那么就不记录它, 因为它只会拉低下一个数 的数值,
    // 如果当前区间的总值不是负数  那么他和当前区间的下一个数字能组成一个较大的 rs
    int maxSubArray(vector<int>& nums) {
        //
        int rs=INT32_MIN;
        int range_sum =0;

        for(int i=0;i<=nums.size()-1;i++){
            range_sum +=nums[i];

            if(range_sum>rs){
                rs=range_sum;
            }

            if(range_sum<=0){
                range_sum =0;
            }




        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={1};
    //int mytarget = 5;

    int rs1 = -1;
    rs1 = solut1->maxSubArray(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


