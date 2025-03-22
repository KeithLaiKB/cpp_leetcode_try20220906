#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given a string containing digits from 2-9 inclusive,
 *
 * return all possible letter combinations that the number could represent. Return the answer in any order.
 * A mapping of digits to letters (just like on the telephone buttons) is given below.
 * Note that 1 does not map to any letters.
 *
 *
 * Example1:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example2:
 * Input: digits = ""
 * Output: []
 *
 *
 * Example3:
 * Input: digits = "2"
 * Output: ["a","b","c"]
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
    vector<string> pad1={"",         //0
                         "",         //1
                         "abc",      //2
                         "def",      //3
                         "ghi",      //4
                         "jkl",      //5
                         "mno",      //6
                         "pqrs",     //7
                         "tuv",      //8
                         "wxyz"      //9
    };


    //
    // 假设输入"23"
    //
    //                                                                                         digits[2]==> 集合{"def"}
    //                                      |                                                       |                                                       |
    //                                      |取d                                                    |取e                                                     |取f
    //   第一层的结果:                        "d"                                                    "e"                                                      "f"
    //                      |               |               |                       |               |               |                       |               |               |
    //                      |(取g)           |(取h)          |(取i)                  |(取g)           |(取h)          |(取i)                  |(取g)           |(取h)          |(取i)
    //   第二层的结果:       "dg"             "dh"            "di"                   "eg"            "eh"            "ei"                     "fg"            "fh"            "fi"
    //
    //
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
    // 时间复杂度：O(3^m * 4^n)，
    //      其中 m 是对应三个字母的数字个数，n 是对应四个字母的数字个数
    // 空间复杂度：O(3^m * 4^n)
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


