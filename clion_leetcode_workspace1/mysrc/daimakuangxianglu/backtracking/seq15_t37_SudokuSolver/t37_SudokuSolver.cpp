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
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 * The '.' character indicates empty cells.
 *
 *  board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
 *  Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
 *
 * Example2:
 * Input:  n = 1
 * Output: [["Q"]]
 *
 * Constraints:
 * board.length == 9
 * board[i].length == 9
 * board[i][j] is a digit or '.'.
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


    bool judgeValid(vector<vector<char>>& chessboard, const int tgrow_idx, const int tgcol_idx, char content){
        //检查列, 从目标处往上搜, 因为后面的棋子还没放呢
        for(int i=tgrow_idx-1;i>=0;i--){
            if(chessboard[i][tgcol_idx]==content){
                return false;
            }
        }

        //检查行, 从目标处往左搜, 因为后面的棋子还没放呢
        for(int i=tgcol_idx-1;i>=0;i--){
            if(chessboard[tgrow_idx][i]==content){
                return false;
            }
        }


        int sub9area_rowidx=tgrow_idx/3*3;
        int sub9area_colidx=tgcol_idx/3*3;
        //搜索范围 [sub9area_rowidx][sub9area_colidx] -> [tgrow_idx][sub9area_colidx]
        // 但是可以在                                    [tgrow_idx][tgcol_idx] 就可以跳出
        for(int i=sub9area_rowidx;i<=tgrow_idx;i++){
            for(int j=sub9area_colidx;j<=sub9area_colidx+2;j++){
                //只搜索当前数字所在的九宫格, 且仅验证 该数字之前的 已存在的数字
                // 整个judge vali的跳出点 a[tgrow_idx][tgcol_idx]
                if(i == tgrow_idx && j == tgcol_idx){
                    return true;
                }
                else{
                    if(chessboard[i][j]==content){
                        return false;
                    }
                }

            }

        }
        return false;
    }

    // 假设第一行你就知道了
    // 假设当前第一行
    // [.,.,.,| 6,.,., | .,8,.]
    // 然后开始填写
    // [1,.,.,| 6,.,., | .,8,.]
    // [1,1,.,| 6,.,., | .,8,.]
    // [1,2,.,| 6,.,., | .,8,.]
    // [1,2,1,| 6,.,., | .,8,.]
    // [1,2,2,| 6,.,., | .,8,.]
    // [1,2,3,| 6,.,., | .,8,.]
    // [1,2,3,| 6,.,., | .,8,.] 6已存在 不填写
    // [1,2,3,| 6,1,., | .,8,.]
    // [1,2,3,| 6,2,., | .,8,.]
    //...
    // [1,2,3,| 6,4,., | .,8,.]
    //...
    // [1,2,3,| 6,4,5, | .,8,.]
    //...
    // [1,2,3,| 6,4,5, | 7,8,.]
    //...
    // [1,2,3,| 6,4,5, | 7,8,9]
    // 然后第二行 原来是什么都没有的然后 和第一行变成了
    // [1,2,3,| 6,4,5, | 7,8,9]
    // [.,.,.,| .,.,., | .,.,.]
    // 直到这一步
    // [1,2,3,| 6,4,5, | 7,8,9] 第一行
    // [4,5,6,| 1,2,3, | 1,.,.]
    // ->一直尝试到了
    // [4,5,6,| 1,2,3, | 7,.,.] 不行, 因为和上面的相同了
    // [4,5,6,| 1,2,3, | 8,.,.] 不行, 因为和上面的相同了
    // [4,5,6,| 1,2,3, | 9,.,.] 不行, 因为和上面的相同了
    //
    // 此时9个数字全部尝试完 回退
    // [4,5,6,| 1,2,3, | .,.,.]
    // 并从3尝试4 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // [4,5,6,| 1,2,4, | .,.,.] 不行, 因为和同行的相同了
    // [4,5,6,| 1,2,5, | .,.,.] 不行, 因为和同行的相同了
    // [4,5,6,| 1,2,6, | .,.,.] 不行, 因为和同行的相同了
    //
    // 尝试到了7 和第一行组成了这样
    // [1,2,3,| 6,4,5, | 7,8,9] 第一行
    // [4,5,6,| 1,2,7, | .,.,.] 这样看暂时行的通, 往下走
    // [4,5,6,| 1,2,7, | 3,.,.]
    // [4,5,6,| 1,2,7, | 3,7,.] 不行, 因为和上面的相同了, 然后又往前回退, 以此类推
    // ...
    //
    // 这很明显了 他的backtracking 是拿着手上这个点, 去backtrack 后面的所有可能性
    bool backtracking(vector<vector<char>>& chessboard, int now_row_idx, int now_col_idx){
        //limit
        // 能从一个点不停的进去 走到这里
        // 就证明上一个字符 '1'~'9' 放置时是没有问题的
        // 此时只是 判断的位置已经满了 没有再需要你去搞的地方了
        // 所以这里成功了 所以return true
        if(now_row_idx ==chessboard.size()-1+1){
            //结束
            //rs.push_back(chessboard);
            return true;
        }


        // 如果当前行满了走到下一行
        // 不管行数是否超了, 反正上面接着
        if(now_row_idx <= chessboard.size()-1 && now_col_idx==chessboard[0].size()-1+1){
            return backtracking(chessboard,now_row_idx+1,0);
        }

        //如果当前已经是题目预设好的
        // 则直接进入下一个
        if(now_row_idx<=chessboard.size()-1 && now_col_idx<=chessboard[0].size()-1 && chessboard[now_row_idx][now_col_idx]!='.'){
            return backtracking(chessboard,now_row_idx,now_col_idx+1);
        }



        // 就像是
        // [.,.,.,| 6,.,., | .,8,.]
        // 然后开始填写
        // [1,.,.,| 6,.,., | .,8,.] ->然后进入backtracking方法
        // [1,1,.,| 6,.,., | .,8,.] ->此时他上一层入口 是最开始的那个1, 而不是它自己 或 自己重新的是弄出来的
        for(int i=now_row_idx;i<=chessboard.size()-1;i++){
            for(int j=now_col_idx;j<=chessboard[0].size()-1;j++){
                for(char ch_tmp='1';ch_tmp<='9';ch_tmp++){
                    bool judgeValidFlag=judgeValid(chessboard,i,j,ch_tmp);

                    //如果可以放置 则从这个点作为入口去 进入到 下一个点看
                    if(judgeValidFlag==true){
                        chessboard[i][j] = ch_tmp;
                        if(backtracking(chessboard,i,j+1)){
                            return true;
                        }

                        //pop
                        chessboard[i][j] = '.';
                    }
                }
                return false;

            }
        }


        return false;
    }


    //时间复杂度: O(9^m × n)
    //    对于 judgeValid 函数：
    //      行检查：最多 O(n) 操作
    //      列检查：最多 O(n) 操作
    //
    //    3×3 小方格检查：最多 O(1) 操作（固定大小）
    //      因此，每次判断有效性的时间复杂度是 O(n)。
    //综合来看，整体的时间复杂度是 O(9^m × n)，其中 m 是空格数，n 是棋盘大小（在标准数独中 n=9）。
    //
    //空间复杂度: O(n^2)
    //
    //    存储棋盘本身需要 O(n^2) 的空间（9×9 矩阵）
    //    递归调用栈的深度最多为 O(n^2)，因为最多需要填充 n^2个空格
    // 没有使用额外的显著空间，所以总体空间复杂度是 O(n²)。
    void solveSudoku(vector<vector<char>>& board) {

        backtracking(board,0,0);

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
    vector<vector<char>> vec_vec_char={
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    solut1->solveSudoku(vec_vec_char);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBvecBtBB(vec_vec_char,0,vec_vec_char.size()-1);
    return 0;
}


