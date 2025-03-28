#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>

#include <algorithm>

using namespace std;

/**
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * 输入数组 可能会相同
 *  找出所有子集
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    template<typename T>
    void myOutput_VectorBVectorBintBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
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

    bool static mycomp(const int& a, const int& b){
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
    // 基本上和 t40一致 我就不解释了 而且我有文档的按照t40的来就行
    vector<string> backtracking(vector<int>& candidates, int candd_idx, vector<int> &vec_ele,vector<vector<int>> &rs1, vector<int> &path_arrvied){
        //limit
        //-----------和t40的区别------------------
        // 检查上轮结果
        if(candd_idx==candidates.size()){
            return {};
        }

        //--------------------------------------

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


            path_arrvied[i] =1;
            vec_ele.push_back(candidates[i]);
            rs1.push_back(vec_ele);
            //-----------和t39的区别------------------
            //backtracking
            backtracking(candidates,i+1,vec_ele,rs1,path_arrvied);
            //--------------------------------------

            //pop
            vec_ele.pop_back();
            //-----------和t39的区别------------------
            path_arrvied[i] =0;
            //--------------------------------------

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
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        //方便剪枝 先排序
        sort(nums.begin(),nums.end(), mycomp);

        vector<vector<int>> rs1={};

        vector<int> path_arrvied(nums.size(),0);

        for(int i=0;i<=nums.size()-1;i++){

            //-----------和t39的区别------------------
            //去重
            // 如果path_arrvied[i]==0 那意味着 这个不是从 前一个节点下来的
            if(i>=1 && nums[i-1] == nums[i] ){
                continue;
            }
            path_arrvied[i]=1;
            //--------------------------------------

            vector<int> vec_ele={nums[i]};

            //-----------和t40的区别------------------
            rs1.push_back(vec_ele);
            //--------------------------------------

            //-----------和t39的区别------------------
            path_arrvied[i]=1;
            backtracking(nums,i+1,vec_ele,rs1,path_arrvied);

            //pop
            path_arrvied[i]=0;
            //--------------------------------------
        }

        //-----------和t40的区别------------------
        // 因为它还包括 空集 所以额外加进去就好
        rs1.push_back({});
        //--------------------------------------

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={1,2,3};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    //string str1 ="101023";
    vector<vector<int>> rs1 = solut1->subsetsWithDup(intvec1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


