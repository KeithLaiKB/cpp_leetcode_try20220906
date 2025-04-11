#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>
#include <unordered_set>

#include <algorithm>

using namespace std;

/**
 *
 * Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
 *
 * Example1:
 * Input: nums = [1,1,2]
 * Output:
 * [[1,1,2],
 * [1,2,1],
 * [2,1,1]]
 *
 * Example2:
 * Input: nums = [1,2,3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 *
 *
 * 意义上:
 * 他是t46基础上 多出了一个前提条件 就是 源数组内有重复元素
 * 返回的话 跟46差不多 也是要求unique(当然46他本身就是unique的)
 * 对used数组的进行玩法, 他就是循环used数组
 * 他是找所有的可能性, 而不需要求和
 *
 * 写法上:
 * 当前题和t40的写法基本一样, 除了for循环是 i=0开始 而不是i=layer_index开始
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


    vector<string> backtracking(vector<int>& candidates, vector<int> &vec_ele,vector<vector<int>> &rs1, vector<int> &path_arrvied){
        //limit

        // 检查上轮结果
        if(vec_ele.size()==candidates.size()){
            rs1.push_back(vec_ele);
            return {};
        }


        //deal

        //for
        //-----------和t40的区别 主要这里i就是从0开始------------------
        for(int i =0;i<=candidates.size()-1;i++){
        //--------------------------------------

            if( (path_arrvied[i]==1) || (i-1>=0 && path_arrvied[i-1]==0 && candidates[i-1] == candidates[i])){
                continue;
            }


            path_arrvied[i] =1;
            vec_ele.push_back(candidates[i]);

            //-----------和t39的区别------------------
            //backtracking
            backtracking(candidates,vec_ele,rs1,path_arrvied);
            //--------------------------------------

            //pop
            vec_ele.pop_back();
            //-----------和t39的区别------------------
            path_arrvied[i] =0;
            //--------------------------------------

        }

        return {};
    }


    //时间复杂度: O(n * n!)
    //  该算法生成 n! 个排列（每个位置分别有 n, n-1, n-2, ..., 1 个选择） 所以是O(n!)
    //  每次超过一维的vector 关于，push_back的时间为 O(n),
    //      因为push_back对于基本类型和指针是O(1)，
    //          但对于需要深拷贝的复杂对象（如向量），它是O(对象大小)的。
    //  所以是O(n * n!), 但如果不考虑拷贝的复杂度的话就是 O(n!)
    //
    //空间复杂度: O(n)
    vector<vector<int>> permuteUnique(vector<int>& nums) {

        //方便剪枝 先排序
        sort(nums.begin(),nums.end(), mycomp);

        vector<vector<int>> rs1={};

        vector<int> path_arrvied(nums.size(),0);

        for(int i=0;i<=nums.size()-1;i++){


            //去重
            // 如果path_arrvied[i]==0 那意味着 这个不是从 前一个节点下来的
            if(i>=1 && nums[i-1] == nums[i] ){
                continue;
            }

            vector<int> vec_ele={nums[i]};
            path_arrvied[i]=1;

            backtracking(nums,vec_ele,rs1,path_arrvied);

            //pop
            path_arrvied[i]=0;
        }

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={1,1,2};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    //string str1 ="101023";
    vector<vector<int>> rs1 = solut1->permuteUnique(intvec1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


