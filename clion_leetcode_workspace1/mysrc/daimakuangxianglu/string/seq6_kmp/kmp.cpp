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


    // 这种偏向暴力求Next
    void getNext2(string &str, int* next){
        int surf_ed =1;
        int pref_ed=0;

        // 因为str[0]这个串 也就是str[1]的子串 是没有办法有真前缀和真后缀的
        next[0]=0;
        for(; surf_ed<=str.size()-1; ){
            if(str[pref_ed]==str[surf_ed]){
                ++pref_ed;
                ++surf_ed;
                next[pref_ed]=next[pref_ed-1]+1;
            }
            else{
                pref_ed=0;
                next[surf_ed]=0;
                ++surf_ed;
            }
        }

    }

    //next数组的长度 是和当前这个str的长度一样的
    // 这种做法是都不减一, 使得他们存储的内容是字串的长度
    void getNext_mytryog_NO_minus1(string str, int* next){
        int surf_ed =1;
        int pref_ed=0;

        // 因为str[0]这个串 也就是str[1]的子串 是没有办法有真前缀和真后缀的
        next[0]=0;
        for(;surf_ed<=str.size()-1;){
            //匹配相同 记录当前pref_ed在案 增加
            if(str[pref_ed]==str[surf_ed]){
                next[surf_ed]=pref_ed+1;      //记录pre字符串长度
                cout<<"\t"<<next[surf_ed];
                //都往后移动
                ++pref_ed;
                ++surf_ed;

            }
            //匹配不同 后缩pref_ed
            else if(str[pref_ed]!=str[surf_ed]){
                // 如果 pref_ed=0 那就可以结束了, 因为没有继续的必要 因为next[0]=0
                for(;pref_ed>=1 && str[pref_ed]!=str[surf_ed];){
                    pref_ed=next[pref_ed-1];
                }

                // 相等
                if(str[pref_ed]==str[surf_ed]){
                    //
                    next[surf_ed]=pref_ed+1;      //记录pre字符串长度
                    cout<<"\t"<<next[surf_ed];
                    //都往后移动
                    ++pref_ed;
                    ++surf_ed;
                }
                // 不相等
                else if(str[pref_ed]!=str[surf_ed]){
                    //记录pre字符串的 前缀子串 的长度, 其实我觉得这里换成next[surf_ed]=0都合理, 而且 next[surf_ed]=0 也跑过了leetcode的测试
                    // 因为 如果这个时候都不相等, 此时 pref_ed 已经等于0了
                    next[surf_ed]=pref_ed;
                    //next[surf_ed]=0;
                    cout<<"\t"<<next[surf_ed];
                    //不移动pref
                    //++pref_ed;
                    ++surf_ed;
                }

            }

        }

    }

    //next数组的长度 是和当前这个str的长度一样的
    void getNext_mytryog_allminus1(string &str, int* next){
        int surf_ed = 1;
        int pref_ed =-1;            //pre字符串的最后一位前一位的index, 整个搜查匹配都是pref_ed+1来匹配, -1使得跳转可读性更好(跳的是index 而不是需要长度-1)

        // 因为str[0]这个串 也就是str[1]的子串 是没有办法有真前缀和真后缀的
        next[0]=-1;
        for(;surf_ed<=str.size()-1;){
            //匹配相同 记录当前pref_ed在案 增加
            if(str[pref_ed+1]==str[surf_ed]){       // pref_ed 当前pre字符串 最后一个的字符的 前一个字符的index, 所以需要 pref_ed+1
                next[surf_ed]=pref_ed+1;            // 记录下 当前pre字符串 最后一个的字符 的 index 而不是长度, 所以需要 pref_ed+1, 虽然 和 不统一减一的 句子相同, 但意义不同, 这里的是index
                cout<<"\t"<<next[surf_ed];
                //都往后移动
                ++pref_ed;
                ++surf_ed;

            }
                //匹配不同 后缩pref_ed
            else if(str[pref_ed+1]!=str[surf_ed]){
                // 如果 pref_ed=-1 那就可以结束了, 因为没有继续的必要 因为next[0]=-1
                for(;pref_ed>=0 && str[pref_ed+1]!=str[surf_ed];){
                    pref_ed=next[pref_ed];      // 因为Next数组 记录的是index, 直接跳转到index就可以了
                }

                // 相等
                if(str[pref_ed+1]==str[surf_ed]){
                    //
                    next[surf_ed]=pref_ed+1;      // 记录下 当前pre字符串 最后一个的字符 的 index 而不是长度, 所以需要 pref_ed+1, 虽然 和 不统一减一的 句子相同, 但意义不同, 这里的是index
                    cout<<"\t"<<next[surf_ed];
                    //都往后移动
                    ++pref_ed;
                    ++surf_ed;
                }
                // 不相等
                else if(str[pref_ed+1]!=str[surf_ed]){
                    //记录下 当前pre的 前缀子串 最后一个的字符 的 index 而不是长度, 其实我觉得这里换成next[surf_ed]=-1都合理, 而且 next[surf_ed]=0 也跑过了leetcode的测试
                    // 因为 如果这个时候都不相等, 此时 pref_ed 已经等于-1了
                    next[surf_ed]=pref_ed;
                    //next[surf_ed]=0;
                    cout<<"\t"<<next[surf_ed];
                    //不移动pref
                    //++pref_ed;
                    ++surf_ed;
                }

            }

        }




    }

    //时间复杂度: O(n+m)
    //空间复杂度: O(m)
    int kmp_NO_minus1(string str1, string sub1) {
        string str_result;

        //求next数组
        vector<int> next(sub1.size());
        getNext_mytryog_NO_minus1(sub1,next.data());
        //
        //匹配开始
        int j =0;
        for(int i=0;i<=str1.size()-1;){
            if(str1[i]==sub1[j]){
                ++j;
                ++i;
                //cout<<str1[i]<<endl;
            }
            else if(str1[i]!=sub1[j]){
                for(;j>=1 && str1[i]!=sub1[j];){
                    j = next[j-1];              // 这就是不统一减一带来的 不同, 因为他记录的是长度 所以变成下标 需要减一, 所以上面for 要 j>=1
                }
                //如果匹配成功 则sub往后走一位
                if(str1[i]==sub1[j]){
                    ++j;
                    ++i;
                }
                //如果匹配不成功 则sub此时也应当是在0的位置了
                else if(str1[i]!=sub1[j]){
                    ++i;
                }
            }


            // t28的判定 返回完全匹配sub1成功时 的起始点
            if(j==sub1.size()){
                // 现在i 是在匹配后有++ 所以此时i就已经代表长度了
                //          起始位置   =i的长度 - 子串长度
                // 如果有疑惑 你一定要用纸写下来 你肯定就清楚了
                // 0 1 2 3 4 5 6 7 8 9  _
                // 1 2 3 4 5 6 7 8 9 10
                int sub1_st_in_str1 = i-sub1.size();
                cout<<endl;
                cout<<i<<endl;
                cout<<sub1_st_in_str1<<endl;
                return sub1_st_in_str1;
            }
        }

        return -1;
    }

    //时间复杂度: O(n+m)
    //空间复杂度: O(m)
    int kmp_minus1(string str1, string sub1) {
        string str_result;

        //求next数组
        vector<int> next(sub1.size());
        getNext_mytryog_allminus1(sub1,next.data());
        //cout<<next.data()<<endl;
        //
        //匹配开始
        int j = -1;                                 // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index
        for(int i=0;i<=str1.size()-1;){
            if(str1[i]==sub1[j+1]){                 // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index, 所以 当前准备匹配的字符的index=j+1
                ++j;
                ++i;
                //cout<<str1[i]<<endl;
            }
            else if(str1[i]!=sub1[j+1]){                // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index, 所以 当前准备匹配的字符的index=j+1
                for(;j>=0 && str1[i]!=sub1[j+1];){      // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index, 所以 当前准备匹配的字符的index=j+1, 并且j是-1开始所以>=0
                    j = next[j];                        // 这就是统一减一带来的 不同, 因为他记录的已经是下标了, 直接跳转到该index上就可以了, 不需要 j+1
                }
                //如果匹配成功 则sub往后走一位
                if(str1[i]==sub1[j+1]){                 // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index, 所以 当前准备匹配的字符的index=j+1
                    ++j;
                    ++i;
                }
                //如果匹配不成功 则sub此时也应当是在0的位置了
                else if(str1[i]!=sub1[j+1]){            // 这就是统一减一带来的 不同, 因为他是 当前准备匹配的字符 的子串中 最后一个字符的index, 所以 当前准备匹配的字符的index=j+1
                    ++i;
                }
            }


            // t28的判定 返回完全匹配sub1成功时 的起始点
            // 这就是统一减一带来的 不同,
            // j原本是 当前准备匹配的字符 的子串中 最后一个字符的index, 但是 现在j 是在匹配后有++
            // 所以此时j就已经代表 当前准备匹配的字符 的 index了, 要和长度相等的话 还需要 j+1
            if(j+1==sub1.size()){
                // 现在i 是在匹配后有++ 所以此时i就已经代表长度了
                //          起始位置   =i的长度 - 子串长度
                // 如果有疑惑 你一定要用纸写下来 你肯定就清楚了
                // 0 1 2 3 4 5 6 7 8 9  _
                // 1 2 3 4 5 6 7 8 9 10
                int sub1_st_in_str1 = i-sub1.size();
                cout<<endl;
                cout<<i<<endl;
                cout<<sub1_st_in_str1<<endl;
                return sub1_st_in_str1;
            }
        }

        return -1;
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
    string str1 = "BABABBABAB";
    string str2 = "BABBABAB";

    //int rs_str1_indx =solut1->kmp_NO_minus1(str1,str2);
    int rs_str1_indx =solut1->kmp_minus1(str1,str2);
    cout<<"result"<<endl;
    solut1->myOutput_string(str1,rs_str1_indx,rs_str1_indx+str2.size());
    //cout<<"length:"<<rs_str1.size()<<endl;





    return 0;
}


