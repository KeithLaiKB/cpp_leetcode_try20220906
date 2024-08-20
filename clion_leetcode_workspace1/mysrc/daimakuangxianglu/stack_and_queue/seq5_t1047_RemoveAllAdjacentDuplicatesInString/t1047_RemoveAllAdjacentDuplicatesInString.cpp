#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;

/**
 *
 * You are given a string s consisting of lowercase English letters. A duplicate removal consists of choosing two adjacent and equal letters and removing them.
 * We repeatedly make duplicate removals on s until we no longer can.
 * Return the final string after all such duplicate removals have been made. It can be proven that the answer is unique.
 *
 * Example1:
 * Input: s = "abbaca"
 * Output: "ca"
 * Explanation:
 * For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal,
 * and this is the only possible move.  The result of this move is that the string is "aaca",
 * of which only "aa" is possible, so the final string is "ca".
 *
 * Example2:
 * Input: s = "azxxzy"
 * Output: "ay"
 *
 * 题目中说字符串只会包含括号 但我想扩展 所以 允许其他字符在里面
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    //时间复杂度: O(n+m)
    //空间复杂度: O(m)
    string removeDuplicates(string str1) {
        stack<char> st1;
        for(int i=0;i<=str1.length()-1;i++){
            char ch_now=str1[i];
            // 如果不是空 并且等于刚加进去的 也就是判定他们是相邻的
            if(st1.empty()==false && ch_now==st1.top()){
                //所以就弹出
                st1.pop();
            }
            else{
                st1.push(ch_now);
            }
        }
        string rs1="";
        for(int i=0;st1.empty()==false;i++){
            rs1= rs1 + (char)st1.top();
            st1.pop();
            cout<<st1.size()<<endl;
        }
        reverse(rs1.begin(),rs1.end());
        return rs1;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    string str1_og="abbaca";
    //string str1_og="azxxzy";




    string rs1 = solut1->removeDuplicates(str1_og);
    cout<<"result"<<endl;
    cout<<rs1<<endl;





    return 0;
}


