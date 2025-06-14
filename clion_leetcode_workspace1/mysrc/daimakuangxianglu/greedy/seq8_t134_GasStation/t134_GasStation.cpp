#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
//#include <cstdint>
#include <climits>


using namespace std;

/**
 *
 * There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].
 * You have a car with an unlimited gas tank
 * and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station.
 * You begin the journey with an empty tank at one of the gas stations.
 *
 * Given two integer arrays gas and cost,
 * return the starting gas station's index if you can travel around the circuit once in the clockwise direction,
 * otherwise return -1.
 *
 * If there exists a solution, it is guaranteed to be unique.
 *
 * Example1:
 * Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
 * Output: 3
 * Explanation:
 * Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
 * Travel to station 4. Your tank = 4 - 1 + 5 = 8
 * Travel to station 0. Your tank = 8 - 2 + 1 = 7
 * Travel to station 1. Your tank = 7 - 3 + 2 = 6
 * Travel to station 2. Your tank = 6 - 4 + 3 = 5
 * Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
 * Therefore, return 3 as the starting index.
 *
 * Example2:
 * Input: gas = [2,3,4], cost = [3,4,3]
 * Output: -1
 * Explanation:
 * You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
 * Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
 * Travel to station 0. Your tank = 4 - 3 + 2 = 3
 * Travel to station 1. Your tank = 3 - 3 + 3 = 3
 * You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
 * Therefore, you can't travel around the circuit once no matter where you start.
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


    // 1. 先查看 是否有可能完成 一圈
    //      所以 先不管中途是否 出现负数, 只有总体 total_gas > total_cost
    //      就能跑完整一圈, 只是需要看 从哪开始而已
    // 2. 看从哪开始最好
    //      假设 如果一定实在数组中间 开始start, 那么 我们可以分为两个区间
    //      (0,..................,st_idx,..................len-1)
    //
    //      假设
    //      一定会从 st_idx开始 那么
    //      (0,.........st_idx-1)
    //          这个区间的 累加rest 一定是负数的,
    //          所以 从 st_idx 开始 起步这样, 绕完一圈, 回到i的时候 能够拥有最大的储备油量!!!!
    //          因此有
    //          (0 ~ st_idx-1)<0
    //
    //      如果 需要 完整跑一圈 那么绝对有
    //          rest(0 ~ st_idx-1) + rest(st_idx, len-1) >=0
    //      则当 (0 ~ st_idx-1)<0 时 肯定有
    //          rest(st_idx, len-1) >0
    //
    //      由于这条公式的成立
    //      其实就是 st_idx =0 开始也是可以的,
    //          只是我们刚才那样解释 可以方便的 分开成两个区间
    //
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost){
        int rs=0;

        int total_gas=0;
        int total_cost =0;

        int accu_rest = 0;
        int st_idx = 0;

        for(int i=0;i<=gas.size()-1;i++){
            total_gas += gas[i];
            total_cost += cost[i];
        }
        if(total_gas-total_cost<0){
            cout<<"not enough gas to the trip"<<endl;
            return -1;
        }

        for(int i=0;i<=gas.size()-1;i++){

            accu_rest += gas[i]-cost[i];

            if(accu_rest<0){
                accu_rest=0;
                st_idx = (i +1) % gas.size();
            }

        }

        return st_idx;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={2,-3,-1,5,-4};
    vector<int> vec_int2={2,-3,-1,5,-4};
    int mytarget = 5;

    int rs1 = 0;
    rs1 = solut1->canCompleteCircuit(vec_int1, vec_int2);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


