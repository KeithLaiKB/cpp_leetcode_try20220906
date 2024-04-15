#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * Given an array of integers nums which is sorted in ascending order,
 * and an integer target, write a function to search target in nums.
 * If target exists, then return its index. Otherwise, return -1.

 * You must write an algorithm with O(log n) runtime complexity.
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    // 时间复杂度：O(log n)
    // 空间复杂度：O(1)   他是直接在原来数组上改变, 因为他不关心里面有没有改变, 只关心返回的k是不是正确的
    int removeElement(vector<int>& nums, int val) {
        int og_length = nums.size();
        int og_indx = 0;
        int nw_indx = 0;

        int result_length = -1;

        for(;og_indx<=og_length-1;og_indx++){
            if(nums[og_indx]!=val){
                nums[nw_indx]=nums[og_indx];
                nw_indx++;
            }
        }

        result_length = (nw_indx-1)+1;
        return result_length;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();
    vector<int> intvec={0,1,2,2,3,0,4,2};
    //vector<int> intvec={3,2,2,3};

    int mytarget = 2;
    //int mytarget = 3;


    int indx_rs1 = -1;
    indx_rs1 = solut1->removeElement(intvec,mytarget);
    cout<<"array length:"<<indx_rs1<<endl;


    return 0;
}


