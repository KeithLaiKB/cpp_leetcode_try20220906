#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <cstdint>
using namespace std;

/**
 *
 *You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.
 *Evaluate the expression. Return an integer that represents the value of the expression.

 *Note that:
 * The valid operators are '+', '-', '*', and '/'.
 * Each operand may be an integer or another expression.
 * The division between two integers always truncates toward zero.
 * There will not be any division by zero.
 * The input represents a valid arithmetic expression in a reverse polish notation.
 * The answer and all the intermediate calculations can be represented in a 32-bit integer.
 *
 * Example1:
 * Input: tokens = ["2","1","+","3","*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9
 *
 * Example2:
 * Input: tokens = ["4","13","5","/","+"]
 * output: 6
 * Explanation: (4 + (13 / 5)) = 6
 *
 * Example3:
 * Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
 * Output: 22
 * Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22
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

    //时间复杂度: O(n)
    //空间复杂度: O(n)
    int evalRPN(vector<string>& tokens) {
        stack<long long> st1;
        string str_now="";
        int rs1= 0;
        long long rs1_tmp= 0;
        for(int i=0;i<=tokens.size()-1;i++){
            string str_now = tokens[i];

            // 6,2,1,*,/ ->6/(2*1)
            if(str_now=="+" || str_now=="-" || str_now=="*" ||str_now=="/"){
                if(st1.size()<2){
                    return INT32_MAX;
                }
                int num2_tmp = st1.top();
                st1.pop();

                int num1_tmp = st1.top();
                st1.pop();


                if(str_now =="+"){
                    rs1_tmp = num1_tmp + num2_tmp;
                }
                else if(str_now =="-"){
                    rs1_tmp = num1_tmp - num2_tmp;
                }
                else if(str_now =="*"){
                    rs1_tmp = 1LL * num1_tmp * num2_tmp;
                }
                else if(str_now =="/"){
                    if(num2_tmp == 0){
                        return INT32_MAX;
                    }
                    rs1_tmp = num1_tmp / num2_tmp;
                }
                st1.push(rs1_tmp);
                // divisor could not be zero
            }
            else{
                st1.push(stoll(str_now));
            }
        }

        rs1 = static_cast<int>(st1.top());
        st1.pop();
        return rs1;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    vector<string> str_vec1={"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    str_vec1.reserve(100);
    //string str1_og="azxxzy";




    int rs1 = solut1->evalRPN(str_vec1);
    cout<<"result"<<endl;
    cout<<rs1<<endl;





    return 0;
}


