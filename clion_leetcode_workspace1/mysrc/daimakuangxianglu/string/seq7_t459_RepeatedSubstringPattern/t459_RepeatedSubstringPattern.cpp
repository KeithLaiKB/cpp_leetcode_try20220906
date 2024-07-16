#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.


 * Example1:
 * Input: s = "abab“
 * Output: true
 * Explanation: It is the substring "ab" twice.
 *
 * Example2:
 * Input: s = "aba"
 * Output: false
 *
 * Example2:
 * Input: s = "abcabcabcabc"
 * Output: true
 * Explanation: It is the substring "abc" four times or the substring "abcabc" twice.
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

    void myOutput_string(string str1, int st_indx, int ed_indx){
        int len = ed_indx - st_indx +1;
        string str_rs1(str1.substr(st_indx,len));
        cout<<str_rs1<<endl;
    }
    void myOutput_VectorBintB(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }
    /**
     * 这里面的 和kmp里面的是一模一样的 只是我这边该了变量名
     * 因为我觉得 pfed_prev 这个名字 会比 以前的 更加清楚
     * 因为 pfed_prev +1 = pfed;
     *
     * sfed         就代表以前的surf_ed
     * pfed_prev +1 就代表以前的pref_ed, 但是以前这么起名 有一些歧义的, 但因为官方是这么玩, 我之前就这么起名, 但我先在更喜欢我这种起名字
     * 因为pfed_prev 就代表的是 pre字符串的最后一位的前一位的index
     *
     *
     *
     *
     * @param str
     * @param next
     */
    void getNext_allminus1(string &str, int* next){
        int sfed=1;
        int pfed_prev=-1;       // pfed_prev +1 = pfed;
        next[0]=-1;
        for (; sfed<=str.size()-1 ; ) {
            // 相同 记录 并大家后移
            if(str[pfed_prev+1]==str[sfed]){
                next[sfed]=pfed_prev+1;            //记录当前pfed的位置 pfed=pfed_prev+1
                ++pfed_prev;
                ++sfed;

            }
            else {
                // 不相同 pfed_prev往前跳
                for(;pfed_prev>=0 && str[pfed_prev+1]!=str[sfed];){
                    pfed_prev = next[pfed_prev];
                }

                // 继续判断
                // 相同 则记录并后移
                if(str[pfed_prev+1]==str[sfed]){
                    next[sfed]=pfed_prev+1;    //记录当前pfed的位置 pfed=pfed_prev+1
                    ++pfed_prev;
                    ++sfed;
                }
                // 不相同 就只是 surf往后跳
                else {
                    //记录下 当前pre的 前缀子串 最后一个的字符 的 index 而不是长度, 其实我觉得这里换成next[surf_ed]=-1都合理, 而且 next[surf_ed]=-1 也跑过了leetcode的测试
                    // 因为 如果这个时候都不相等, 此时 pref_ed 已经等于-1了
                    next[sfed]=pfed_prev;
                    ++sfed;
                }
            }
        }
    }


    //时间复杂度: O(n+m)
    //空间复杂度: O(m)
    //
    // 用统一减一的方式
    // 0    1   2   3   4   5   6   7   8   9   10  11
    // a    s   d   f   a   s   d   f   a   s   d   f
    //-1   -1   -1  -1  0   1   2   3   4   5   6   7
    // 最长相同前后缀 asdfasdf 长度为 8
    // 假设 这个str是重复字符 那么 str[0]~str[3] 就是原始周期
    // 总长度 - 最长相同前后缀长度 = str[0]~str[3] 的长度 = 假定这个str是重复字符 的这个周期的长度= 4
    //
    // 为了验证 他是重复字符 那么要证:
    // 总长度 % 假定这个str是重复字符 的这个周期的长度 == 0
    // 总长度 % (总长度 - 最长相同前后缀长度)        == 0
    // 12    % (12-     (next[11]+1))          = 12 % (12-8) = 12 % 4 ==0
    // 因此成立
    // 也就是
    // s.size() % (s.size()- (next[s.size()-1]+1) ) ==0
    //
    // 当然了 "abac" 也是不可以的
    // 尽管 他对上面的公式是成立的 4 % (4-(-1)+1)==0
    // 所以我们还要加上一个条件 就是 next[最后一个下标] != -1
    // 也就是 next[s.size() - 1] != -1
    //
    bool repeatedSubstringPattern(string s) {
        vector<int> next(s.size());
        getNext_allminus1(s, next.data());


        //bool result =false;
        bool result = ( next[s.size() - 1] != -1 && s.size() % (s.size()- (next[s.size()-1]+1) ) ==0 ) ? true: false;
        myOutput_VectorBintB(next,0,next.size()-1);
        return result;
    }
};
/**
 * feature:
 *
 *
 * 思路():
 *
 * 这个文件 想要测试你的next数组 合不合理
 *      直接 使用 leetcode28的 答案 直接 替换掉 它求Next数组的方法 就知道可不可以了
 *
 * */
int main() {
    Solution* solut1 = new Solution();


    //string str1 = "blue  ";     //测试结尾
    //string str1 = "AAEAAGAAEAACAAEAAGAAEAAD";
    //string str2 = "AAEAAGAAEAAD";
    string str1 = "abcabcabcabc";

    //int rs_str1_indx =solut1->kmp_NO_minus1(str1,str2);
    bool rs_str1_indx =solut1->repeatedSubstringPattern(str1);
    cout<<"result"<<endl;
    cout<<rs_str1_indx<<endl;
    //solut1->myOutput_string(str1,rs_str1_indx,rs_str1_indx+str2.size());
    //cout<<"length:"<<rs_str1.size()<<endl;





    return 0;
}


