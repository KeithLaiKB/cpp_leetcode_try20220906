#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given an array of positive integers nums and a positive integer target,
 * return the minimal length of a subarray whose sum is greater than or equal to target.
 * If there is no such subarray, return 0 instead.
 *
 * Example:
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem constraint.
 * 7=4+3
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    int minSubArrayLen(int target, vector<int>& nums) {
        int st_indx = 0;
        int ed_indx = 0;

        int minimal_sum = 0;
        int sum_tmp1 = 0;
        int minimal_length = INT32_MAX;


        for (; ed_indx <= nums.size()-1; ed_indx++) {
            sum_tmp1 = sum_tmp1 + nums[ed_indx];

            for(int myloadi=st_indx;myloadi<=ed_indx;myloadi++){
                cout<<nums[myloadi]<<"\t";
                if(myloadi==ed_indx){
                    cout<<endl;
                }
            }

            if (sum_tmp1 >= target) {
                for (; st_indx <= ed_indx;) {
                    sum_tmp1 = sum_tmp1 - nums[st_indx];
                    st_indx++;


                    for(int myloadi=st_indx;myloadi<=ed_indx;myloadi++){
                        cout<<nums[myloadi]<<"\t";
                        if(myloadi==ed_indx){
                            cout<<endl;
                        }
                    }

                    if (sum_tmp1 < target) {
                        break;
                    }
                    int sub_length = ed_indx - st_indx + 1;
                    minimal_length = minimal_length < sub_length? minimal_length : sub_length;
                    minimal_sum = sum_tmp1;
                    cout<<"(length:"<<minimal_length<<"sum:"<<minimal_sum<<")"<<endl;
                }
            }
            else if (sum_tmp1 < target) {
                //
            }

        }

        return minimal_length == INT32_MAX ? 0 : minimal_length;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();
    vector<int> intvec={3,3,2,1,4,3};
    //vector<int> intvec={2,3,1,2,4,3};
    intvec.reserve(100000);  //这是题目要求里length说的. 虽然暂时没有100000个
    //vector<int> intvec={3,2,2,3};

    int mytarget = 7;
    //int mytarget = 3;


    int result= solut1->minSubArrayLen(mytarget,intvec);
    cout<<"result"<<result<<endl;

    /*for(int i=0;i<=intvec_result.size()-1;i++){
        cout<<intvec_result[i]<<"\t";
        if(i==intvec_result.size()-1){
            cout<<endl;
        }
    }*/



    return 0;
}


