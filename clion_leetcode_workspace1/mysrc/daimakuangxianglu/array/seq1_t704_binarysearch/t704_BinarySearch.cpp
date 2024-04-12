#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * 关于hashmap时间复杂度
 * 如果能在桶里直接找到 则复杂度为o(1)
 * 如果找不到
 *  则需要在桶里找,
 *      如果桶内数量<=6   则桶内是链表      则时间复杂度(包括查找桶内)为   o(1)+o(n)       = o(n)
 *      如果桶内数量>6    则桶内是红黑树     则时间复杂度(包括查找同内)为   o(1)+o(log2^n) = o(log2^n)
 *
 * 这个6好像不一定对, 但大概这么一个意思
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    int search(vector<int>& nums, int target) {

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

    string str1 = "abc";
    string str2 = "abc";
    if(str1.compare(str2)==0){
        cout<<"yes"<<endl;
    }

    return 0;
}


