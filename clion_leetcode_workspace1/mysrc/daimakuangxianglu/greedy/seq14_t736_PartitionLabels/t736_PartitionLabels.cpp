#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
//#include <cstdint>
#include <climits>


using namespace std;

/**
 *
 * You are given a string s. We want to partition the string into as many parts as possible
 * so that each letter appears in at most one part.
 * For example, the string "ababcc" can be partitioned into ["abab", "cc"],
 * but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.
 *
 * Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.
 *
 * Return a list of integers representing the size of these parts.
 *
 *
 * Example1:
 * Input: s = "ababcbacadefegdehijhklij"
 *Output: [9,7,8]
 *Explanation:
 *The partition is "ababcbaca", "defegde", "hijhklij".
 *This is a partition so that each letter appears in at most one part.
 *A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.
 *
 *
 * Example2:
 * Input: s = "eccbbbbdec"
 *Output: [10]
 *

 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    template <typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    bool static mycomp(const vector<int> &a, const vector<int> &b){
        if(a[0]==b[0]){
            return a[1]<b[1];
        }
        else{
            return a[0]<b[0];
        }
    }


    // 时间复杂度：
    //
    // 空间复杂度：
    //
    //
    // 我这个是能通过leecode的测试的
    // 但他不是贪心算法
    vector<int> partitionLabels_my(string s){
        unordered_map<char,int> map_ch_pos;
        vector<string> vec_str1={};

        // 对于这变量的简单小例子
        //vector 里面当前 有实际内容 的最大的下标, 因为例如 vec[0]="a", vec[1]="cde",vec[2]="",vec[3]=""
        //但是 vec.size = 4, 如果我们要插一个 f
        // 则需要查到 vec[now_max_used_idx+1] = 'f'
        // 从而 vec[0]="a", vec[1]="cde",vec[2]="f",vec[3]=""
        int now_max_used_idx = -1;

        char check_ch=0;


        vector<int> len_in_vecstr1={};

        //例如 babacacb dfgd hsh f
        // map<char,int> = {char, 插入到第几个string里}

        //          vec_string[0]: b
        //          vec_string[1]:
        //              checked ： a
        //          {{'b',0}}
        // 得到一个string
        //          vec_string[0]: b
        //          vec_string[1]: a
        //          checked： b
        //          {{'b',0},{'a',1}}
        // 因为搜索到有{'b',0} 所以 从vec_string[0]开始, 合并完到这个check, 然后放到vec_string[0], 并且把{‘a’,1}变成{'a',0}
        // 于是得到
        //          vec_string[0]: bab
        //          vec_string[1]:
        //          checked：a
        //          {{'b',0},{'a',0}}
        // 因为搜索到有{'a',0} 所以 从vec_strsing[0]开始, 合并完到这个check, 然后放到vec_string[0], 并且{'a',0}
        // 于是得到
        //          vec_string[0]: baba
        //          vec_string[1]:
        //          checked：c
        //          {{'b',0},{'a',0}}
        // 得到一个string
        //          vec_string[0]: baba
        //          vec_string[1]: c
        //          checked：a
        //          {{'b',0},{'a',0},{'c',1}}
        // 因为搜索到有{'a',0} 所以 从vec_string[0]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[0], 并且把{‘c’,1}变成{'c',0}
        // 于是得到
        //          vec_string[0]: babaca
        //          vec_string[1]:
        //          check：c
        //          {{'b',0},{'a',0},{'c',0}}
        // 因为搜索到有{'c',0} 所以 从vec_string[0]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[0], 并且{'c',0}
        // 于是得到
        //          vec_string[0]: babacac
        //          vec_string[1]:
        //          check：b
        //          {{'b',0},{'a',0},{'c',0}}
        // 因为搜索到有{'b',0} 所以 从vec_string[0]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[0], 并且{'b',0}
        // 于是得到s
        //          vec_string[0]: babacacb
        //          vec_string[1]:
        //           check：d
        //          {{'b',0},{'a',0},{'c',0}}
        // 得到一个string
        //          vec_string[0] babacacb
        //          vec_string[1]: d
        //            check：f
        //          {{'b',0},{'a',0},{'c',0},{'d',1}}
        // 得到一个string
        //          vec_string[0]: babacacb
        //          vec_string[1]: d
        //          vec_string[2]: f
        //          check：g
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',2}}
        // 得到一个string
        //          vec_string[0]: babacacb
        //          vec_string[1]: d
        //          vec_string[2]: f
        //          vec_string[3]: g
        //          check：d
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',2},{'g',3}}
        // 因为搜索到有{'b',1} 所以 从vec_string[1]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[1], 并且{'d',1},{'f',1},{'g',1}
        // 于是得到
        //          vec_string[0]: babacacb
        //          vec_string[1]: dfgd
        //          vec_string[2]:
        //          vec_string[3]:
        //          check：h
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',1},{'g',1}}
        // 得到一个string
        //          vec_string[0]: babacacb
        //          vec_string[1]: dfgd
        //          vec_string[2]: h
        //          vec_string[3]:
        //          check：s
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',1},{'g',1},{'h',2}}
        // 得到一个string
        //          vec_string[0]: babacacb
        //          vec_string[1]: dfgd
        //          vec_string[2]: h
        //          vec_string[3]: s
        //          check：h
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',1},{'g',1},{'h',2},{'s',3}}
        // 因为搜索到有{'h',2} 所以 从vec_string[2]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[2], 并且{'h',2},{'s',2},{'h',2}
        // 于是得到
        //          vec_string[0]: babacacb
        //          vec_string[1]: dfgd
        //          vec_string[2]: hsh
        //          vec_string[3]:
        //          check：f
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',1},{'g',1},{'h',2},{'s',3}}
        // 因为搜索到有{'f',2} 所以 从vec_string[1]开始, 合并完vec_string[len-1]到这个check, 然后放到vec_string[1], 并且{'h',1},{'s',1},{'f',1}
        // 于是得到
        //          vec_string[0]: babacacb
        //          vec_string[1]: dfgdhshf
        //          vec_string[2]:
        //          vec_string[3]:
        //          {{'b',0},{'a',0},{'c',0},{'d',1},{'f',1},{'g',1},{'h',1},{'s',1}}
        // 然后结束


        for(int i=0;i<=s.size()-1;i++){
            check_ch = s[i];

            // 新字符
            if(map_ch_pos.find(check_ch)==map_ch_pos.end()){
                //放到一个单独的string
                // 如果 当前 vector 不够位置放了, 则push来加空间来放
                if(now_max_used_idx==vec_str1.size()-1){
                    vec_str1.push_back(string(1, check_ch));
                }
                // 如果 够位置,
                // 例如 vec[0]="a", vec[1]="cde",vec[2]="",vec[3]=""
                // 则从 vec[2]==“”开始放
                else{
                    vec_str1[now_max_used_idx+1]=string(1, check_ch);
                }

                ++now_max_used_idx;     //当前使用的下标更新

                //放进map
                map_ch_pos.insert(pair<char,int>(check_ch,now_max_used_idx));

            }
            // 不是新字符
            else{
                int target_pos_tmp = map_ch_pos[check_ch];

                //更新 map
                for(int i=target_pos_tmp+1;i<=now_max_used_idx;i++){
                    string str_tmp = vec_str1[i];

                    // 每个string, 里面的每个字符 对应的 map
                    // 都要更新 它里面的 value(就是新的在vec_str1里的 idx)
                    for(int i=0;i<=str_tmp.size()-1;i++){
                        char ch_tmp=str_tmp[i];
                        map_ch_pos[ch_tmp] = target_pos_tmp;
                    }

                    //把当前这个vec_str[i] 设置 "" 因为当前这个已经被合并到了 target_pos_tmp
                    vec_str1[target_pos_tmp].append(str_tmp);
                    vec_str1[i]="";


                }

                // 合并后, 当前有内容的最大idx进行更新
                now_max_used_idx = target_pos_tmp;

                vec_str1[target_pos_tmp].append(string(1,check_ch));
                map_ch_pos[check_ch] = target_pos_tmp;
            }

            cout<<now_max_used_idx<<endl;
            myOutput_VectorBtB(vec_str1,0,now_max_used_idx);
            cout<<endl;
        }


        //循环字符数组 得出result
        for(int i=0;i<=now_max_used_idx;i++){
            cout<<"str"<<i<<":"<<vec_str1[i]<<endl;
            len_in_vecstr1.push_back(vec_str1[i].size());
        }

        return len_in_vecstr1;
    }

    // 时间复杂度：O(n)
    //
    // 空间复杂度：O(1)
    //
    vector<int> partitionLabels(string s){
        vector<int> len_in_vecstr1;
        int ch_longestpos_idx[26] = {};

        vector<string> vec_str1={};     //可以不用, 我只是拿来检查看一下

        // 例如   a   b   d   a   b   b
        //
        //   pos{0}                 a
        //   pos{0, 1}              ab
        //   pos{0, 1, 0, 2}        abd
        //   pos{3, 1, 0, 2}        abda 更新 a的最远距离
        for(int i=0;i<=s.size()-1;i++){
            char ch_tmp=s[i];
            ch_longestpos_idx[ch_tmp-'a']=i;
        }

        // 然后再去遍历
        int now_left_idx=0;
        int now_maxright_idx=0;
        int len_tmp = 0;
        for(int i=0;i<=s.size()-1;i++){
            char ch_tmp=s[i];
            now_maxright_idx = max(ch_longestpos_idx[ch_tmp-'a'], now_maxright_idx);

            if(i==now_maxright_idx){
                len_tmp = now_maxright_idx - now_left_idx  +1;
                len_in_vecstr1.push_back(len_tmp);

                vec_str1.push_back(s.substr(now_left_idx,len_tmp)); // 检查看一下 string 分别是什么, 当然你可以删掉

                //然后重置left到新的区域
                now_left_idx = i + 1;
            }
        }

        // 检查看一下 string 分别是什么, 当然你可以删掉
        for(int i=0;i<=vec_str1.size()-1;i++){
            cout<<"str"<<i<<":"<<vec_str1[i]<<endl;
        }


        return len_in_vecstr1;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    //vector<vector<int>> vec_vec_int1={{10,16},{2,8},{1,6},{7,12}};

    //string str1 = "babacacbdfgdhshf";
    string str1 = "ababcbacadefegdehijhklij";

    vector<int> rs1 = solut1->partitionLabels(str1);
    cout<<"result:"<<endl;
    //cout<<rs1<<endl;
    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    return 0;
}


