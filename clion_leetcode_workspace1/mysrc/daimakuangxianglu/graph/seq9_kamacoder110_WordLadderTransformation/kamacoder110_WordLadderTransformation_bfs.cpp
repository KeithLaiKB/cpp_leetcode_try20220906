#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>
#include <list>


using namespace std;

/**
 * 字典 strList 中从字符串 beginStr 和 endStr 的转换序列是一个按下述规格形成的序列：
 *
 * 1. 序列中第一个字符串是 beginStr。
 *
 * 2. 序列中最后一个字符串是 endStr。
 *
 * 3. 每次转换只能改变一个字符。
 *
 * 4. 转换过程中的中间字符串必须是字典 strList 中的字符串，且strList里的每个字符串只用使用一次。
 *
 * 给你两个字符串 beginStr 和 endStr 和一个字典 strList，找到从 beginStr 到 endStr 的最短转换序列中的字符串数目。如果不存在这样的转换序列，返回 0。
 *
 * 输入:
 * 第一行包含一个整数 N，表示字典 strList 中的字符串数量。 第二行包含两个字符串，用空格隔开，分别代表 beginStr 和 endStr。 后续 N 行，每行一个字符串，代表 strList 中的字符串。
 *
 *
 * 输出:
 *  输出一个整数，代表从 beginStr 转换到 endStr 需要的最短转换序列中的字符串数量。如果不存在这样的转换序列，则输出 0。
 *
 *
 *
 * 例如
 * abc def
 * efc
 * dbc
 * ebc
 * dec
 * dfc
 * yhn
 *      他指的是 终点只能为5的路径
 *
 *
 *
 *
 *
 * 本身来说 他们 就是无向图
                            ---  dbc ------>   dec ------- (def)
                     -----        |             |
          (abc)  ----             |             |
                     ----         |             |
                         ---      |             |
                            ---  ebc           dfc
                                 |              |
                                   |           |
                                      |     |
                                      |  |
                                      efc                    yhn (独立出来了, 因为没有人跟他连接)


为什么 说是无向图,
    因为 我这里加个箭头 (我这里不是指 变化成 有向图, 只是代表 能够从开始 到 终点 的变化的顺序)
    你可以感觉到
    不是按照 第一轮改 第一层字母, 第二轮改第二层字母 来做的

    你从 abc->efc->dfc->dec->def 可以看到 他就不是按照 这种方式改的,
    你可以看到正确来说
        他是第一轮 改第一个字母
            第二轮 改第二个字母
            第三轮 改第一个字母
            第四轮 改第二个字母
            第五轮 改第三个字母

                            -->  dbc ------>   dec ------>  (def)
                     -----        |             /\
          (abc)  ----             |             |
                     ----         |             |
                         ---     \/             |
                            -->  ebc           dfc
                                 |             /\
                                   |           |
                                      |     |
                                     \/  |
                                      efc                    yhn (独立出来了, 因为没有人跟他连接)

 *
 * 结果:
 * 4
 * 因为
 *  abc -> dbc -> dec -> def
 *
 * 我们这里不需要邻接表 和临界矩阵
 *      因为他并不像 我们前面那样 需要 重复使用 那个 图(邻接矩阵/邻接表)
 *          来对里面的每个 格子 都去走个 什么dfs/bfs
 *
 * abc 把 这三位的每一位 改编成 bcdefgh......
 *      然后搜索对应的 是否在我们这个 nodes里面存在 {"efc","dbc","ebc","dec","dfc","yhn"};
 *      此时 只有 abc,ebc符合, 因为 也不存在什么 adc, aba之类的东西
 *
 *      q_root : dbc, ebc
 *
 *      更改 dbc 并且找对应存在的 字符串放到队尾
 *      找到    : ebc(不算, 因为已经访问过, 不要重复放进去),dec
 *      q_root : ebc, dec
 *
 *      更改 ebc 并且找对应存在的 字符串放到队尾
 *      找到    : dbc(不算, 因为已经访问过, 不要重复放进去),dfc
 *      q_root : dec,efc
 *
 *      更改 dec 并且找对应存在的 字符串放到队尾
 *      找到    : def, dfc                    (你可以很明显在这里看到,
 *                                              反而dfc 最早是 abc->dbc->dec->dfc访问到的,
 *                                              而不是 abc->ebc->efc->dfc, 所以这就是无向图!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
 *      q_root : 不需要看了, 因为已经到达终点
 *
 *
 *
 */

class Solution {
private:

public:
    Solution(){

    }
    ~Solution(){

    }
    template <typename T>
    void myOutput_VectorBvecBtBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            vector<T> vec_tmp = nums[i];
            // 比如 会出现这种 里面有空的情况 {{1}，{1,2},{},{4,5,6}}
            if (vec_tmp.empty()==true){
                cout<<"this is empty element(row)"<<endl;
                continue;
            }

            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<vec_tmp[j]<<"\t";
            }
            cout<<endl;
        }
    }


    template <typename T>
    void myOutput_VectorBlistBtBB(vector<list<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            list<T> vec_tmp = nums[i];
            for(int &num: vec_tmp){
                cout<<num<<"\t";
            }
            cout<<endl;
        }
    }





    //时间复杂度:
    //空间复杂度:
    //

    //
    int WordLadderTransformation_byOneLetter_bfs(string str_st, string str_ed, vector<string> vecstr_nodes){

        // 记录 从start 走到当前str 需要多长的距离
        // 同时 它的存在 也代表它 已经走过
        unordered_map<string,int> walked_len;
        queue<string> q_root;

        int rs_success_nodes_num=0;
        int rs_len=0;

        // 把题目中的那些东西 先放在里面
        for(string str_tmp: vecstr_nodes){
            //walked_len.insert(pair<string,int>(str_tmp,-1));    // 还没被访问过 则是保持-1, 不知道为什么 这个过不了那个网页的testcase, 按道理不会重复赋值才对啊
            walked_len[str_tmp] = -1;  // 还没被访问过 则是保持-1
        }

        q_root.push(str_st);
        //walked_len.insert(pair<string,int>(str_st,0));      //初始当前 已经放问过start
        //walked_len.insert(pair<string,int>(str_ed,-1));     // 还没被访问过 则也是保持-1
        walked_len[str_st] = 0;       // 初始当前 已经放问过start, 不知道为什么 这个过不了那个网页的testcase, 按道理不会重复赋值才对啊
        walked_len[str_ed] = -1;      // 还没被访问过 则也是保持-1, 不知道为什么 这个过不了那个网页的testcase, 按道理不会重复赋值才对啊

        int int_walked_len_tmp=0;
        while(q_root.empty()==false){
            string str_tmp = q_root.front();
            q_root.pop();

            int_walked_len_tmp = walked_len[str_tmp];

            // 对当前string 的每一位 都进行尝试替换
            // 例如abc,
            // 不仅要尝试 bbc, cbc, dbc, ebc ....zbc
            // 还要尝试   aac, acc, adc, aec....azc
            // 还要尝试   aba, abb, abd, abe....abe
            for(int i=0;i<=str_tmp.size()-1;i++){

                //复原一下, 因为上一次 改第一个字符的可能会变成 zbc，
                // 如果不复原,
                //      那么 下面我们本来 要一直查到 azc, 的
                //      结果因为 第一个字符没有复原
                //      导致 变成                 zzc
                string new_str1_tmp = str_tmp;
                for(int j=0;j<=26-1;j++){
                    new_str1_tmp[i] = 'a'+j;

                    // 如果发现 这个 存在 已知列表中(也就是属于nodes的范围内), 并且没有被访问过
                    // 则进行进一步处理
                    if(walked_len.find(new_str1_tmp)!=walked_len.end() && walked_len[new_str1_tmp]==-1){

                        walked_len[new_str1_tmp]=int_walked_len_tmp+1;     //修改值
                        q_root.push(new_str1_tmp);                      //把新str 放进队列

                        if(new_str1_tmp == str_ed){
                            rs_len = int_walked_len_tmp+1;

                            // 点数 = 变长+1
                            rs_success_nodes_num = rs_len+1;
                            return rs_success_nodes_num;
                        }
                    }


                }
            }
        }


        // 就是题目要求, 如果 变不了 就return0
        // 如果变的了 就返回 总共的 最短node的个数
        if(rs_len!=0){
            // 点数 = 变长+1
            rs_success_nodes_num = rs_len+1;
        }


        return rs_success_nodes_num;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();

    // 初始化 图
    //vector<vector<int>> adjacencyList1 = solut1->init_AdjacencyList_vector_ints();
    //solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);


    string str1 = "abc";
    string str2 = "def";
    vector<string> vecstr1 = {"efc","dbc","ebc","dec","dfc","yhn"};
    int rs1 = solut1->WordLadderTransformation_byOneLetter_bfs(str1,str2, vecstr1);



    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


