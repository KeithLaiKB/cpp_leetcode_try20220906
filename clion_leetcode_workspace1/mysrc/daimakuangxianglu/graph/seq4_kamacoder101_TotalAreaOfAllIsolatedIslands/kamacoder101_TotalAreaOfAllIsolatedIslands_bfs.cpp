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
 *  输出一个整数，表示所有孤岛的总面积，如果不存在孤岛，则输出 0。
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
    void my_bfs_better(vector<vector<int>> &islandmap, vector<vector<bool>>& visited, int row, int col){
        //分别 代表 从当前idx
        // 往上, 所以 row-1
        // 往右, 所以 col+1
        // 往下, 所以 row+1
        // 往左, 所以 col-1
        vector<vector<int>> direction= {{-1,0},
                                        {0,1},
                                        {1,0},
                                        {0,-1}};

        //         row,col
        // 其实和树的那个interation的 层序遍历有点像, 我这里名字 就跟他靠拢好了 q_root
        queue<pair<int,int>> q_root;                                            // 和 dfs 写法不一样!!!!!!!!!!!!!!!!!!!!!!!

        //放入当前节点
        q_root.push(pair<int,int>(row,col));                            // 和 dfs 写法不一样!!!!!!!!!!!!!!!!!!!!!!!


        // deal something before for
        // islandmap[row][col]=0;                                                  // 当然我们这样写也行, 但他也就只给最外面的入口有用,
                                                                                   // 因为我们走的是 立马标记的 风格, 所以我们已经提到外面的入口处了


        while(!q_root.empty()){                                                 // 和 dfs 写法不一样!!!!!!!!!!!!!!!!!!!!!!!
            pair<int,int> now_node = q_root.front();
            q_root.pop();

            int now_row = now_node.first;
            int now_col = now_node.second;

            // ---------------------里面这一部分 和 dfs 比较一致------------------------------------
            // 做 隐藏的limit


            // for
            for(int i=0;i<=direction.size()-1;i++){
                int row_tmp = now_row + direction[i][0];
                int col_tmp = now_col + direction[i][1];

                if(0<=row_tmp && row_tmp<=islandmap.size()-1 && 0<=col_tmp && col_tmp<=islandmap[0].size()-1 ){

                    if(visited[row_tmp][col_tmp]!=true && islandmap[row_tmp][col_tmp]!=0){
                        q_root.push(pair<int,int>(row_tmp,col_tmp));        // 和 dfs 写法不一样!!!!!!!!!!!!!!!!!!!!!!!
                        // deal
                        visited[row_tmp][col_tmp]=true;                              // 立马标记!!!!!!!!!!!!!!!

                        //----------岛屿面积处理---------------
                        islandmap[row_tmp][col_tmp]=0;                                                       // 清零
                        //-----------------------------------
                    }

                }
                else{
                    //do nothing
                }

            }
            // -----------------------------------------------------------------------


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
    int countTotalAreaOfAllIsolatedIslands_bfs(vector<vector<int>>& islandmap) {
        int row_num = islandmap.size();
        int col_num = islandmap[0].size();

        //初始化 一个 与islandmap 对应的visited数组 为 false
        vector<vector<bool>> visited(row_num,vector<bool>(col_num,false));

        int rs_area=0;


        //----------------------我们要沾着 上下左右四个边界来 玩搜索 并且清零------------------------

        // 上下边 同时来, 融合在一起写,
        // 当然 你也可以分开写
        for(int j=0;j<=islandmap[0].size()-1;j++){

            // 上边界
            if(islandmap[0][j]==1){

                //----------岛屿面积处理---------------
                islandmap[0][j]=0;                                                       // 清零当前入口
                //-----------------------------------

                my_bfs_better(islandmap, visited, 0, j);

            }

            // 下边界
            if(islandmap[islandmap.size()-1][j]==1){

                //----------岛屿面积处理---------------
                islandmap[islandmap.size()-1][j]=0;                                      // 清零当前入口
                //-----------------------------------

                my_bfs_better(islandmap, visited, islandmap.size()-1, j);

            }
        }

        // 左右边 同时来, 融合在一起写,
        // 当然 你也可以分开写
        for(int i=0;i<=islandmap.size()-1;i++){

            // 左边界
            if(islandmap[i][0]==1){

                islandmap[i][0]=0;                                                       // 清零当前入口

                my_bfs_better(islandmap, visited, i, 0);

            }

            // 右边界
            if(islandmap[i][islandmap[0].size()-1]==1){

                islandmap[i][islandmap[0].size()-1]=0;                                   // 清零当前入口

                my_bfs_better(islandmap, visited, i, islandmap[0].size()-1);

            }
        }
        //--------------------------------------------------------------------


        //---------------------- 剩下的1 都是孤岛, 直接累加就是答案 ------------------------
        //
        for(int i=0;i<=islandmap.size()-1;i++){
            for (int j = 0; j <= islandmap[0].size()-1; j++) {
                if(islandmap[i][j]==1){
                    ++rs_area;
                }
            }
        }

        //展示清零后的样子
        myOutput_VectorBvecBtBB(islandmap, 0, islandmap.size()-1);

        return rs_area;
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
    int rs1 = solut1->countTotalAreaOfAllIsolatedIslands_bfs(islandMapInts1);


    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


