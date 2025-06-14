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


