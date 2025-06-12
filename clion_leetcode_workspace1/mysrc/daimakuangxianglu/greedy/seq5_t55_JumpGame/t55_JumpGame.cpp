#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

/**
 *
 * You are given an integer array nums.
 * You are initially positioned at the array's first index,
 * and each element in the array represents your maximum jump length at that position.
 *
 * Return true if you can reach the last index, or false otherwise.
 *
 *
 *
 * Example1:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Example2:
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 *
 *
 * 数组里面是你在每个台阶的时候 当前下一步 最多可以 跳的阶数
 *
 * 例如 2,2,3,0,4,5
 * 如果说
 * i=0
 * dest_range_from_start = 0 + 2
 *
 * i=1
 * max_dest_idx_from_start = max(2, 1+2)= 3
 *      因为如果我跳到 idx=1的位置 的情况下,
 *          再采取行动 还能 跳2个step
 *              这意味着我从idx=0 能跳到 idx = 1+2=3,
 *              因为 max_dest_idx_from_start 不能到达 idx=5  而且 小于 当前方案 可以跳到 idx=3
 *              所以选择当前方案 并且 max_dest_idx_from_start 更改为3
 *
 * i=2
 * max_dest_idx_from_start = max(3, 1+1+3)= 5
 *      因为如果我能够跳到 idx=2的位置 的情况下,
 *          再采取行动 还能 跳3个step
 *              这意味着我从idx=0 能跳到 idx = 1+1+3=5,
 *              因为 max_dest_idx_from_start 不能到达 idx=5
 *              所以选择当前方案 并且 max_dest_idx_from_start 更改为5
 *              返回true
 *
 * 想不明白 看网上 会有说的, 非常好理解
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    // 首先这种就是分钟类
    //
    bool canJump(vector<int>& nums) {

        int max_dest_idx_from_start=0;
        bool rs=false;


        for(int i=0;i<=nums.size()-1;i++){

            //如果之前 最远能到达的下标位置 都不能到达 当前这个 idx=i 的位置,
            //证明是不可能到达当前位置, 那么 也无法继续进行下去了
            if(max_dest_idx_from_start < i){
                return false;
            }
            else{
                max_dest_idx_from_start = max(max_dest_idx_from_start, i+nums[i]);

                // 如果最远能够到达的idx 大于 最后一位的位置
                if (max_dest_idx_from_start >= nums.size()-1){
                    return true;
                }
            }
        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={2,3,1,1,4};
    //int mytarget = 5;

    int rs1 = -1;
    rs1 = solut1->canJump(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


