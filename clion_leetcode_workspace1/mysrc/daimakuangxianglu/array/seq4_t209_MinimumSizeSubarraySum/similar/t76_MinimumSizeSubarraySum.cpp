#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given two strings s and t of lengths m and n respectively,
 * return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string ""
 *
 * Example:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 *
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_VectorBintB(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    void myOutput_string(string str1, int st_indx, int ed_indx){
        int len = ed_indx - st_indx +1;
        string str_rs1(str1.substr(st_indx,len));
        cout<<str_rs1<<endl;
    }

/*    void myOutput_string(vector<string>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }*/

    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    // og = "CEBGCBAECADBCACGGE"
    // target = "ABCC"
    // 我这个自创的肯定最小的就是那个BCAC
    string minWindow(string og, string target){
        unordered_map<char,int> target_freq;
        unordered_map<char,int> og_window_freq;

        //og 的指针 从而建立window
        int st_indx = 0;
        int ed_indx = 0;

        int rs_st_indx=-1;
        int rs_ed_indx=-1;
        int rs_min_len=INT32_MAX;        //包括有效字符的最小串的长度

        //window中存在的有效数字
        //例如 target中
        //    A=1 B=1 C=2
        //    但是window中
        //    A=1 B=2 C=2 eff_len仍然是3, B多余的那个我不算在内
        int eff_total_len = 0;

        for(int i=0;i<=target.size()-1;i++){
            ++target_freq[target[i]];
        }


        for(;ed_indx<=og.size()-1;ed_indx++){
            char ch_tmp= og[ed_indx];
            //
            // 为了能够缩小 og_window_freq的空间, 但是会可能消耗一些时间 去find
            // 如果当前增加的字符 是有效字符
            if(target_freq.find(ch_tmp)!=target_freq.end()){
                ++og_window_freq[ch_tmp];   //存储window出现的 有效字母 和 其出现次数

                // 如果此时该字符(已经增加本次)已经出现的数度 已经 达到了 或者 超过了 规定的次数
                if(og_window_freq[ch_tmp] > target_freq[ch_tmp]){
                    //则不增加本次的出现次数 到 总次数中
                    //do nothing
                }
                // 如果此时该字符(已经增加本次)已经出现的数度 没有 达到了 和 超过了 规定的次数
                else{
                    ++eff_total_len;    //增加本次出现的次数 到 window中有效字符 出现的 总次数中
                    //
                    // 每当 总次数 增加, 去判断是否 达标
                    // 例如og 搜索到 ABBC  target要求是BAC
                    // 那么 eff_total_len = 3 达标
                    if(eff_total_len==target.size()){

                        //达标的话 先看是不是 比之前的总长度更小,
                        //如果是的话则记录下来
                        if(ed_indx-st_indx+1 < rs_min_len){
                            rs_min_len = ed_indx-st_indx+1;
                            rs_st_indx = st_indx;
                            rs_ed_indx = ed_indx;
                        }



                        //然后准备进行删除
                        for(;st_indx<=ed_indx;){
                            //分析头部的第一位, 从而准备删除这一位
                            char ch_tmp2=og[st_indx];
                            ++st_indx;

                            //如果删除的当前字符 是有效字符
                            if(target_freq.find(ch_tmp2)!=target_freq.end()){

                                //删除该字符出现的次数
                                --og_window_freq[ch_tmp2];

                                // 如果删除 该字符以后 他的有效次数不达标
                                if(og_window_freq[ch_tmp2] < target_freq[ch_tmp2]){
                                    // 意味着 删除 该字符以后 影响到总有效次数了 例如:BA 删除了有效的字符B了
                                    --eff_total_len; //总有效次数也减
                                    // 停止继续缩减, 而是要增加ed_indx从而进行下一步
                                    break;
                                }
                                // 如果删除 该字符以后 他的有效次数仍然达标
                                else{
                                    // 到后面查看是否删除后 有效是否达标
                                    // do nothing
                                }

                            }
                            //如果删除的当前字符 不是有效字符
                            else{
                                // 到后面查看是否删除后 有效是否达标
                                // do nothing
                            }

                            // 查看是否删除后 有效是否达标
                            if(eff_total_len==target.size()){
                                //发现
                                //删除从而缩小后 仍然达标的话 先看是不是 比之前的总长度更小,
                                //如果是的话则记录下来
                                if(ed_indx-st_indx+1 < rs_min_len){
                                    rs_min_len = ed_indx-st_indx+1; //从删除了的这一个字符的下一个位置开始算长度
                                    rs_st_indx = st_indx;       //记录当前想要删除的位置的下一个位置
                                    rs_ed_indx = ed_indx;
                                }
                                // 然后继续下一轮循环 从而st_index++缩小范围
                            }
                        }

                    }
                }
            }
            // 如果不是有效字符
            else{
                // do nothing 从而移动ed_indx
            }



        }



        if(rs_min_len==INT32_MAX){
            return "";
        }
        else{
            return og.substr(rs_st_indx,rs_min_len);
        }
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();



    //string str_og("bba");
    //string target("ab");

    string str_og("ADOBECODEBANC");
    string target("ABC");

    //string str_og("CEBGCBAECADBCACGGE"); //我自己的
    //string target("ABCC");


    string result= solut1->minWindow(str_og,target);
    cout<<"result"<<result<<endl;

    /*for(int i=0;i<=intvec_result.size()-1;i++){
        cout<<intvec_result[i]<<"\t";
        if(i==intvec_result.size()-1){
            cout<<endl;
        }
    }*/



    return 0;
}


