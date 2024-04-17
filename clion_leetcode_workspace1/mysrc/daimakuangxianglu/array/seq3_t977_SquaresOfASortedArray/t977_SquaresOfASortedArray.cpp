#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given an integer array nums sorted in non-decreasing order,
 * return an array of the squares of each number sorted in non-decreasing order.
 *
 * Example:
 * Input: nums = [-4,-1,0,3,10]
 * Output: [0,1,9,16,100]
 * Explanation: After squaring, the array becomes [16,1,0,9,100].
 * After sorting, it becomes [0,1,9,16,100].
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   他是直接在原来数组上改变, 因为他不关心里面有没有改变, 只关心返回的k是不是正确的
    vector<int> sortedSquares(vector<int>& nums) {
        int og_length = nums.size();
        int st_indx = 0;
        int ed_indx = og_length -1;

        vector<int> intvec_rs(nums.size(),-999);
        int ed_rsindx=nums.size()-1;

        int st_num_tmp_sqr=-1;
        int ed_num_tmp_sqr=-1;


        for(;st_indx<=ed_indx;ed_rsindx--){
            st_num_tmp_sqr = nums[st_indx] *nums[st_indx];
            ed_num_tmp_sqr = nums[ed_indx] *nums[ed_indx];
            // 我的案例1
            //               st        ed                new_ed
            //og             -4,-1,0,3,10        0,0,0,0,0
            //               st      ed                  new_ed
            // 16<100   ->   -4,-1,0,3,10        0,0,0,0,100
            //                   st  ed                new_ed
            // 16>9     ->   -4,-1,0,3,10        0,0,0,16,100
            //                  st ed                new_ed
            // 1<9      ->   -4,-1,0,3,10        0,0,9,16,100
            //                   st/ed             new_ed
            // 1>0      ->   -4,-1,0,3,10        0,1,9,16,100
            //                   edst            new_ed
            // 0=0      ->   -4,-1,0,3,10        0,1,9,16,100


            // 我的案例2
            //               st        ed                new_ed
            //og             -4,-3,-1,1,2         0,0,0,0,0
            //                  st     ed                new_ed
            // 16>4     ->   -4,-3,-1,1,2         0,0,0,0,16
            //                     st  ed              new_ed
            // 9>4      ->   -4,-3,-1,1,2         0,0,0,9,16
            //                     st ed            new_ed
            // 1<=1     ->   -4,-3,-1,1,2         0,0,4,9,16
            //                    st/ed            new_ed
            // 0<1      ->   -4,-3,-1,1,2         0,1,9,16,16
            //                 ed st              new_ed
            // 0=0      ->   -4,-3,0,1,2          0,1,9,16,16
            if(st_num_tmp_sqr<=ed_num_tmp_sqr){
                intvec_rs[ed_rsindx] = ed_num_tmp_sqr;
                ed_indx--;
            }
            else if(st_num_tmp_sqr>ed_num_tmp_sqr){
                intvec_rs[ed_rsindx] = st_num_tmp_sqr;
                st_indx++;
            }

            for(int i=0;i<=intvec_rs.size()-1;i++){
                cout<<intvec_rs[i]<<"\t";
                if(i==intvec_rs.size()-1){
                    cout<<endl;
                }
            }
        }
        return intvec_rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();
    //vector<int> intvec={-4,-1,0,3,10};
    vector<int> intvec={-7,-3,2,3,11};
    intvec.reserve(10000);  //这是题目要求里length说的. 虽然暂时没有10000个
    //vector<int> intvec={3,2,2,3};

    int mytarget = 2;
    //int mytarget = 3;


    vector<int> intvec_result = solut1->sortedSquares(intvec);

    for(int i=0;i<=intvec_result.size()-1;i++){
        cout<<intvec_result[i]<<"\t";
        if(i==intvec_result.size()-1){
            cout<<endl;
        }
    }



    return 0;
}


