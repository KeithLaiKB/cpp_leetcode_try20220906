#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
 * Only numbers 1 through 9 are used.
 * Each number is used at most once.
 *
 *
 * Return a list of all possible valid combinations.
 * The list must not contain the same combination twice, and the combinations may be returned in any order.
 *
 *
 * Example1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 * Explanation:
 * 1 + 2 + 4 = 7
 * There are no other valid combinations.
 *
 * Example2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6],[1,3,5],[2,3,4]]
 * Explanation:
 * 1 + 2 + 6 = 9
 * 1 + 3 + 5 = 9
 * 2 + 3 + 4 = 9
 * There are no other valid combinations.
 *
 *
 * Example3:
 * Input: k = 4, n = 1
 * Output: []
 * Explanation: There are no valid combinations.
 * Using 4 different numbers in the range [1,9],
 * the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.
 *
 * 这个就是 k 个 数字 组成一个 sum=n的 vector<vector<int>>
 *
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    void myOutput_VectorBVectorBintBB(vector<vector<int>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            for(int j=0;j<=nums[i].size()-1;j++){

                cout<<nums[i][j]<<"\t";
                if(j==nums[i].size()-1){
                    cout<<endl;
                }

            }
        }
    }
    // st_num,ed_num代表范围
    // vec1 代表组合
    // now_sum 代表当前总和
    // vec_rs1 代表 结果集合
    // target 代表sum 最终要到达的数字
    vector<int> backtracking(int st_num, int ed_num, const int k, vector<int> &vec1, int& now_sum,vector<vector<int>> &vec_rs1, const int target){
            //limit
            if(st_num > ed_num || vec1.size()+1>k){
                return {};
            }
            //deal
            //for
            for(int i=st_num;i<=ed_num;i++){
                if(now_sum+i>target ){
                    break;
                }
                // sum相同 数量K相同, 则 塞入结果集合
                else if(now_sum+i==target && vec1.size()+1==k){
                    vec1.push_back(i);
                    vec_rs1.push_back(vec1);
                    //
                    vec1.pop_back();
                    break;
                }
                // 提前完成 是不允许的
                else if(now_sum+i==target && vec1.size()+1!=k){
                    break;
                }
                // sum不同 还有不同种做法
                else if(now_sum+i<target && vec1.size()+1>k){
                    break;
                }
                else if(now_sum+i<target && vec1.size()+1==k){
                    //例如 k=3,n=7
                    // 1+2+3 的时候他 是满足当强条件的
                    // 但不可以break
                    // 因为下一轮可以 1+2+4=7
                    continue;

                }
                else if(now_sum+i<target && vec1.size()+1<k){
                    vec1.push_back(i);
                    //
                    now_sum+=i;
                    backtracking(i+1,ed_num,k,vec1,now_sum,vec_rs1,target);
                    //pop
                    now_sum-=i;
                    vec1.pop_back();
                }
            }
            return {};
    }
    //
    //
    // 时间复杂度： O(C(9,k) × k)
    //   关于push_back和pop_back操作：
    //      虽然单次操作可以看作O(1)
    //      但是对于每个组合，我们仍需要进行k次这样的操作
    //
    //
    //
    // 空间复杂度： O(k)（辅助空间）或 O(C(9,k) × k)（包括结果存储）
    //
    //    空间复杂度需要考虑：
    //    1.递归栈深度：最深为k层，因此为O(k)
    //    2.存储结果的空间：有C(n,k)个结果，每个结果占用O(k)空间，因此为O(k × C(n,k))
    //
    //    总空间复杂度为 O(k) + O(k × C(n,k)) = O(k × C(n,k))，因为结果存储空间远大于递归栈空间。
    //
    //
    //                                  [1,2,3,4]
    //            |                       |                 |           |
    //           [1]                     [2]                [3]         [4]
    //       |    |    |               |    |                |
    //      [2]  [3]  [4]             [3]  [4]              [4]
    //
    //
    // 这就是回溯 把所有可能性都回溯一遍
    // k 是 一个集合里有多少个数字, n 是 sum 的target
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> rs1={};
        for(int i=1;i<=9;i++){
            int now_sum_tmp=0;

            // 添加
            vector<int> vec1_tmp={i};
            now_sum_tmp+=i;
            //
            backtracking(i+1,9,k,vec1_tmp,now_sum_tmp,rs1,n);
        }
        return rs1;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
   // vector<int> intvec1 ={-1,0,3,5,9,12};


    //int mytarget = 5;

    int indx_rs1 = -1;

    int k = 3;
    int n =7;

    vector<vector<int>> rs1 = solut1->combinationSum3(k,n);
    cout<<"result:"<<indx_rs1<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size());

    return 0;
}


