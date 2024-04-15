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

        for (;st<=ed;){
            mid = (st+ed)/2 ;
            if (nums[mid]==target)
            {
                rs_indx = mid;
                cout<<"=="<<"st:"<<st<<"mid:"<<mid<<"ed:"<<ed<<endl;
                break;
            }
            else if (target<nums[mid]){
                ed=mid-1;
                cout<<"<"<<"st:"<<st<<"mid:"<<mid<<"ed:"<<ed<<endl;
            }
            else if (target>nums[mid]){
                st=mid+1;
                cout<<">"<<"st:"<<st<<"mid:"<<mid<<"ed:"<<ed<<endl;
            }
        }
        return rs_indx;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    int mytarget = 5;

    int indx_rs1 = -1;
    indx_rs1 = solut1->search(*p_intvec,mytarget);
    cout<<"position index:"<<indx_rs1<<endl;


    delete p_intvec;
    return 0;
}


