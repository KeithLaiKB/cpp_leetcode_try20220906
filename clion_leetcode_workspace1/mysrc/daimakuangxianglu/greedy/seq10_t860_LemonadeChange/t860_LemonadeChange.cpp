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
 * At a lemonade stand, each lemonade costs $5.
 * Customers are standing in a queue to buy from you and order one at a time (in the order specified by bills).
 *
 * Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.
 * You must provide the correct change to each customer so that the net transaction is that the customer pays $5.
 * Note that you do not have any change in hand at first.
 *
 * Given an integer array bills where bills[i] is the bill the ith customer pays,
 * return true if you can provide every customer with the correct change, or false otherwise.
 *
 *
 *
 * Example1:
 * Input: bills = [5,5,5,10,20]
 * Output: true
 * Explanation:
 * From the first 3 customers, we collect three $5 bills in order.
 * From the fourth customer, we collect a $10 bill and give back a $5.
 * From the fifth customer, we give a $10 bill and a $5 bill.
 * Since all customers got correct change, we output true.
 *
 * Example2:
 * Input: bills = [5,5,10,10,20]
 * Output: false
 * Explanation:
 * From the first two customers in order, we collect two $5 bills.
 * For the next two customers in order, we collect a $10 bill and give back a $5 bill.
 * For the last customer, we can not give the change of $15 back because we only have two $10 bills.
 * Since not every customer received the correct change, the answer is false.
 *
 *
 *  从 题目中的 bills[i] is the bill the ith customer pays
 *  这 ith
 *  可以看出bills 里的 顾客是按顺序进来购买的, 所以不能排序
 *
 * Note that you do not have any change in hand at first.
 * 这道题 就是说一开始 手上只有 0张5块, 0张十块, 0张 20块
 * 顾客 回来买柠檬, 每个柠檬5块
 * 我也可以利用 收入 来去找零钱
 * 最后可以完美完整的 进行交易。
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
    //
    // 如果是大数, 就尽量找一些 大数字的change
    // 例如 遇到 对方给自己20块, 我们要找零钱 = 20-5=15
    //          自己优先    找 10 + 5
    //                  而不是 5 + 5 + 5
    //          因为这样 我们可以留 下更多的 5 进行 找零钱, 比较方便, 而且 5 块钱多了 还可以拼凑起来
    //
    // 所以局部最优：遇到账单20，优先消耗美元10，完成本次找零。全局最优：完成全部账单的找零
    bool lemonadeChange(vector<int>& bills) {
        int change_5 = 0;
        int change_10 = 0;
        int change_20 = 0;

        bool rs = false;

        int i=0;
        for(;i<=bills.size()-1;i++){
            if(bills[i]==5){
                ++change_5;
            }
            else if(bills[i]==10){
                if(change_5>0){
                    --change_5;
                    ++change_10;
                }
                else{
                    return false;
                }


            }
            else if(bills[i]==20){
                if(change_10>=1 && change_5>=1){
                    ++change_20;
                    --change_10;
                    --change_5;

                }
                else if(change_10==0 && change_5>=3){
                    ++change_20;
                    --change_5;
                    --change_5;
                    --change_5;

                }
                else{
                    return false;
                }
            }
        }

        if(i==bills.size()){
            rs = true;
        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    int mytarget = 5;

    int rs1 = 0;
    rs1 = solut1->lemonadeChange(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


