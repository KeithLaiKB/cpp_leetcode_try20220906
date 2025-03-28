#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>

#include <algorithm>

using namespace std;

/**
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example1:
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Example2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * 输入数组 不会相同
 *  找出所有子集
 *
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



    vector<int> backtracking(vector<int>& nums, int st_num, vector<int> &now_content,vector<vector<int>> &rs){
        //limit
        if(st_num==nums.size()){
            return {};
        }
        //deal
        //for
        for(int i=st_num;i<=nums.size()-1;i++){
            now_content.push_back(nums[i]);

            // [1]
            // [1,2]
            // [1,2,3]
            // 然后Pop 3      ->[1,2]
            // 再pop 2       ->[1]
            // 然后 加入2 的兄弟节点3
            // [1,3]
            // pop3, pop1   - >[]
            // [2]
            // [2,3]
            rs.push_back(now_content);

            //backtracking
            backtracking(nums, i+1,now_content,rs);

            //pop
            now_content.pop_back();
        }
        return {};
    }

    //
    // 时间复杂度: O(n*2^n)
    //      子集的总数为：2^n, 因为在集合中 每个元素有出现或不出现的情况
    //      每次 vector 还要塞入 vector<vector<int>> 里面, 所以需要复制数组 也就是 n
    //      所以总体是 O(n*2^n)
    //空间复杂度:
    //      O(n*2^n)
    //    [
    //    [],        // 空集
    //    [1],
    //    [2],
    //    [1, 2],
    //    [3],
    //    [1, 3],
    //    [2, 3],
    //    [1, 2, 3]
    //    ]
    //
    //      这一看就是右 2^n个结果
    //      但是每个结果里面又有元素, 假设每个结果里的元素为n
    //      所以这是二维数组 也就是 O(n*2^n)
    //
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> rs={};
        vector<int> now_content = {};
        backtracking(nums,0,now_content,rs);

        // 因为它还包括 空集 所以额外加进去就好
        rs.push_back({});
        return rs;
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
    vector<vector<int>> rs1 = solut1->subsets(intvec1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


