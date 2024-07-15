#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given an input string s, reverse the order of the words.
 * A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
 * Return a string of the words in reverse order concatenated by a single space.
 * Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

 * Example1:
 * Input: s = "the sky is blue"
 * Output: "blue is sky the"
 *
 * Example2:
 * Input: s = "  hello world  "
 * Output: "world hello"
 *
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_string(string str1, int st_indx, int ed_indx){
        int len = ed_indx - st_indx +1;
        string str_rs1(str1.substr(st_indx,len));
        cout<<str_rs1<<endl;
    }

    void removeExtraSpaces(string& s) {
        char tmp;
        int cur_slow=0;
        int cur_fast=0;
        for(; cur_fast<=s.size()-1;){

            //去头
            if(cur_fast==0 && s[cur_fast]==' '){
                cur_slow=0;
                ++cur_fast;
            }
            else if(cur_fast>0 && s[cur_fast]==' ' && s[cur_fast]==s[cur_fast-1]){
                ++cur_fast;
            }
            //
            //处理字符
            //    |fast
            // "  blue sky"
            //  |slow
            // "b"
            else if(s[cur_fast]!=' '){
                s[cur_slow]=s[cur_fast];
                ++cur_slow;
                ++cur_fast;
            }
            //
            // 单词后的空格
            //     | fast -1
            //      | fast
            // "blue  sky"
            //
            else if(cur_fast>0 && s[cur_fast]==' ' && s[cur_fast-1]!=' ') {
                s[cur_slow]=s[cur_fast];
                ++cur_slow;
                ++cur_fast;
            }
            //
        }


        //for 循环结束后 处理尾巴
        //如果尾巴是空格,则删掉 并且resize
        //            |slow
        //           |slow-1
        // "blue  sky "
        if(cur_slow>0 && s[cur_slow-1]==' '){
            s.resize(cur_slow-1-1+1);
        }
        //如果尾巴不是空格,则直接resize
        else if(cur_slow>0 && s[cur_slow-1]!=' '){
            // 用的是cur_slow
            // 因为填入之后 它跑到下一位的未存放内容等待了,
            // 此时只有实际的内容的末尾index是cur_slow-1
            s.resize(cur_slow-1+1);
        }

    }

    void reverse_str(string& s, int indx_st, int indx_ed) {
        char ch_tmp;
        int i=indx_st;
        int j=indx_ed;
        for(;i<=j;i++,j--){
            ch_tmp=s[i];
            s[i]=s[j];
            s[j]=ch_tmp;
        }
    }

    //时间复杂度: O(n)
    //空间复杂度: O(1) 或 O(n)，取决于语言中字符串是否可变
    string reverseWords(string s) {
        removeExtraSpaces(s);

        char ch_tmp;
        //
        // "sky is blue"
        // "eulb si yks"
        reverse_str(s,0,s.size()-1);//
        // "blue is sky"
        int word_st=0;
        int word_ed=0;
        for(int i=0;i<=s.size()-1;i++){
            //      |i
            //  |st
            // "blue si yks"
            if(s[i]==' '){
                reverse_str(s, word_st, i-1);
                //      |i
                //       |st
                // "blue si yks"
                word_st = i+1;
            }
            else if(i==s.size()-1){
                reverse_str(s, word_st, i);
            }
        }
        return s;
    }


};

/**
 * feature:
 *
 *
 * 思路():
 *
 *
 *
 * */
int main() {
    Solution* solut1 = new Solution();


    //string str1 = "blue  ";     //测试结尾
    string str1 = "  sky is   blue  ";

    string rs_str1 =solut1->reverseWords(str1);

    cout<<"result"<<endl;
    solut1->myOutput_string(rs_str1,0,rs_str1.size()-1);
    cout<<"length:"<<rs_str1.size()<<endl;





    return 0;
}


