#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 关于hashmap时间复杂度
 * 如果能在桶里直接找到 则复杂度为o(1)
 * 如果找不到
 *  则需要在桶里找,
 *      如果桶内数量<=6   则桶内是链表      则时间复杂度(包括查找桶内)为   o(1)+o(n)       = o(n)
 *      如果桶内数量>6    则桶内是红黑树     则时间复杂度(包括查找同内)为   o(1)+o(log2^n) = o(log2^n)
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        unordered_map<int,int> mpp;
        for(int i = 0;i<nums.size();i++)
        {
            // 2 7 11 15
            // assume target 26
            //
            //      2
            // map:
            // 26-2=24
            // mpp.find(24) 不存在
            // map: 2,0
            //
            //      7
            // map: 2,0
            // 26-7=19
            // mpp.find(19) 不存在
            // map: 2,0     7,1
            //
            //      11
            // map: 2,0     7,1
            // 26-11=15
            // mpp.find(15) 不存在
            // map: 2,0     7,1     11,2
            //
            //      15
            // map: 2,0     7,1     11,2
            // 26-15=11
            // mpp.find(11) 存在
            // 成功

            // 如果 没找到这个元素 则 == mpp.end()
            if(mpp.find(target-nums[i]) != mpp.end())
            {
                ans.push_back(mpp[target - nums[i]]);
                ans.push_back(i);
                return ans;
            }
            mpp[nums[i]] = i;
        }
        return ans;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int>* intvec = new vector<int>();
    int mytarget = -1;

    vector<int> intvec_rs1;
    // insert example

    intvec->push_back(2);
    intvec->push_back(7);
    intvec->push_back(11);
    intvec->push_back(15);

    mytarget = 9;

    intvec_rs1 = solut1->twoSum(*intvec,mytarget);
    int i =0;
    for(i=0;i<=intvec_rs1.size()-1;i++)
    {
        cout<<intvec_rs1[i]<<endl;
    }

    return 0;
}


