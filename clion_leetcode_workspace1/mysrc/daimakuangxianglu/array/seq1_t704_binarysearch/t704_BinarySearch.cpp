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
    // 空间复杂度：O(1)
    int search(vector<int>& nums, int target) {
        int st=0;
        int ed=nums.size()-1;
        int mid=-1;

        int rs_indx = -1;   // -1 means cannot find

        for (;st<ed;){
            mid = (st+ed)/2 ;
            if (nums[mid]==target)
            {
                rs_indx = mid;
                break;
            }
            else if (target<nums[mid]){
                ed=mid-1;
            }
            else if (target>nums[mid]){
                st=mid+1;
            }
            cout<<"st:"<<st<<"mid:"<<mid<<"ed:"<<ed<<endl;
        }
        return rs_indx;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int>* intvec = new vector<int>();
    int mytarget = -1;

    vector<int> intvec_rs1;
    // insert example
    intvec->push_back(-1);
    intvec->push_back(0);
    intvec->push_back(3);
    intvec->push_back(5);
    intvec->push_back(9);
    intvec->push_back(12);

    //mytarget = 9;
    mytarget = 6;

    int indx_rs1 = -1;
    indx_rs1 = solut1->search(*intvec,mytarget);
    cout<<"position index:"<<indx_rs1<<endl;


    return 0;
}


