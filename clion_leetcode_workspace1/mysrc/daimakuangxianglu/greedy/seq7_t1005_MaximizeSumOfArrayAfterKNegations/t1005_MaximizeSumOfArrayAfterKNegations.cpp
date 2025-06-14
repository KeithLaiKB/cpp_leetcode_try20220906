#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

/**
 *
 * Given an integer array nums and an integer k, modify the array in the following way:
 * choose an index i and replace nums[i] with -nums[i].
 *
 * You should apply this process exactly k times. You may choose the same index i multiple times.
 * Return the largest possible sum of the array after modifying it in this way.
 *
 * Example1:
 * Input: nums = [4,2,3], k = 1
 * Output: 5
 * Explanation: Choose index 1 and nums becomes [4,-2,3].
 *
 * Example2:
 * Input: nums = [3,-1,0,2], k = 3
 * Output: 6
 * Explanation: Choose indices (1, 2, 2) and nums becomes [3,1,0,2].
 *
 *
 * Example2:
 * Input: nums = [2,-3,-1,5,-4], k = 2
 * Output: 13
 * Explanation: Choose indices (1, 4) and nums becomes [2,3,-1,5,4].
 *
 *
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    //绝对值 从大到小 排列
    bool static mycomp(const int &a, const int& b){
        return abs(a)> abs(b);
    }

    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    //
    // -4 -2 5 0 2 1
    //-> 依据绝对值从大到小排列
    // 5  -4 -2 2 1 0
    // 优先把 最大的负数进行 改成正,
    // 如果 全都已经变成 非负数 的情况下 还有k没用完
    //      则 直接 把队尾 的那个最小值 反复改, 因为改它的影响是最小的
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int rs=0;

        sort(nums.begin(),nums.end(), mycomp);
        for(int i=0;i<=nums.size()-1;i++){
            if(nums[i]<0){
                nums[i] = -nums[i];
                --k;
                if(k==0){
                    break;
                }
            }
        }

        //如果k 还没被用完
        //则反复修改 队尾 那个最小的元素, 因为它对总和的影响最小
        if(k>0){
            if(k%2!=0){
                nums[nums.size()-1] = -nums[nums.size()-1];
            }
        }

        for(int ele: nums){
            rs +=ele;
        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={2,-3,-1,5,-4};
    int mytarget = 5;

    int rs1 = 0;
    rs1 = solut1->largestSumAfterKNegations(vec_int1, mytarget);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


