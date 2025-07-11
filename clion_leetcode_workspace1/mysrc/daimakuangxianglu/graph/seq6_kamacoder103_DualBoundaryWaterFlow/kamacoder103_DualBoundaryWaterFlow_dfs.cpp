#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>

using namespace std;

/**
 * 现有一个 N × M 的矩阵，每个单元格包含一个数值，
 * 这个数值代表该位置的相对高度。
 *
 * 矩阵的左边界和上边界被认为是第一组边界，
 * 而矩阵的右边界和下边界被视为第二组边界。
 *
 * 矩阵模拟了一个地形，当雨水落在上面时，水会根据地形的倾斜向低处流动，
 * 但只能从较高或等高的地点流向较低或等高并且相邻（上下左右方向）的地点。
 *
 * 我们的目标是确定那些单元格，从这些单元格出发的水可以达到第一组边界和第二组边界。
 *
 * 输入:
 * 第一行包含两个整数 N 和 M，分别表示矩阵的行数和列数。
 * 后续 N 行，每行包含 M 个整数，表示矩阵中的每个单元格的高度。
 *
 *
 * 输出:
 *  输出共有多行，每行输出两个整数，用一个空格隔开，
 *  表示可达第一组边界和第二组边界的单元格的坐标，输出顺序任意。
 *
 *
 *  4 5
 *  于是有
 *  1 1 0 0 0
 *  1 1 0 0 0
 *  0 0 1 0 0
 *  0 0 0 1 1
 *
 * ---------------------------------------------
 *
 * 例如
 *
 *  1 1 1 1 1 1 1
 *  1 1 1 1 1 4 1
 *  1 2 1 5 2 1 1
 *  1 2 3 6 1 1 1
 ×  1 4 7 2 1 1 1
 *
 *
 * 上左  为边界A
 * 右下  为边界B
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
            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<vec_tmp[j]<<"\t";
            }
            cout<<endl;
        }
    }




    // 他虽然也是 二维数组
    // 但他并不是邻接矩阵,
    // 因为临界矩阵 里面的含义是
    // 从 x 到 y 点 是否可达
    //
    // 而这里的地图指的是 这是岛屿 还是 海
    vector<vector<int>> init_IslandMap_ints(){

        //----------------- 模拟console 进来的参数  ---------------------

        // simulate input,
        // 我这里 就不用 cin>>x1>>x2; 来搞了,
        // 不然输入太麻烦了
        vector<vector<int>> simul_input ={{1,1,0,0,0},
                                          {1,1,0,0,0},
                                          {0,0,1,0,0},
                                          {0,0,0,1,1}};


        // 这里 和邻接矩阵 不一样 这已经是个图了 !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 不需要 根据点和点 的关系 再去init 一个邻接矩阵 什么的了
        return simul_input;
    }







    //
    //
    //这个就是虽然 不是那么好理解 甚至不太像回溯(当然也不是回溯, 写成像回溯只是说为了好背)
    //但这种写法不容易超时
    //
    // 我现在这种写法 是可以优化的!!!!!!!!!!!!
    //      visited 数组 是可以完全去掉的,
    //      因为这题目 清0这个操作就类似 visited了
    //      而且不需要有什么改动, 删掉对应的代码就可以
    //      我现在这里写 只是说 让你去发现和其他的 图论题目  有个对应而已
    //
    void my_dfs_better(vector<vector<int>> &islandmap, vector<vector<bool>>& visited, int row, int col){
        //分别 代表 从当前idx
        // 往上, 所以 row-1
        // 往右, 所以 col+1
        // 往下, 所以 row+1
        // 往左, 所以 col-1
        vector<vector<int>> direction= {{-1,0},
                                        {0,1},
                                        {1,0},
                                        {0,-1}};

        // limit
        // 如果 这个被访问过, 或者他不是陆地, 则不进行下一步了


        // deal
        visited[row][col]=true;

        // for
        for(int i=0;i<=direction.size()-1;i++){
            int row_tmp = row + direction[i][0];
            int col_tmp = col + direction[i][1];

            if(0<=row_tmp && row_tmp<=islandmap.size()-1 && 0<=col_tmp && col_tmp<=islandmap[0].size()-1 ){
                // 水从高往地处流
                // 但是我们因为是从边缘出发, 找mountain peek
                // 所以 下一个位置 需要 比当前位置高
                // 这样到后面才能成为 mountain peek
                if(visited[row_tmp][col_tmp]!=true && islandmap[row][col]<=islandmap[row_tmp][col_tmp]){                                                 //与kamarcoder102不同!!!!!!!!!!!!!!!!!!!!!!!

                    visited[row_tmp][col_tmp]=true;                                                     // 立马标记!!!!!!!!!!!!!!!


                    //进一步搜索
                    my_dfs_better(islandmap, visited, row_tmp, col_tmp);

                }

            }
            else{
                //do nothing
            }

        }

        return ;
    }


    // 时间复杂度:O(n × m)
    //      外层双重循环遍历所有格子 O(n × m)
    //          因为 有类似的 visited数组 去重思想 的方式 所以 保证 每个位置不能 重复的往下 dfs
    // 空间复杂度:O(n × m)
    //      direction数组：O(1) - 固定大小4×2的数组
    //      递归调用栈：O(m × n) - 最坏情况下（比如整个网格都是连通的陆地），递归深度可能达到m×n
    //
    // +++++++++++++++++++++++++++++
    // 过程如下
    //      我们要沾着 上左 右下 两组边界来 玩搜索
    //          1. 上左  为边界A, 找出UL 的peeks
    //          2. 右下  为边界B, 找出DR 的peeks
    //            然后这两个 Peeks相交 得到的就是 能到双边界的 peeks
    vector<vector<int>> getMap_MountainPeeks_dfs(vector<vector<int>>& islandmap) {
        int row_num = islandmap.size();
        int col_num = islandmap[0].size();

        vector<vector<bool>> MountainPeeksTo_UL(row_num,vector<bool>(col_num,false));       //左上
        vector<vector<bool>> MountainPeeksTo_DR(row_num,vector<bool>(col_num,false));       //右下

        //初始化 一个 与islandmap 对应的visited数组 为 false
        //vector<vector<bool>> visited(row_num,vector<bool>(col_num,false));

        vector<vector<int>> rs;


        //----------------------我们要沾着 上下左右四个边界来 玩搜索 并且清零------------------------

        // 上下边 同时来, 融合在一起写,
        // 当然 你也可以分开写
        for(int j=0;j<=islandmap[0].size()-1;j++){

            // 上边界
            my_dfs_better(islandmap, MountainPeeksTo_UL, 0, j);

            // 下边界
            my_dfs_better(islandmap, MountainPeeksTo_DR, islandmap.size()-1, j);

        }

        // 左右边 同时来, 融合在一起写,
        // 当然 你也可以分开写
        for(int i=0;i<=islandmap.size()-1;i++){

            // 左边界
            my_dfs_better(islandmap, MountainPeeksTo_UL, i, 0);

            // 右边界
            my_dfs_better(islandmap, MountainPeeksTo_DR, i, islandmap[0].size()-1);


        }
        //--------------------------------------------------------------------



        for(int i=0;i<=islandmap.size()-1;i++){
            for (int j = 0; j <= islandmap[0].size()-1; j++) {
                if(MountainPeeksTo_UL[i][j]&&MountainPeeksTo_DR[i][j]==true){
                    rs.push_back({i,j});
                }
            }
        }


        return rs;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();

    // 初始化 图
    vector<vector<int>> islandMapInts1 = solut1->init_IslandMap_ints();
    solut1->myOutput_VectorBvecBtBB(islandMapInts1, 0, islandMapInts1.size()-1);
    cout<<endl;

    // 开始
    vector<vector<int>>  rs1 = solut1->getMap_MountainPeeks_dfs(islandMapInts1);


    cout<<"result"<<endl;
    //cout<<rs1<<endl;
    solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


