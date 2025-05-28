#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

/**
 *
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
 * On each day, you may decide to buy and/or sell the stock.
 * You can only hold at most one share of the stock at any time.
 * However, you can buy it then immediately sell it on the same day.
 * Find and return the maximum profit you can achieve.
 *
 *
 *
 * Example1:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
 * Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
 * Total profit is 4 + 3 = 7.
 *
 * Example2:
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 * Total profit is 4.
 *
 * Example3:
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 * Total profit is 4.
 *
 *
 * 同一只股票能进行多次买卖
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


