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
        int st_indx = 0;
        int ed_indx = 0;


        int rs_st_indx=-1;
        int rs_ed_indx=-1;
        int rs_min_length=INT32_MAX;        //包括有效字符的最小串的长度

        //需要被包含的串 的每个字符 以及出现的次数, 因为这个子串 有可能是"ABCCC", 那么包含它的大串 C 也要出现三次
        unordered_map<char,int> target_freq;
        unordered_map<char,int> og_window_freq;

        int window_effect_len=0;        //只包含有效字母
        int window_total_len=0;         //总长度



        //建立
        // A B C
        // 1 1 2
        for(int i = 0;i<=target.size()-1;i++){
            target_freq[target[i]]++;       //不用我们专门生成对应的key 和value之后 再自增, c++发现如果不存在可以直接自己生成操作
        }

        //如果大数组的长度 还没有 要涵括的子数组长,
        //那么就不用匹配了, 因为根本匹配不了
        if(og.size()<target.size()){
            return "";
        }



        for(;ed_indx<= og.size()-1;ed_indx++){
            char c_tmp=og[ed_indx];
            //在target_freq中的 ABC找不到对应元素
            if(target_freq.find(c_tmp)==target_freq.end()){
                //则不管他
            }
            //找到
            else{
                og_window_freq[c_tmp]++;
                window_effect_len++;
                //如果插入的 多过了要求的 例如 BGCB 缩减-> 变成GCB ->CB
                //注意超过1位都不行
                //{C E B G C B}
                //{C E B G C B}     遇见第一个B前, 有效字符 或者是 非有效字符 全都删掉 例如这里的 C和E
                //{  E B G C B}
                //{    B G C B}     删掉B
                //{      G C B}     删掉B以后, 遇到非有效字符, 删除
                //{        C B}     删掉B以后, 遇到的有效字符, 不删除, 并且停止, 然后进行下一步
                //{        C B A}
                int del_flag = 0;   //用来判断是否已经删除第一个B
                //
                //
                // 发现多余的B, 并且没有删除
                if(og_window_freq[c_tmp]>target_freq[c_tmp]){
                    // test output
                    myOutput_string(og,st_indx,ed_indx);
                    for(;st_indx<=ed_indx;){
                        //如果当前 准备删除的字符 就是 当前准备加入的多的那个字符
                        // BGCB 缩减-> 变成GCB
                        if(og[st_indx]==c_tmp){
                            //进行删除
                            og_window_freq[c_tmp]--;    //当前的window的freq-- 就是把刚才加上的删掉
                            window_effect_len--;        //有效长度-- 就是把刚才加上的删掉
                            st_indx++;
                            del_flag = 1;
                        }

                        //如果当前 准备删除的字符 不是 当前准备加入的多的那个字符
                        else{
                            if(target_freq.find(og[st_indx])!=target_freq.end() ){
                                // 删掉第一个B以后, 遇到的有效字符, 不删除, 并且停止, 然后进行下一步
                                // CB 保持 -> CB
                                if(del_flag==1){
                                    //不进行删除
                                    //停止整个for循环
                                    // test output
                                    myOutput_string(og,st_indx,ed_indx);
                                    break;
                                }
                                // 没有删除第一个B前, 遇到的的有效字符 删除
                                // {C E B G C B} -> {   E B G C B}
                                else{
                                    og_window_freq[og[st_indx]]--;
                                    window_effect_len--;
                                    st_indx++;
                                }
                            }
                            //如果不是任何有效字符
                            // {   E B G C B} -> {    B G C B}
                            else{
                                //进行删除
                                st_indx++;
                            }
                        }
                        // test output
                        myOutput_string(og,st_indx,ed_indx);
                    }
                }
                // 既然能插的进去 就看一下 能不能缩小一下
                else if(og_window_freq[c_tmp]==target_freq[c_tmp]){
                    // test output
                    myOutput_string(og,st_indx,ed_indx);
                    for(;st_indx<=ed_indx;){
                        //
                        //例如 og=sab 中找 target=b
                        //
                        // 例如这个a 就不存在的
                        if(target_freq.find(og[st_indx])==target_freq.end() ){
                            st_indx++;
                        }
                        else{
                            break;
                        }
                        // test output
                        myOutput_string(og,st_indx,ed_indx);
                    }
                }

                //结束查看 当前window的有效长度 == target的长度
                //也就是
                //A B C == A B C
                //1 1 2    1 1 2
                if(window_effect_len==target.size()){
                    //然后看是不是最小的长度
                    int len_tmp = ed_indx - st_indx + 1;
                    // 如果比之前的答案还要小, 记下当前结果
                    if(len_tmp<rs_min_length){
                        rs_st_indx = st_indx;
                        rs_ed_indx = ed_indx;
                        rs_min_length = len_tmp;
                    }
                }

            }
            // test output
            myOutput_string(og,st_indx,ed_indx);
        }



        if(rs_min_length==INT32_MAX){
            return "";
        }
        else{
            return og.substr(rs_st_indx,rs_min_length);
        }
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();



    string str_og("ab");
    string target("b");

    //string str_og("ADOBECODEBANC");
    //string target("ABC");

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


