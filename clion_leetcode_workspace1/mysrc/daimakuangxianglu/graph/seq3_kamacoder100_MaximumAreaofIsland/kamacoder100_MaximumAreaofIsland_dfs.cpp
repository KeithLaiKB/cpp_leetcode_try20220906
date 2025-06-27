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
 * 给定一个由 1（陆地）和 0（水）组成的矩阵，你需要计算岛屿的数量。岛屿由水平方向或垂直方向上相邻的陆地连接而成，并且四周都是水域。你可以假设矩阵外均被水包围。
 *
 * 输入:
 * 第一行包含两个整数 N, M，表示矩阵的行数和列数。
 * 后续 N 行，每行包含 M 个数字，数字为 1 或者 0。
 *
 *
 * 输出:
 *  输出一个整数，表示岛屿的最大面积。如果不存在岛屿，则输出 0。
 *
 *
 *
 *  4 5
 *  于是有
 *  1 1 0 0 0
 *  1 1 0 0 0
 *  0 0 1 0 0
 *  0 0 0 1 1
 *
 * 例如这个 最大的面积的岛屿 的面积是 4
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






    // 其实你可以看到 这个dfs 写法很像回溯 但是他是没有那个 pop的
    //
    // row 和 col 从0开始
    void my_dfs(const vector<vector<int>> &islandmap, vector<vector<bool>>& visited, int row, int col, int &now_area, int& max_area){
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
        if(visited[row][col]==true || islandmap[row][col]==0){
            return ;
        }

        // deal
        visited[row][col]=true;

        //----------岛屿面积处理---------------
        ++now_area;                                                                         // 岛屿面积+1
        if(now_area>max_area){
            max_area = now_area;
        }
        //-----------------------------------

        // for
        for(int i=0;i<=direction.size()-1;i++){
            int row_tmp = row + direction[i][0];
            int col_tmp = col + direction[i][1];

            if(0<=row_tmp && row_tmp<=islandmap.size()-1 && 0<=col_tmp && col_tmp<=islandmap[0].size()-1 ){
                my_dfs(islandmap, visited, row_tmp, col_tmp, now_area, max_area);
            }
            else{
                //do nothing
            }

        }

        return ;
    }

    // 1 1
    // 1 0
    //
    // 这种情况 去用回溯的pop now_area 是不行的
    // 你可以看到这样算法, 他结果其实是2,
    //      就算是 [0,1] 那个地方 他也 到不了[1,0]
    //      因为 还是要从[0,0]出发
    // 然后最外层循环 只要没visited 过都是起始为1或者0起步
    // 因此这种并不是回溯
    //
    //
    //这个就是虽然 不是那么好理解 甚至不太像回溯(当然也不是回溯, 写成像回溯只是说为了好背)
    //但这种写法不容易超时
    void my_dfs_better(const vector<vector<int>> &islandmap, vector<vector<bool>>& visited, int row, int col, int &now_area, int& max_area){
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
                if(visited[row_tmp][col_tmp]!=true && islandmap[row_tmp][col_tmp]!=0){
                    visited[row_tmp][col_tmp]=true;                                                     // 立马标记!!!!!!!!!!!!!!!

                    //----------岛屿面积处理---------------
                    ++now_area;                                                                         // 岛屿面积+1
                    if(now_area>max_area){
                        max_area = now_area;
                    }
                    //-----------------------------------

                    my_dfs_better(islandmap, visited, row_tmp, col_tmp,now_area,max_area);


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
    //      visited数组：O(m × n) - 存储每个格子的访问状态
    //      direction数组：O(1) - 固定大小4×2的数组
    //      递归调用栈：O(m × n) - 最坏情况下（比如整个网格都是连通的陆地），递归深度可能达到m×n
    //
    // +++++++++++++++++++++++++++++
    // 过程如下
    // 就是一个深搜, 从初始这个点出发
    //      如果当前这个点不是海 并且 没搜过
    //              搜到 周围都没得搜了,
    //              那么刚才搜的区域  就自成一片, 也就是岛屿+1
    // 然后往后看每个点
    //      如果当前这个点不是海 并且 没搜过, 于是做 同样的操作 从这个点出发
    //          搜到 周围都没得搜了,
    //              那么刚才搜的区域  就自成一片, 也就是岛屿+1
    int maxAreaOfIsland_dfs(vector<vector<int>>& islandmap) {
        int row_num = islandmap.size();
        int col_num = islandmap[0].size();

        //初始化 一个 与islandmap 对应的visited数组 为 false
        vector<vector<bool>> visited(row_num,vector<bool>(col_num,false));

        //int rs =0;
        int now_area=0;
        int max_area=0;

        for(int i=0;i<=islandmap.size()-1;i++){
            for (int j = 0; j <= islandmap[0].size()-1; j++) {
                if(visited[i][j]==false && islandmap[i][j]==1){

                    //----------岛屿面积处理---------------

                    //now_area=0;       //如果用my_dfs, 则用这个
                    now_area=1;         //如果用my_dfs_better, 则用这个
                    if(now_area>max_area){
                        max_area = now_area;
                    }

                    //-----------------------------------

                    //my_dfs(islandmap, visited, i, j,now_area,max_area);
                    my_dfs_better(islandmap, visited, i, j,now_area,max_area);


                }

            }
        }
        return max_area;
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

    // 开始
    int rs1 = solut1->maxAreaOfIsland_dfs(islandMapInts1);


    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


