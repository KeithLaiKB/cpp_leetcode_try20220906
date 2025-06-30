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
 * 给定一个由 1（陆地）和 0（水）组成的矩阵，你最多可以将矩阵中的一格水变为一块陆地，在执行了此操作之后，矩阵中最大的岛屿面积是多少。
 *
 * 岛屿面积的计算方式为组成岛屿的陆地的总数。岛屿是被水包围，并且通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设矩阵外均被水包围
 *
 *
 * 输入:
 * 第一行包含两个整数 N 和 M，分别表示矩阵的行数和列数。
 * 后续 N 行，每行包含 M 个整数，表示矩阵中的每个单元格的高度。
 *
 *
 * 输出:
 *  输出一个整数，表示最大的岛屿面积。
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
 * 简单说就是:
 *      计算并得到出 把其中哪一个海区域 变成陆地,
 *      能够使得 这整副地图中 获得一个最大面积的岛
 *          因为这个翻转 有可能 能使得 附近几个岛 相连接
 *          从而获得一个 超级大的面积的岛
 *      找到 新生成能够成为的最大面积 的方案
 *      并返回这个 最大面积 的值
 *
 *      1. 把所有的岛屿 进行 搜索, 然后把地图上的每一个格子都做成 编号
 *              例如 第一个 岛屿 里的 所有格子 从1 改成2
 *              例如 第二个 岛屿 里的 所有格子 从1 改成3
 *              因为我们要改的是地图
 *                  本身0 就代表海洋了
 *                  1    就代表将要被flip的格子
 *                  所以  地图上为了防止和他们冲突, 只能从 2开始
 *
 *              注意我们这个地图上的 2,3,4,5 不代表 这个岛屿的面积, 而是编号
 *                  面积会有 map来存储
 *
 *
 * 例如:
 *  1 0 0 0 0 0 0
 *  0 0 1 1 0 0 0
 *  1 1 0 0 1 0 0
 *  0 1 0 1 0 0 0
 *  0 1 0 1 1 0 0
 *
 *  变成
 *  2 0 0 0 0 0 0
 *  0 0 3 3 0 0 0
 *  4 4 0 0 5 0 0
 *  0 4 0 6 0 0 0
 ×  0 4 0 6 6 0 0
 *
 *  你看如果从 1 和 0 开始标号这些岛屿
 *  就会和 上面的 海水 和 将要flip的区域 其冲突了
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
    //          因为 visited数组 保证 每个位置不能 重复的往下 dfs
    // 空间复杂度:O(n × m)
    //      direction数组：O(1) - 固定大小4×2的数组
    //      递归调用栈：O(m × n) - 最坏情况下（比如整个网格都是连通的陆地），递归深度可能达到m×n
    //
    // +++++++++++++++++++++++++++++
    // 过程如下
    //      我们要沾着 上下左右四个边界来 玩搜索,
    //      把所有沾边的岛屿全部清零
    //      从而留下的1 就是孤岛
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


