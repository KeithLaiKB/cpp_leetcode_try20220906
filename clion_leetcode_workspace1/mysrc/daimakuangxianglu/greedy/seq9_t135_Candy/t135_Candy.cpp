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
 * There are n children standing in a line.
 * Each child is assigned a rating value given in the integer array ratings.
 *
 * You are giving candies to these children subjected to the following requirements:
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 *
 *
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * Example1:
 * Input: ratings = [1,0,2]
 * Output: 5
 * Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
 *
 * Example2:
 * Input: ratings = [1,2,2]
 * Output: 4
 * Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 * The third child gets 1 candy because it satisfies the above two conditions.
 *
 *
 * 局部最优:
 * 1. 第一次遍历时，只照顾我比左边高。
 * 2. 第二次遍历时，只修复我比右边高的情况
 * 以上 所有规则都是局部的（只看相邻）
 *
 * 我们按两个方向都遍历了一次，每个相邻约束都被处理到了，
 * 并且我们只在必要的情况下+1，保证是“最少分糖”
 * 推出全局最优
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    //
    int candy(vector<int>& ratings) {
        vector<int> vec_rs(ratings.size(),1);
        int rs_total=0;

        vector<int> vec_candy_left_to_right(ratings.size(),1);
        vector<int> vec_candy_right_to_left(ratings.size(),1);
        for(int i=1 ;i<=ratings.size()-1;  i++){
            // 比之前的大 则+1
            if(ratings[i]>ratings[i-1]){
                vec_candy_left_to_right[i] = vec_candy_left_to_right[i-1]+1;
            }
            // 比之前的小 或者等于 则从1开始,
            // 因为这样 肯定比 去-1 得到的值更低, 更好
            else{
                //do nothing
            }
        }

        for(int i= static_cast<int>(ratings.size())-2 ;i>=0;  i--){
            // 比之前的大 则+1
            if(ratings[i]>ratings[i+1]){
                vec_candy_right_to_left[i] = vec_candy_right_to_left[i+1]+1;
            }
                // 比之前的小 或者等于 则从1开始,
                // 因为这样 肯定比 去-1 得到的值更低, 更好
            else{
                //do nothing
            }
        }


        //                  1, 2, 2, 5, 4, 3, 2
        //left to right     1  2  1  2  1  1  1
        //right to left     1  1  1  4  3  2  1
        // 我们可以看到, 这每一次遍历, 只和前一个位置有关
        // 例如 left to right 中 的 4, 3 他们 对应的是(1,1) 而不是 (2,1), 他是从左往右搜, 他只看 有没有比 上一个搜索的大, 大了才+1
        // 例如 right to left 中 的 1, 2 他们 对应的是(1,1) 而不是 (1,2), 他是从右往左搜, 他只看 有没有比 上一个搜索的大, 大了才+1

        // vec_rs[i] = max ( left_to_right[i], right_to_left[i] )

        for(int i=0;i<=ratings.size()-1;i++){
            vec_rs[i]= max(vec_candy_left_to_right[i], vec_candy_right_to_left[i]);
            rs_total +=vec_rs[i];
        }

        return rs_total;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={1,2,2};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    int mytarget = 5;

    int rs1 = 0;
    rs1 = solut1->candy(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


