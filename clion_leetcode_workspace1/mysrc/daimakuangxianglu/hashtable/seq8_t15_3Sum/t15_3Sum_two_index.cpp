#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given an integer array nums,
 * return all the triplets [nums[i], nums[j], nums[k]]
 * such that i != j, i != k, and j != k,
 * and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.

 * Example1:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation:
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not matter.

 *
 * Example2:
 * Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum up to 0.
 *
 * Example3:
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums up to 0.
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

    // 时间复杂度：O(n^2)
    // 空间复杂度：O(1)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0

        for(int i=0;i<=nums.size()-1;i++){
            if (nums[i]>0){
                return result;  //你排完序 你还第一个>0 那就不用玩了, 因为他是怎么也不可能 a+b+c=0的了
            }

            // a 去重
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }

            int left=i+1;
            int right=nums.size()-1;

            for(;left<right;){
                if(nums[i]+nums[left]+nums[right]>0){
                    right --;
                }
                else if(nums[i]+nums[left]+nums[right]<0){
                    left ++;
                }
                else if(nums[i]+nums[left]+nums[right]==0){
                    result.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    // 找到三元组后, 防止下一次的b重复
                    while(left<right && nums[left]==nums[left+1]){
                        ++left;
                    }
                    // 找到三元组后, 防止下一次的c重复
                    // 因为假设当前B已经确定了这个C 是配对了,
                    // 所以在当前i下, c不会再能和其他的b 能凑到a+b+c==0了
                    // 因此c如果重复 大胆的移动就行
                    while(left<right && nums[right]==nums[right-1]){
                        --right;
                    }
                    left++;
                    right--;
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
    vector<int> intvec1={-10,4,4,6,6,6};

    vector<vector<int>> rs_intvect =solut1->threeSum(intvec1);

    cout<<"result"<<endl;
    solut1->myOutput_VectorBVectorBintBB(rs_intvect,0,rs_intvect.size()-1);





    return 0;
}


