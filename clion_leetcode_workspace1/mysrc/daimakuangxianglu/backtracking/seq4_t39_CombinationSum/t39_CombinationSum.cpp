#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given an array of distinct integers candidates and a target integer target,
 *
 * return a list of all unique combinations of candidates where the chosen numbers sum to target.
 *
 * You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times.
 * Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 *
 * The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 *
 *
 * Example1:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 * Explanation:
 *  2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 *  7 is a candidate, and 7 = 7.
 *  These are the only two combinations.
 *
 * Example2:
 * Input: candidates = [2,3,5], target = 8
 * Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 *
 * Example3:
 * Input: candidates = [2], target = 1
 * Output: []
 *
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

    template<typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }
    // 假设 target=7
    //
    // 我们拿最小值, 这样可以获得最长的路径
    // 可以看到 树的最高深度为 7/2 =3                  ->  深度 = T(target)/M(最小值)
    // 然后树的每个节点 在不剪枝的情况下 都有3个节点       ->  每个节点的可能性 = n
    //
    // 所以时间复杂度: O( n* (T/M) )
    // 空间复杂度: O(T/M)
    //      因为最多就是 长度为 最长的path= target/ 最小值   从而得到的最大深度，也就是空间复杂度，
    //      其他的不用怎么看 就算是有小的复杂度 也不会高于它, 不会太影响这个数字
    //
    //                                  [2,3,5]
    //                   |               |               |
    //                   2               3               5
    //               |   |   |        |
    //               2   3   5        5 (这里是5而不是2, 因为不用往前找了)
    //             |
    //            2
    vector<string> backtracking(vector<int>& candidates, int candd_idx, int &now_sum, const int target, vector<int> &vec_ele,vector<vector<int>> &rs1){
        //limit

        if(now_sum==target){
            rs1.push_back(vec_ele);
            return {};
        }
        // 总数超了
        else if(now_sum>target){
            return {};
        }
        //当前的这个已经超了, 就没必要往后看了
        if(candidates[candd_idx]>target){
            return {};
        }


        //deal

        //for
        for(int i =candd_idx;i<=candidates.size()-1;i++){

            now_sum+=candidates[i];
            vec_ele.push_back(candidates[i]);

            //backtracking
            backtracking(candidates,i,now_sum,target,vec_ele,rs1);

            //pop
            vec_ele.pop_back();
            now_sum-=candidates[i];

        }

        return {};
    }
    //
    //
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> rs1={};

        for(int i=0;i<=candidates.size()-1;i++){
            vector<int> vec_ele={candidates[i]};
            int sum_tmp=candidates[i];
            backtracking(candidates,i,sum_tmp,target,vec_ele,rs1);
        }

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={2,3,6,7};
    int mytarget = 7;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;

    vector<vector<int>> rs1 = solut1->combinationSum(intvec1,mytarget);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


