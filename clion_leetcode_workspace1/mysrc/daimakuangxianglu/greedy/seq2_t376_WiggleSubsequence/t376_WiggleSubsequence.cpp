#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

/**
 *
 * A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative.
 * The first difference (if one exists) may be either positive or negative.
 * A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.
 *
 * For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence
 * because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
 *
 * In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences.
 * The first is not because its first two differences are positive, and the second is not because its last difference is zero.
 *
 * A subsequence is obtained by deleting some elements (possibly zero) from the original sequence,
 * leaving the remaining elements in their original order.

 *
 *
 * Example1:
 * Input: nums = [1,7,4,9,2,5]
 * Output: 6
 * Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).
 *
 * Example2:
 * Input: nums = [1,17,5,10,13,15,10,5,16,8]
 * Output: 7
 * Explanation: There are several subsequences that achieve this length.
 * One is [1, 17, 10, 13, 10, 16, 8] with differences (16, -7, 3, -3, 6, -8).
 *
 * Example3:
 * Input: nums = [1,2,3,4,5,6,7,8,9]
 * Output: 2
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

    // 时间复杂度：O(log n)
    // 空间复杂度：O(1)
    // 首先这种就是分钟类
    // 1. 点位1 - 递增 或 平等 - 上升到 点位2
    // 2. 点位1 - 递减 或 平等 - 下降到 点位2
    // 3. 点位1 - 递增 或 平等 - 下降到 点位2, 记录两个点(点位2前面的点, 点位2)
    // 4. 点位1 - 递减 或 平等 - 上升到 点位2, 记录两个点(点位2前面的点, 点位2)
    //
    // 例如 2.
    // 2--------------------3--------------------5--------------------5--------------------4
    //  -------diff=1------- -------diff=2------- -------diff=0------- -------diff=-1-------
    //            prediff=1  然后prediff一直不变(即使这里的diff=0!!!)   直到 prediff=-1 也就是说此时 i=3 (5) 你的result一共有2+1=3个点 (因为这默认右边有一个数字了 不然 你这个位置怎么可能有diff)
    int wiggleMaxLength(vector<int>& nums) {
        //
        int pre_diff =0;
        int cur_diff =0;

        // 我们数的是diff, 但是最终的rs是点数, 点数=diff数+1
        int count_num_rs=1;

        cout<<"test nums.size()-2 = "<<nums.size()-2<<endl;
        for(int i=0;i<nums.size()-1;i++){
            cur_diff = nums[i+1]-nums[i];

            // 情况4                                情况3
            if((pre_diff<=0 && cur_diff >0) || (pre_diff>=0 && cur_diff <0)) {
                ++count_num_rs;
                pre_diff = cur_diff;
            }
        }
        return count_num_rs;

    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={1};
    //int mytarget = 5;

    int rs1 = -1;
    rs1 = solut1->wiggleMaxLength(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


