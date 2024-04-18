#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given two strings s and t of lengths m and n respectively,
 * return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string ""
 *
 * Example:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
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

    void myOutput_Vector(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    int minSubArrayLen(int target, vector<int>& nums) {
        int st_indx = 0;
        int ed_indx = 0;

        //这题目用不到  但是我想用来记录 从而更好的发现这个程序的规律
        // 例如 如果 过程中 最小length相同的 array有两组
        // 他记录的是最开始的那组, 所以你会发现 {2,1,4} 它没记录7而是记录之前的8
        int minimal_sum = 0;


        int sum_tmp1 = 0;
        int minimal_length = INT32_MAX;


        for (; ed_indx <= nums.size()-1; ed_indx++) {
            sum_tmp1 = sum_tmp1 + nums[ed_indx];

            //output test
            myOutput_Vector(nums,st_indx,ed_indx);

            if (sum_tmp1 >= target) {
                // 符合标准 先记下当前的sublength
                int sub_length = ed_indx - st_indx + 1;
                if(minimal_length > sub_length){
                    minimal_length = sub_length;
                    minimal_sum = sum_tmp1;
                    //output test
                    cout<<"(length:"<<minimal_length<<"sum:"<<minimal_sum<<")"<<endl;
                }

                // 达到标准 就把 st_indx 往后推,
                // 尝试获得比较小 而且 符合 target的范围
                for (; st_indx <= ed_indx;) {
                    sum_tmp1 = sum_tmp1 - nums[st_indx];
                    st_indx++;

                    //output test
                    myOutput_Vector(nums,st_indx,ed_indx);

                    // 缩小失败, 返回到外层循环 让它去移动ed_index
                    if (sum_tmp1 < target) {
                        break;
                    }

                    // 缩小成功 查看是否比之前的length还要小
                    sub_length = ed_indx - st_indx + 1;
                    if(minimal_length > sub_length){
                        minimal_length = sub_length;
                        minimal_sum = sum_tmp1;
                    }
                    //output test
                    cout<<"(length:"<<minimal_length<<"sum:"<<minimal_sum<<")"<<endl;
                }
            }
            else if (sum_tmp1 < target) {
                // do nothing
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


