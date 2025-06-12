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
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
 *
 *
 * 同一只股票能进行多次买卖
 *
 * 感觉有点像t53, t53是   找出 获得最大值  的连续的subarray
 * 这里是               找出 获得最大值   subsequence(不连续)
 *      这是股票, 只要使得每一天都能获利就可以了
 *          也许 可能你会考虑玩波段,
 *          例如:                                                 i   i+1   i+2
 *          假设第 i 天卖出 还是赚的, 但是第 i+1 天卖出亏的:      (3,   8,   4,    5)
 *              那你就 第i天 卖出  就好了, 都不需要考虑 第 i+1 天才卖出
 *                  也就是你把你当作一个牛人
 *                  你能够准时的在每一个第 i 天都获利,
 *                  这样你在 第i+1天 手上就 没有 股票 去卖出!!!!!!
 *                  如果 第i+2天 卖出 第i+1天 能获利, 那就是相当于
 *                      你准时在第i+i天这个低点 是买入 而 不是卖出
 *                  所以就不会亏 相当于买波段了
 *
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
    int maxProfit(vector<int>& prices) {
        int rs=0;

        int i=1;
        for(;i<=prices.size()-1;i++){
            int today_sell_oneday_profit= prices[i]-prices[i-1];
            if(today_sell_oneday_profit>0){
                rs+=today_sell_oneday_profit;
            }
        }
        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={7,1,5,3,6,4};
    //int mytarget = 5;

    int rs1 = -1;
    rs1 = solut1->maxProfit(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


