#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <climits>
#include <unordered_set>

#include <algorithm>

using namespace std;

/**
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 *
 * You may return the answer in any order.
 * Each solution contains a distinct board configuration of the n-queens' placement,
 * where 'Q' and '.' both indicate a queen and an empty space, respectively.
 *
 * Example1:
 * Input:  n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
 *
 * Example2:
 * Input:  n = 1
 * Output: [["Q"]]
 *
 *
 * 他做的是对chessboard进行处理
 * 你要思考 他是怎么变成逻辑树的
 *      他只不过是 对 vector<vector<string>> 进行一个个搜
 *
 * 你可能会很糊涂 为什么for循环只是针对 col来做, 他明明就是 二维数组?
 *      但你要记得 本身递归 他就已经代表了一层for循环了!!!!!!!!
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
    void myOutput_VectorBvecBtBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            vector<T> vec_tmp = nums[i];
            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<vec_tmp[j]<<"\t";
            }
            cout<<endl;
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

    // [".Q..","...Q","Q...","..Q."],
    // 每个string就是一行
    bool judgeValid(vector<string>& chessboard, const int tgrow_idx, const int tgcol_idx, const int n){
        //检查列, 从目标处往上搜, 因为后面的棋子还没放呢
        for(int i=tgrow_idx-1;i>=0;i--){
            if(chessboard[i][tgcol_idx]=='Q'){
                return false;
            }
        }

        //检查行, 从目标处往左搜, 因为后面的棋子还没放呢
        for(int i=tgcol_idx-1;i>=0;i--){
            if(chessboard[tgrow_idx][i]=='Q'){
                return false;
            }
        }


        //检查左上的45度, 从目标处往左上搜, 因为后面的棋子还没放呢
        for(int i=1;tgrow_idx-i>=0 && tgcol_idx-i>=0;i++){
            if(chessboard[tgrow_idx-i][tgcol_idx-i]=='Q'){
                return false;
            }
        }

        //检查右上的45度, 从目标处往右上搜, 因为后面的棋子还没放呢
        for(int i=1;tgrow_idx-i>=0 && tgcol_idx+i<=n-1;i++){
            if(chessboard[tgrow_idx-i][tgcol_idx+i]=='Q'){
                return false;
            }
        }

        return true;
    }


     //
     // 我们会发现 这里不会 使用 tickets 也就是我们常说的candidate数组
     // 而是使用弄好的一个map 来弄
    int backtracking(vector<string>& chessboard, int n, int now_row_idx, vector<vector<string>>& rs){
        //limit
        if(now_row_idx ==n){
            //结束
            rs.push_back(chessboard);
            return 1;
        }

        // 只对当前行从左往右写,
        // 因为n皇后 一共n 行n列一共要放n个皇后
        // 因为之前的是合法放置, 所以接下来把当前行 作为基石, 然后对后面的可能性进行遍历就可以了
        for(int col_tmp=0 ; col_tmp<=n-1 ; col_tmp++){
            bool judgeValidFlag = judgeValid(chessboard,now_row_idx,col_tmp,n);
            //如果发现 可以合法放置
            if(judgeValidFlag==true){
                //放置
                chessboard[now_row_idx][col_tmp]='Q';

                //backtracking
                // 对下一行进行处理, 下一行的那个backtracking也是从左往右的对列进行处理
                backtracking(chessboard,n,now_row_idx+1,rs);

                //pop
                chessboard[now_row_idx][col_tmp]='.';

            }
            //不合法的话 继续看下一列
            else{
                continue;
            }
        }

        return 0;
    }


    //时间复杂度: O(n * n!)
    //  对于n皇后的问题，例如第一次 我可以放置n个皇后,所以有n种可能性
    //                  第二次 我可以放置n-1个皇后,所以有n-1种可能性
    //                  第三次 我可以放置n-2个皇后,所以有n-2种可能性
    //  以此类推复杂度有O(n!)
    //
    //  在每次递归调用中，judgevalid 的复杂度是O(n)
    //综合来看，时间复杂度为O(n * n!)
    //
    //空间复杂度: O(n^2)
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, string(n,'.'));
        vector<vector<string>> rs1;

        backtracking(chessboard,n,0,rs1);
        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    int n =4;
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    //string str1 ="101023";
    vector<vector<string>> rs1 = solut1->solveNQueens(4);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBvecBtBB(rs1,0,rs1.size()-1);
    return 0;
}


