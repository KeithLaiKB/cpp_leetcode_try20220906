#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <climits>

#include <algorithm>

using namespace std;

/**
 *
 * A valid IP address consists of exactly four integers separated by single dots.
 * Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
 * For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses,
 * but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
 *
 * Given a string s containing only digits,
 * return all possible valid IP addresses that can be formed by inserting dots into s.
 * You are not allowed to reorder or remove any digits in s.
 * You may return the valid IP addresses in any order.
 *
 *
 * Example1:
 * Input: s = "25525511135"
 * Output: ["255.255.11.135","255.255.111.35"]
 *
 * Example2:
 * Input: s = "0000"
 * Output: ["0.0.0.0"]

 * Example2:
 * Input: s = "101023"
 * Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 *
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

    template<typename T>
    void myOutput_VectorBVectorBintBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            for(int j=0;j<=nums[i].size()-1;j++){

                cout<<nums[i][j]<<"\t";
                if(j==nums[i].size()-1){
                    cout<<endl;
                }

            }
        }
    }

    template<typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }


    bool judgeValid(const string &s, int st_idx, int ed_idx){
        if(ed_idx-st_idx+1>3){
            return false;
        }
        //
        else if (ed_idx-st_idx+1==3){
            int num=0;
            for(int i=st_idx;i<=ed_idx;i++){
                num= num*10 + (s[i]-'0');
            }
            if(num<=255){
                return true;
            }
            else{
                return false;
            }
        }
        else if (ed_idx-st_idx+1<3){
            return true;
        }
        return false;
    }
    //
    //                                                                  [1211312]
    //                                          [1]
    //                              [2]                      ......      [21]
    //                    [1]               [13]            .....   [1]
    //               [1312] 4个数字不成功   [12] 成功              [312] 超过3个数字
    //
    // now_content 装得是 例如 {"127" , "0" , "0", "1"} 他是string 类型的来的
    int backtracking(string s, int layer_idx, int st_idx,vector<string> &now_content, vector<string> &rs){
        //limit
        // 因为如果上一层不是回文, 是不会走到这里的
        // 0 1 2 3   到了4就证明前面的{0,1,2,3} 已经能组成了IP
        if(layer_idx==4){
            //如果此时还有剩下的, 则证明多出来了 例如 127.0.0.1.255
            //
            // 127.0.0.1|
            //          st_idx
            // 正常来说 此时 st_idx -1 ==s.size()-1 才对
            //              也就是 st_idx == s.size()
            //
            // 如果
            // 127.0.0.1 2 3 4 5 6 7 8
            //             |         |
            //          st_idx       s.size()-1
            // 就不行
            if(st_idx<=s.size()-1){
                return 0;
            }

            // 组装
            string ipadd_tmp=now_content[0];
            for(int i=1;i<=now_content.size()-1;i++){
                ipadd_tmp.append(1,'.').append(now_content[i]);
            }
            rs.push_back(ipadd_tmp);
            return 1;
        }

        //deal
        string str_tmp="";          //来做自增

        //for
        for(int i =st_idx;i<=s.size()-1;i++){


            // 如果当前octet的size >=2,
            //      则开头不能是0
            // 也就是说 可以 127.0.0.1
            // 但 不可以    127.01.0.1
            if(i-st_idx+1>=2 && s[st_idx]-'0'==0){
                break;
            }


            str_tmp.push_back(s[i]);
            bool jdgv_tmp=judgeValid(s,st_idx,i);
            //
            // [1,21,1,312] 不行 不代表兄弟节点的 [1,21,13,12]不行
            // 所以不可以break
            if(jdgv_tmp==false){
                continue;
            }

            //backtracking
            //看后面
            now_content.push_back(str_tmp);
            backtracking(s, layer_idx+1, i+1,now_content,  rs);

            //
            // 弹出当前, 为了 让下一个 自增后的再进来
            //pop
            now_content.pop_back();

        }

        return 0;
    }
    //
    // 时间复杂度: O(1)
    //      最多 3^4 = 81 种分割方式
    //
    // 空间复杂度: O(4 + k) = O(k)，
    //      4是栈的深度
    //      k 是结果数量
    vector<string> restoreIpAddresses(string s) {
        vector<string> rs1={};
        vector<string> now_content={};
        backtracking(s, 0, 0,now_content,  rs1);

        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    //vector<int> intvec1 ={10,1,2,7,6,1,5};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    string str1 ="101023";
    vector<string> rs1 = solut1->restoreIpAddresses(str1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    return 0;
}


