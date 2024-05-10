#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 *
 * Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * Repeat the process until the number equals 1 (where it will stay),
 * or it loops endlessly in a cycle which does not include 1.
 * Those numbers for which this process ends in 1 are happy.
 *
 * Return true if n is a happy number, and false if not.
 *
 * Example1:
 * Input: n = 19
 * Output: true
 * Explanation:
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1

 *
 * Example2:
 * Input: n = 2
 * Output: false
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    int getSum(int n){
        int rs=0;
        // 201
        // rs%10=1
        // rs%10=0
        // rs%10=2
        for(;n>0;n=n/10){
            rs= rs+ ((n%10)*(n%10)); // rs+ square
        }
        cout<<rs<<endl;
        return rs;
    }

    // 如果每次产生的数字 之前已经出现过了 就证明死循环了
    bool isHappy(int n) {
        unordered_set<int> proces_record;

        int record_tmp=n;
        for(;;){
            //
            if(record_tmp==1){
                return true;
            }
            //
            record_tmp = getSum(record_tmp);
            if(proces_record.find(record_tmp)!=proces_record.end()){
                //有重复了, 所以它不是happy number了 因为会死循环了
                return false;
            }
            else{
                proces_record.insert(record_tmp);
            }

        }
    }


};

/**
 * feature:
 * 1. 要一个set去重
 *
 * 思路():
 * 1. 把过程都记录下来, 发现过程重复 证明无法最终到头
 *
 *
 * */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    int num = 19;

    bool rs=solut1->isHappy(num);


    cout<<"result"<<endl;
    cout<<rs<<endl;





    return 0;
}


