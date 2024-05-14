#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given an array of integers nums and an integer target,
 * return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

 *
 * Example2:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_VectorBintB(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> map_tmp1;
        for(int i=0;i<=nums.size()-1;i++){
            unordered_map<int, int>::iterator iter1_tmp = map_tmp1.find(target-nums[i]);

            if(iter1_tmp!=map_tmp1.end()){
                return {iter1_tmp->second, i};
            }
            else{
                map_tmp1.insert(pair<int, int>(nums[i], i));
            }
        }

        return {};
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
    Solution* solut1 = new Solution();

    vector<int> intvec1={2,7,11,15};
    //vector<int>* intvec1P=&intvec1;
    int target = 9;

    vector<int> rs_intvect=solut1->twoSum(intvec1,target);


    cout<<"result"<<endl;
    solut1->myOutput_VectorBintB(rs_intvect,0,rs_intvect.size()-1);





    return 0;
}


