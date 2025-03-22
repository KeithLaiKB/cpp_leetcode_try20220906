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

    vector<string> backtracking(vector<int> digits, int st_idx, string &now_content, vector<string>& vec_rs){
            //limit
            // 这题目很好的告诉了你 不是动不动就size-1的
            if(st_idx==digits.size()){
                vec_rs.push_back(now_content);
                return {};
            }

            //deal
            // 如 key=3 中里 有"def"
            string letter = pad1[digits[st_idx]];

            //for
            // for最底层的对象, 所以不是for 那个digits  例如“23”
            // 而是 for 那个pad 中的每个key里的content, 例如"abc" "def" 那些
            for(int i =0;i<=letter.size()-1;i++){
                //"a"->"ab"
                now_content.push_back(letter[i]);

                //backtracking
                backtracking(digits,st_idx+1,now_content,vec_rs);

                //pop
                // 例如 我们的"23"例子中,
                // 假设 当前的情况是 我们经过了d 现在深入到当前这个key_content[i]=g
                // 在上面的backtracking当中 我们已经把 “dg” 放进了rs
                // 此时我们要把 “dg”中的 "g"弹出, 准备装 下一个key_content[i+1]=h, 从而获得 "dh"
                now_content.pop_back();

            }

            return {};
    }

    vector<string> letterCombinations(string digits) {
        vector<string> rs1={};
        vector<int> vec_digits={};
        string content="";

        if(digits==""){
            return {};
        }

        for(char ch_tmp: digits){
            vec_digits.push_back(ch_tmp-'0');
        }

        backtracking(vec_digits,0,content,rs1);

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
   // vector<int> intvec1 ={-1,0,3,5,9,12};


    //int mytarget = 5;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;

    vector<string> rs1 = solut1->letterCombinations("23");
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    return 0;
}


