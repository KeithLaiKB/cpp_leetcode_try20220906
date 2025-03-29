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
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 *
 * Example1:
 * Input: nums = [4,6,7,7]
 * Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example2:
 * Input: nums = [4,4,3,2,1]
 * Output: [[4,4]]
 *
 * 输入数组 不能被重新排序,并且不能少于两个数字
 *  找出所有递增的子集
 *  感觉这个是 t40的升级版, 因为t40它本身是允许 自己排序的
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


    vector<string> backtracking(vector<int>& candidates, int candd_idx, vector<int> &vec_ele,vector<vector<int>> &rs1){
        //limit
        //-----------和t40的区别------------------
        // 检查上轮结果
        if(candd_idx==candidates.size()){
            return {};
        }


        //--------------------------------------

        //deal
        unordered_set<int> unord_set1={};
        //for
        for(int i =candd_idx;i<=candidates.size()-1;i++){


            //去重
            if (unord_set1.find(candidates[i]) != unord_set1.end()) {
                continue;
            }

            // 如果和已经放进集合里的 最后一个元素形成 递减
            // 则继续看他的兄弟节点
            // 例如 [4,7,3,9] ,从上一层 到这里时[4,7],
            // 扫描这一层的时候3 不成功 不要break, 因为可以看兄弟9, 从而形成[4,7,9]
            //
            if(vec_ele.size()>=1 && vec_ele[vec_ele.size()-1]>candidates[i]){
                continue;
            }

            unord_set1.insert(candidates[i]);
            vec_ele.push_back(candidates[i]);

            if(vec_ele.size()>=2){
                rs1.push_back(vec_ele);
            }

            //backtracking
            backtracking(candidates,i+1,vec_ele,rs1);

            //pop
            vec_ele.pop_back();

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
    vector<vector<int>> findSubsequences(vector<int>& nums) {



        vector<vector<int>> rs1={};
        //deal
        unordered_set<int> unord_set1={};
        vector<int> vec_ele={};

        for(int i=0;i<=nums.size()-1;i++){

            //去重
            if (unord_set1.find(nums[i]) != unord_set1.end()) {
                continue;
            }

            vec_ele.push_back(nums[i]);
            unord_set1.insert(nums[i]);

            //backtracking
            backtracking(nums,i+1,vec_ele,rs1);

            //pop
            vec_ele.pop_back();
        }

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={4,6,7,7};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    //string str1 ="101023";
    vector<vector<int>> rs1 = solut1->findSubsequences(intvec1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


