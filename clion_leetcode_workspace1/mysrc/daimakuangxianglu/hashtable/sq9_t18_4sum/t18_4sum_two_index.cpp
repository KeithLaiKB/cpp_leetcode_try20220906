#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
 * 0 <= a, b, c, d < n
 * a, b, c, and d are distinct.
 * nums[a] + nums[b] + nums[c] + nums[d] == target
 *
 * You may return the answer in any order.

 * Example1:
 * Input: nums = [1,0,-1,0,-2,2], target = 0
 * Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 *
 * Example2:
 * Input: nums = [2,2,2,2,2], target = 8
 * Output: [[2,2,2,2]]
 *
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

    void myOutput_VectorBVectorBintBB(vector<vector<int>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            for(int j=0;j<=nums[i].size()-1;j++){

                cout<<nums[i][j]<<"\t";
                if(j==nums[i].size()-1){
                    cout<<endl;
                }

            }
        }
    }

    // 时间复杂度：O(n^3)
    // 空间复杂度：O(1)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0

        for(int i=0;i<=nums.size()-1;i++){
            //因为这次不是 总和等于0, 而是一个target, 负数相加还是有机会 = target
            // 例如 -1>-15
            // -1,-2,-3,-9 总和== -15
            // 但如果是正数 因为排序过了, 你还第一个>target 那就不用玩了, 因为他是怎么也不可能 a+b+c+d=target的了
            if (nums[i]>target && nums[i]>=0){
                break;
            }

            // a 去重
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }

            // 做到顺序为 i, k, left, right
            for(int k = i+1;k<=nums.size()-1;k++){
                // -1,-2,-3,-9 总和== -15
                //这种是有机会的
                // 但是 8>-15 这种是没机会的, 因为已经排序好了的, 后面不会比前面还小
                if(nums[i]+nums[k]>target && nums[i]+nums[k]>=0){
                    break;
                }

                //b去重
                if(k>i+1 && nums[k]==nums[k-1]){
                    continue;
                }


                // 相当于锁住 i,k 然后 让left 和 right 在剩余的array中 双指针 向中间移动
                int left = k +1;
                int right = nums.size()-1;
                for(;left<right;){
                    if(nums[i]+nums[k]+nums[left]+nums[right]>target){
                        --right;
                    }
                    else if(nums[i]+nums[k]+nums[left]+nums[right]<target){
                        ++left;
                    }
                    else if(nums[i]+nums[k]+nums[left]+nums[right]==target){
                        //匹配成功, 放入结果中
                        result.push_back(vector<int>{nums[i],nums[k],nums[left],nums[right]});
                        //对后面将和现在一样的组合 先跳跃一次, 结合最后的++left 和 ++right 达到跳过考虑的效果，从而达到去重的效果,
                        // left<right 防止 left+1 或 right-1 越界
                        while(left<right && nums[left]==nums[left+1]){
                            ++left;
                        }
                        while(left<right && nums[right]==nums[right-1]){
                            --right;
                        }
                        ++left;
                        --right;
                    }
                }

            }

        }


        return result;
    }


};

/**
 * feature:
 *
 *
 * 思路():
 *
 *
 *
 * */
int main() {
    Solution* solut1 = new Solution();

    //vector<int> intvec1={-1,0,1,2,-1,-4};
    vector<int> intvec1={1,0,-1,0,-2,2};
    int target = 0;

    vector<vector<int>> rs_intvect =solut1->fourSum(intvec1,target);

    cout<<"result"<<endl;
    solut1->myOutput_VectorBVectorBintBB(rs_intvect,0,rs_intvect.size()-1);





    return 0;
}


