#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 * Given two integers n and k,
 *
 *
 * return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 *
 * c(4,2)个组合
 *
 * Example 1:
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 *
 *
 * Example 2:
 * Input: n = 1, k = 1
 * Output: [[1]]
 * Explanation: There is 1 choose 1 = 1 total combination.
 *
 * 就是从[1,n]的范围内, 找出所有 能拼成 元素数量为k的 集合
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
    //
    vector<int> backtracking(int st_num, int ed_num, int k, vector<int> &vec1,vector<vector<int>> &vec_rs1){
            //limit
            if(k==0){
                vec_rs1.push_back(vec1);
                return {};
            }
            //deal

            //for
            // 方法一: 成功
            //for(int i=st_num;i<=ed_num;i++){
            // 方法二: 代码狂想录上有解释,我这里改了一下
            //for (int i = st_num; i<= ed_num && vec1.size()+k<=ed_num ; i++){
            // 方法三：
            //  假设我们还需要选择 k 个元素，当前位置是 i，那么：
            //        当前位置 i 可以选择一个元素
            //        我们还需要从 i+1 到 ed_num 之间选择 k-1 个元素
            //  所以，i 的最大可能值应该满足：从 i+1 到 ed_num 至少有 k-1 个元素可选, 这意味着：
            //
            //        ed_num - (i+1) + 1 ≥ k-1
            //        简化得：ed_num - i ≥ k-1
            //        进一步变形：i ≤ ed_num - (k-1)
            //
            for(int i = st_num; i <= ed_num-(k-1); i++) {
                //deal
                vec1.push_back(i);
                backtracking(i+1,ed_num,k-1,vec1,vec_rs1);
                //pop
                vec1.pop_back();
            }
            return {};
    }
    //
    //
    // 时间复杂度： O(C(n,k) × k)
    //   关于push_back和pop_back操作：
    //      虽然单次操作可以看作O(1)
    //      但是对于每个组合，我们仍需要进行k次这样的操作
    //
    //      因此总时间复杂度应为：O(C(n,k) × k)，即O(n!/(k!(n-k)!) × k)
    //      这可能会简化为O(C(n,k))，如果我们认为k相对于n和组合数量来说足够小，可以被视为常数。但严格来说，应该是O(C(n,k) × k)。
    //
    //
    // 空间复杂度： O(C(n,k) × k)
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
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vec_vecBintB1 = {};

        for(int i=1;i<=n;i++){
            vector<int> vec_tmp={i};
            backtracking(i+1, n,  k-1, vec_tmp,vec_vecBintB1);
        }

        return vec_vecBintB1;

    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
   // vector<int> intvec1 ={-1,0,3,5,9,12};


    //int mytarget = 5;

    int indx_rs1 = -1;

    int n =4;
    int k = 2;
    vector<vector<int>> rs1 = solut1->combine(n,k);
    cout<<"position index:"<<indx_rs1<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size());

    return 0;
}


