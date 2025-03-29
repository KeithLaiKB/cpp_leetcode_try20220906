#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <algorithm>
#include <unordered_set>

using namespace std;

/**
 *
 * Given a collection of candidate numbers (candidates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sum to target.
 *
 * Each number in candidates may only be used once in the combination.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 *
 * Example1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output:
 * [
 * [1,1,6],
 * [1,2,5],
 * [1,7],
 * [2,6]
 * ]
 *
 * Example2:
 * Input: candidates = [2,5,2,1,2], target = 5
 * Output:
 * [
 * [1,2,2],
 * [5]
 * ]
 *
 *

 *
 * 根据已有数字的数组, 从中选出 若干个数字, 从而组成集合 从而得到 sum==target
 * 注意
 *  每个idx上的数字不可重复使用, 但组成的每个集合不能重复
 *      但是 已知原来的输入 是包含重复元素的
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

    bool static mycomp(const int &a, const int& b){
        return a<b;
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
    //      depth=1 的节点相同的情况
    //                                                                          [2,2,3,5]
    //                   |               |                                                                                           |
    //                   2               2 (同一个数字不能出现在相同层, 按道理这里就该结束了 如果还是有疑惑继续往下看)                            3                       5
    //               |   |   |        |
    //               2   3   5        3 (假设你强行往下到这里, 无论如何都没有用)
    //             |                    (因为前面那个分支的 [2,3] 早就已经包含了, 因为我们现在这个数组的前提是 已经事先 排好序的！！！！！)
    //            3                     (所以就不应该下到这个位置, 在上面就应该结束了)
    //
    //      depth=2 的节点相同的情况
    //                                                                          [2,3,3,5]
    //                                      |                                                                                               |                               |                        |
    //                                      2                                                                                               3   a[i-1]!=a[i],可以往下走       3                        5
    //               |                                              |                                                                    |     |                          |
    //               3 (used={1,1,0,0,0})                           3  (used={1,0,1,0,0})                                                3     5                          5
    //             |                                                    左边的兄弟节点 a[i-1] ==  当前的 a[i] 数字重复了
    //            3 (used={1,1,1,0,0})                                      但是 used[i-1]=0, used[i]=1
    //              虽然此时                                                也就是说此时的 a[i-1] 不是 a[i]的父亲节点,
    //                  上面的根节点 a[i-1] ==  当前的 a[i] 数字重复了               也就是说a[i-1] == a[i]
    //              但是 used[i-1]=1, used[i]=1
    //                  也就是说此时的 a[i-1] 是 a[i]的父亲节点,
    //              所以是允许的
    //
    //(因为前面那个分支的 [2,3] 早就已经包含了, 因为我们现在这个数组的前提是 已经事先 排好序的！！！！！)                  (所以就不应该下到这个位置, 应该跳过返回上面 看后面的那个5了)
    //      那么 我们需要讨论 同层不能出现 这个问题 于是我们引入了 path_arrvied
    vector<string> backtracking(vector<int>& candidates, int candd_idx, int &now_sum, const int target, vector<int> &vec_ele,vector<vector<int>> &rs1, vector<int> &path_arrvied){
        //limit

        // 检查上轮结果
        if(now_sum==target){
            rs1.push_back(vec_ele);
            return {};
        }
        // 总数超了
        else if(now_sum>target){
            return {};
        }

        //当前的这个已经超了, 就没必要往后看了, 剪枝
        //  例如当前元素  是 5, target是3, 那就没有必要往后看了
        if(candd_idx<=candidates.size()-1 && candidates[candd_idx]>target){
            return {};
        }


        //deal

        //for
        for(int i =candd_idx;i<=candidates.size()-1;i++){
            //-----------和t39的区别------------------
            //去重
            //发现 candidates[i-1] 与 candidates[i] 是 同一父节点 下同一层的兄弟节点
            if(path_arrvied[i-1]==0 && candidates[i-1] == candidates[i]){
                continue;
            }
            //--------------------------------------

            now_sum+=candidates[i];
            path_arrvied[i] =1;
            vec_ele.push_back(candidates[i]);

            //-----------和t39的区别------------------
            //backtracking
            backtracking(candidates,i+1,now_sum,target,vec_ele,rs1,path_arrvied);
            //--------------------------------------

            //pop
            vec_ele.pop_back();
            now_sum-=candidates[i];
            //-----------和t39的区别------------------
            path_arrvied[i] =0;
            //--------------------------------------

        }

        return {};
    }


    // 这是t491的unorder set方案  完全可以通过leetcode
    // 这个里面不会用到path_arrvied, 但是我就不删除了 方便你对着看, 这里相比正式的 增加了两处
    //
    vector<string> backtracking_v2(vector<int>& candidates, int candd_idx, int &now_sum, const int target, vector<int> &vec_ele,vector<vector<int>> &rs1, vector<int> &path_arrvied){
        //limit

        // 检查上轮结果
        if(now_sum==target){
            rs1.push_back(vec_ele);
            return {};
        }
            // 总数超了
        else if(now_sum>target){
            return {};
        }

        //当前的这个已经超了, 就没必要往后看了, 剪枝
        //  例如当前元素  是 5, target是3, 那就没有必要往后看了
        if(candd_idx<=candidates.size()-1 && candidates[candd_idx]>target){
            return {};
        }


        //deal
        //-----------t491的unordered set方案------------------
        unordered_set<int> unord_set1; // 使用set对本层元素进行去重
        //--------------------------------------
        //for
        for(int i =candd_idx;i<=candidates.size()-1;i++){
            /*
            //去重
            //发现 candidates[i-1] 与 candidates[i] 是 同一父节点 下同一层的兄弟节点
            if(path_arrvied[i-1]==0 && candidates[i-1] == candidates[i]){
                continue;
            }
            */

            //-----------t491的unordered set方案------------------
            if (unord_set1.find(candidates[i]) != unord_set1.end()) {
                continue;
            }
            unord_set1.insert(candidates[i]);
            //--------------------------------------

            now_sum+=candidates[i];
            path_arrvied[i] =1;
            vec_ele.push_back(candidates[i]);


            //backtracking
            backtracking(candidates,i+1,now_sum,target,vec_ele,rs1,path_arrvied);


            //pop
            vec_ele.pop_back();
            now_sum-=candidates[i];

            path_arrvied[i] =0;


        }

        return {};
    }





    //时间复杂度: O(n * 2^n)
    //  因为每个candidate_idx 在同一个结果集中 只能出现一次,
    //  也就是 有  出现 或者 不出现 两种情况 所以右 2^n
    //  每次超过一维的vector 关于，push_back的时间为 O(n),
    //      因为push_back对于基本类型和指针是O(1)，
    //          但对于需要深拷贝的复杂对象（如向量），它是O(对象大小)的。
    //  所以是 O(n * 2^n)
    //
    //空间复杂度: O(n)
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

        //方便剪枝 先排序
        sort(candidates.begin(),candidates.end(), mycomp);

        vector<vector<int>> rs1={};

        vector<int> path_arrvied(candidates.size(),0);

        for(int i=0;i<=candidates.size()-1;i++){

            //-----------和t39的区别------------------
            //去重
            // 如果path_arrvied[i]==0 那意味着 这个不是从 前一个节点下来的
            if(i>=1 && candidates[i-1] == candidates[i] ){
                continue;
            }
            path_arrvied[i]=1;
            //--------------------------------------

            vector<int> vec_ele={candidates[i]};
            int sum_tmp=candidates[i];

            //-----------和t39的区别------------------
            path_arrvied[i]=1;
            backtracking(candidates,i+1,sum_tmp,target,vec_ele,rs1,path_arrvied);

            //pop
            path_arrvied[i]=0;
            //--------------------------------------
        }

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={10,1,2,7,6,1,5};
    int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;

    vector<vector<int>> rs1 = solut1->combinationSum2(intvec1,mytarget);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


