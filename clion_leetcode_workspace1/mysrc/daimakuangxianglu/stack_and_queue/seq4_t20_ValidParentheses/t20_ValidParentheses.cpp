#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;

/**
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
 *
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 *
 * Example1:
 * Input: s = "()"
 * Output: true
 *
 * Example2:
 * Input: s = "()[]{}"
 * Output: true
 *
 * Example3:
 * Input: s = "(]"
 * Output: false
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
    bool isValid(string str1) {
        stack<char> st1;
        bool bl_result=false;
        for(int i=0;i<=str1.length();i++){
            char ch_now=str1[i];
            //push
            if(ch_now =='['){
                st1.push(']');
            }
            else if(ch_now =='{'){
                st1.push('}');
            }
            else if(ch_now =='('){
                st1.push(')');
            }
            //pop
            else{
                if(ch_now!=']' && ch_now!='}' && ch_now!=')'){
                    // do nothing
                }
                else if(ch_now==']' || ch_now!='}' || ch_now!=')'){
                    // str1里有 "{}]" 但stack里 本应当有']' 和 '}'
                    // 但此时只有'}' 弹掉'}' 就没有']'去匹配了了
                    if(st1.empty()==true){
                        return false;
                    }

                    char ch_tmp1=st1.top();
                    if(ch_now!=ch_tmp1){
                        return false;
                    }
                    else{
                        st1.pop();
                    }
                }
            }
        }
        if(st1.empty()){
            bl_result = true;
        }
        else{
            bl_result = false;
        }
        return bl_result;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    string str1_og="[{12(3)}]";




    bool rs1 = solut1->isValid(str1_og);
    cout<<"result"<<endl;
    cout<<rs1<<endl;





    return 0;
}


