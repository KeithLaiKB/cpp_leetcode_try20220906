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
 * An integer has monotone increasing digits if
 * and only if each pair of adjacent digits x and y satisfy x <= y.
 * Given an integer n, return the largest number that is less than or equal to n with monotone increasing digits.
 *
 *
 * Example1:
 * Input: n = 10
 * Output: 9
 * 因为本身 1 和 0 是单调递减
 * 所以 1~10中 单调递增最大的是9
 *
 *
 * Example2:
 * Input: n = 1234
 * Output: 1234
 *
 * Example2:
 * Input: n = 332
 * Output: 299
 * 因为本身 3 和 3 和 2 是不是单调递增
 * 于是我们退一步看 331
 * 因为本身 3 和 3 和 1 是不是单调递增
 * 于是我们退一步看 330
 * 因为本身 3 和 3 和 0 是不是单调递增
 * 于是我们退一步看 329.....
 *
 *
 * 因为本身 3 和 0 和 0 是不是单调递增
 * 于是我们退一步看 229.....
 * 满足 x<=y
 * 所以最大的数字是229
 *
 *
 * 其实就是 找出高位需要改变成9的位置, 然后把后面的都变成9
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }





    // 时间复杂度：O(n)
    //
    //
    // 空间复杂度：O(n)
    //
    int monotoneIncreasingDigits(int n) {
        string str_num1=to_string(n);

        // 我们一共会有两段处理
        // 先找出 需要改成改成9 的那个最高位的idx
        // 然后把 从这个idx 往后都改成9
        int nine_flag_start_idx=-1;

        for(int i=(str_num1.size()-1);i>0;i--){
            // 9 7 3
            // 9 6 9
            // 8 9 9
            // 如果不递增
            if(str_num1[i-1]<=str_num1[i]){
                continue;
            }

            else if(str_num1[i-1]>str_num1[i]){
                str_num1[i]='9';
                str_num1[i-1]--;
                nine_flag_start_idx = i;
            }
        }
        //第二段就是为了解决这个例子
        // 1 0 1
        // 1 9 9
        // 0 9 9
        for(int i=nine_flag_start_idx; i<=str_num1.size()-1;i++){
            str_num1[i]='9';
        }

        return stoi(str_num1);
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    //vector<vector<int>> vec_vec_int1={{1,3},{2,6},{8,10},{15,18}};

    //string str1 = "babacacbdfgdhshf";
    //string str1 = "ababcbacadefegdehijhklij";

    //int num=973;
    //int num=100;
    int num=120;

    int rs1 = solut1->monotoneIncreasingDigits(num);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1,0,rs1.size()-1);
    return 0;
}


