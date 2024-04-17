#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * Given an integer array nums and an integer val, remove all occurrences of val in nums in-place.
 * The order of the elements may be changed.
 * Then return the number of elements in nums which are not equal to val.
 *
 * Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:
 * Change the array nums such that the first k elements of nums contain the elements which are not equal to val.
 * The remaining elements of nums are not important as well as the size of nums.
 * Return k.
 *
 * Example:
 * Input: nums = [0,1,2,2,3,0,4,2], val = 2
 * Output: 5, nums = [0,1,4,0,3,_,_,_]
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


