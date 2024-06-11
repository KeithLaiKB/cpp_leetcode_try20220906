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
    // 空间复杂度：O(n) 和 额外的set的开销
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0
        // a = nums[i], b = nums[j], c = -(a + b)
        for (int i = 0; i < nums.size(); i++) {
            // 排序之后如果第一个元素已经大于零，那么不可能凑成三元组
            if (nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) { //三元组元素a去重
                continue;
            }

            unordered_set<int> set;
            for (int j = i + 1; j < nums.size(); j++) {
                if (j > i + 2
                    && nums[j] == nums[j-1]
                    && nums[j-1] == nums[j-2]) {
                    // 三元组元素b去重,因为如果 假设 a[i]==a[j-3]=-10, a[j-2]=-5, a[j-1]=-5, a[j]=-5
                    // 假设 a[i]==a[j-3]=-10, a[j-2]=-5 之后
                    // 扫描到 a[j-1]=-5
                    // 他是成立的, 因为[-10,5,5]
                    // 但如果说 a[i]==a[j-3]=-10, a[j-2]=-5 a[j-1]=-5 之后
                    // 再次 扫描到 a[j]=-5,
                    // 他是没有意义的, 因为不能存在 两个 [-10,5,5], 这是题目要求的
                    continue;
                }
                int c = 0 - (nums[i] + nums[j]);
                if (set.find(c) != set.end()) {
                    result.push_back({nums[i], nums[j], c});
                    set.erase(c);// 三元组元素c去重
                } else {
                    // 假设 -10,4,5,6
                    // -10,4 扫完以后 把4进去set 等待匹配
                    // 扫到6 的时候 发现等待匹配里面有4, 就取出来
                    set.insert(nums[j]);
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


