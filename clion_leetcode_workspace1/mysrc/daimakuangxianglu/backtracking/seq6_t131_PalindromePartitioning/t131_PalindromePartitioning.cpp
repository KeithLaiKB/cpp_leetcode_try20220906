#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <algorithm>

using namespace std;

/**
 *
 * Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
 *
 *
 * Example1:
 * Input: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 *
 * Example2:
 * Input: s = "a"
 * Output: [["a"]
 *
 *
 * substring 它提到了 substring 那么字符就是连续的
 * 他这个是要做s的切片, 并不是仅仅从里面抽出来
 *
 * [abbc]
 * 打个比方,
 * 比如说t647
 * {a,b,b,c,bb} 里面的每一个元素都是回文, 结果是一共五个
 *
 * 但是当前这题是 从 abbc 切割成若干份, 每一份都是回文, 然后把所有情况都列出来
 * 情况一
 * {{a,b,b,c},{a,bb,c}}
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

    bool judgePalindrome(const string& str1){
        int st_idx=0;
        int ed_idx=str1.size()-1;
        for(;st_idx<=ed_idx;st_idx++,ed_idx--){
            if(str1[st_idx]!=str1[ed_idx]){
                return false;
            }
        }
        return true;
    }

    //
    //                                                                                                                                  [a,b,b,c]
    //                                                    |                                                                                 |                                   |                             |
    //                                                   [a] 下面去分片[b,b,c]                                                       [a,b] 下面去分片[b,c]              [a,b,b] 下面去分片[c]           [a,b,b,c]
    //                     |                              |                     |                   |                               |              |                  |
    //                    [b] 下面去分片[b,c]            [b,b] 下面去分片[c]    [b,b,c]                [b] 下面去分片[c]                [b]             [b,c]              [c]
    //         |                      |               |                                         |                               |
    //        [b] 下面去分片[c]        [bc]            [c]                                       [c]                             [c]
    //      |
    //     [c]
    //
    //
    bool backtracking(string s, int now_idx,vector<string> &now_content, vector<vector<string>> &rs){
        //limit
        // 因为如果上一层不是回文, 是不会走到这里的
        if(now_idx==s.size()){
            rs.push_back(now_content);
            return true;
        }




        //deal
        bool now_palindrom=false;

        // abba
        // a -> ab ->abb ->abba, 他是逐渐一个个字符加进去的, 而不是换字符
        string str_tmp = "";

        //for
        for(int i =now_idx;i<=s.size()-1;i++){

            // abba
            // a -> ab ->abb ->abba
            str_tmp.push_back(s[i]);
            now_palindrom = judgePalindrome(str_tmp);

            // 当前节点不是回文 不代表兄弟节点不是, 所以这里不能用break
            if(now_palindrom == false){
                continue;
            }

            now_content.push_back(str_tmp);


            //backtracking
            //看后面
            backtracking(s, i+1, now_content,  rs);


            //pop
            // 因为要看兄弟节点, 所以要把当前的pop掉
            now_content.pop_back();
        }

        return false;
    }
    //
    // 时间复杂度: O(n*2^n)
    //      n代表的是每次回文的判断
    //      假设一共有N个数字, 那么就有n-1个缝隙,
    //              每个缝隙可以选择切或者不切 从而形成组合
    //      也就是一共有2^(n-1) 的组合
    //      所以总共是 O(n*2^n)
    //
    // 空间复杂度: O(n)
    //      因为最高深度n层
    vector<vector<string>> partition(string s) {
        vector<vector<string>> rs1={};
        vector<string> now_content = {};
        backtracking(s, 0, now_content,  rs1);

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    //vector<int> intvec1 ={10,1,2,7,6,1,5};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    string str1 ="aab";
    vector<vector<string>> rs1 = solut1->partition(str1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBVectorBintBB(rs1,0,rs1.size()-1);
    return 0;
}


