#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given two integer arrays nums1 and nums2, return an array of their intersection.
 * Each element in the result must be unique and you may return the result in any order.
 *
 * Example1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 *
 * Example2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * Explanation: [4,9] is also accepted.
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_VectorBintB(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }


    // 时间复杂度：O(n+m), m是return 那里set转化成vector
    // 空间复杂度：O(n)
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> myset_interst1(nums1.begin(),nums1.end());
        unordered_set<int> myset_rs;

        for(int i =0;i<=nums2.size()-1;i++){
            if(myset_interst1.find(nums2[i])!=myset_interst1.end()){
                myset_rs.insert(nums2[i]);
            }

        }


        return vector<int> (myset_rs.begin(),myset_rs.end());
    }

};

/**
 * feature:
 * 1. 要一个set去重
 *
 * 思路():
 * 1. 先把第一组丢进set里
 * 2.1 然后把第二组 去对比 第一组里有没有
 * 2.2 如果有就放进去 从而做并集
 * 2.3 如果没有就不放进去
 *
 *
 * */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> intvec1 = {1,2,2,1};
    vector<int> intvec2 = {2,2};

    vector<int> rs_intvec1=solut1->intersection(intvec1,intvec2);


    cout<<"result"<<endl;
    solut1->myOutput_VectorBintB(rs_intvec1,0,rs_intvec1.size()-1);





    return 0;
}


