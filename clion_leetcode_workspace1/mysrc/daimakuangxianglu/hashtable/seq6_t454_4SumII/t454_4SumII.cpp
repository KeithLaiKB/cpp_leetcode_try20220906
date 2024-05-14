#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given four integer arrays nums1, nums2, nums3, and nums4 all of length n,
 * return the number of tuples (i, j, k, l) such that:

    0 <= i, j, k, l < n
    nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

 * Example1:
 * Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
 * Output: 2
 * Explanation:
 * The two tuples are:
 * 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
 * 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

 *
 * Example2:
 * Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
 * Output: 1
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

    // 时间复杂度：O(n)
    // 空间复杂度：O(n)
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> uodmap_sum1_2;
        int tmp1=0;
        int tmp2=0;
        int tmp3=0;
        int tmp4=0;

        int rs_count=0;

        // {-1,2} {1,-2} {5,3} {-5,2}
        for(int i =0;i<=nums1.size()-1;i++){
            tmp1 = nums1[i];

            for(int j = 0;j<=nums2.size()-1;j++){
                tmp2 = nums2[j];
                ++uodmap_sum1_2[tmp1+tmp2];
            }
        }

        for(int i =0;i<=nums3.size()-1;i++){
            tmp3 = nums3[i];

            for(int j = 0;j<=nums4.size()-1;j++){
                tmp4 = nums4[j];

                int rest_num = 0-(tmp3 + tmp4);

                if(uodmap_sum1_2.find(rest_num)!=uodmap_sum1_2.end()){
                    // 例如 {-1,1,5,-5} 和  {2,-2,5,-5}
                    // 所以 在5和-5的情况下 对应 的 nums1和nums2的组的可能有两个
                    // {-1,1} 和 {2,-2}
                    rs_count = rs_count + uodmap_sum1_2[rest_num];
                }
            }
        }

        return rs_count;
    }


};

/**
 * feature:
 * 1. 要一个set去重
 *
 * 思路():
 * 1. 把过程都记录下来, 发现过程重复 证明无法最终到头
 *
 *
 * */
int main() {
    Solution* solut1 = new Solution();

    vector<int> intvec1={1,2};
    vector<int> intvec2={-2,-1};
    vector<int> intvec3={-1,2};
    vector<int> intvec4={0,2};
    //vector<int>* intvec1P=&intvec1;
    int target = 9;

    int rs_int=solut1->fourSumCount(intvec1,intvec2,intvec3,intvec4);

    cout<<"result"<<endl;
    cout<<rs_int<<endl;





    return 0;
}


