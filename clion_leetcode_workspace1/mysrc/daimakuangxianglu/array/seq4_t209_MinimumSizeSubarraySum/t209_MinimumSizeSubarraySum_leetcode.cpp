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
        int left =0;
        int right =0;
        vector <int> sol;
        int sum=nums[0];
        while(left<nums.size()){
            while(sum<target && right<(nums.size()-1)){
                right++;
                sum+=nums[right];

                for(int myloadi=left;myloadi<=right;myloadi++){
                    cout<<nums[myloadi]<<"\t";
                    if(myloadi==right){
                        cout<<endl;
                    }
                }

            }
            if(sum>=target){
                sol.push_back(right-left+1);
            }

            // if(right=nums.size()){
            //     break;
            // }
            sum-=nums[left];
            left++;


            for(int myloadi=left;myloadi<=right;myloadi++){
                cout<<nums[myloadi]<<"\t";
                if(myloadi==right){
                    cout<<endl;
                }
            }

        }
        int min =INT32_MAX;
        for(int i =0; i<sol.size();i++){
            if(sol[i]<min){
                min=sol[i];
            }
        }
        if(min!=INT32_MAX)
            return min;
        else
            return 0;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();
    vector<int> intvec={3,3,2,1,4,3};
    //vector<int> intvec={-2,3,1,2,4,3};
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


