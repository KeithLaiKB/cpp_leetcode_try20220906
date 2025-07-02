#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>
#include <map>
#include <unordered_set>

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
 *      1. 把所有的岛屿 进行 搜索(dfs/bfs), 然后把地图上的每一个格子都做成 编号
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
 *      2. 遍历所有 海水格子
 *              查询他们上下左右 有没有 直接 相接壤的岛 (这一步不需要dfs/bfs)
 *              如果有就加起来return
 *                  并查看是否成为最大的面积
 *
 *     结束
 *
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
 *  你看如果从 1 和 0 开始标号这些岛屿return
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
        return;
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
    int my_dfs_better(vector<vector<int>> &islandmap, int row, int col, int island_id){
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
        int count_area=0;

        // for
        for(int i=0;i<=direction.size()-1;i++){
            int row_tmp = row + direction[i][0];
            int col_tmp = col + direction[i][1];

            if(0<=row_tmp && row_tmp<=islandmap.size()-1 && 0<=col_tmp && col_tmp<=islandmap[0].size()-1 ){
                // 水从高往地处流
                // 但是我们因为是从边缘出发, 找mountain peek
                // 所以 下一个位置 需要 比当前位置高
                // 这样到后面才能成为 mountain peek
                if(islandmap[row_tmp][col_tmp]==1){                                                 // 如果是1 并且 还没打上 岛屿的记号island_id,
                                                                                                    // 这就代表它没有 visited过, 这样 可以代替掉visited数组的作用

                    islandmap[row_tmp][col_tmp]=island_id;

                    ++count_area;           //加上当前面积块
                    //进一步搜索
                    count_area += my_dfs_better(islandmap, row_tmp, col_tmp, island_id);

                }

            }
            else{
                //do nothing
            }

        }

        return count_area;
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
    int getLargestIslandAfterOneFlip_dfs(vector<vector<int>>& islandmap) {
        //int row_num = islandmap.size();
        //int col_num = islandmap[0].size();

        unordered_map<int,int> unordmap_id_area;
        vector<vector<int>> direction= {{-1,0},
                                        {0,1},
                                        {1,0},
                                        {0,-1}};


        //初始化 一个 与islandmap 对应的visited数组 为 false
        //vector<vector<bool>> visited(row_num,vector<bool>(col_num,false));

        int max_area=INT_MIN;
        int island_id = 2;                  //从2开始, 因为要在地图上改写1 变成组编号, 以免 和地图 上的0和1相冲突


        bool judgeAllGrid = true;           // 标记是否整个地图都是陆地, 因为如果全是陆地的话, 他就没办法flip, 也进行不了 面积的累加的步骤了

        //---------------------- 第一步 用dfs/bfs 给所有的 岛做标记 ------------------------

        for(int i=0;i<=islandmap.size()-1;i++){
            for(int j=0;j<=islandmap[0].size()-1;j++){



                if(islandmap[i][j]==1){                                                 // 如果是1 并且 还没打上 岛屿的记号island_id,

                    islandmap[i][j] = island_id;                            //立马打标记
                    int now_area = 1;                                       //入口位置, 立马把当前面积初始为1

                    now_area += my_dfs_better(islandmap, i, j, island_id);

                    unordmap_id_area.insert(pair<int,int>(island_id,now_area));      // 记录每个岛屿编号 对应的面积的大小

                    ++island_id;
                }

                // 如果含有海, 那么他就不是全陆地, 其实 不用太去管这个逻辑, 这个不参与我们的 dfs,
                // 他就是类似一个全地图都是陆地 则不需要dfs
                if(islandmap[i][j]==0){
                    judgeAllGrid = false;
                }

            }
        }
        //--------------------------------------------------------------------
        myOutput_VectorBvecBtBB(islandmap,0,islandmap.size()-1);
        //---------------------- 第二步 给所有的 海格子 进行flip ------------------------

        //        2 0 2 0 0 0
        //        2 2 2 0 3 0
        //        0 0 0 0 0 0
        // 我们可以看到 上面 这个被2包围的0
        // 我们需要一个 visitedIslandId 来记录 本次访问过的 island id
        // 不然 面积累加的时候  会重复把这个2的岛屿加进去
        unordered_set<int> uordset_visitedIslandId;           //记录本次格子, 查询上下左右, 查完重新清0


        //如果全是陆地, 提前结束
        if(judgeAllGrid==true){
            return islandmap.size()*islandmap[0].size();
        }


        // 开始搜索海格子
        for(int i=0;i<=islandmap.size()-1;i++){
            for(int j=0;j<=islandmap[0].size()-1;j++){

                // 如果不是海则跳过, 因为我们要flip海格子
                if (islandmap[i][j]!=0){
                    continue;
                }


                int now_area =1;        //当前这个flip的本身
                uordset_visitedIslandId.clear();    //新的海格子, 周围还没查过, 所以要清空


                //遍历 直接 的上下左右 位置
                for(int k=0;k<=direction.size()-1;k++){

                    int row_tmp=i+direction[k][0];
                    int col_tmp=j+direction[k][1];


                    //以免越界
                    if(0<=row_tmp && row_tmp<=islandmap.size()-1 && 0<=col_tmp && col_tmp<=islandmap[0].size()-1 ){

                        // 如果 当前这个相邻的节点 是海 就不用管了
                        if(islandmap[row_tmp][col_tmp]==0){
                            continue;
                        }



                        int id_tmp = islandmap[row_tmp][col_tmp];       //查看当前这个相邻的 有id

                        //那个节点 的上下左右 已经有过当前 islandID了
                        // 这里就不要重复 累加面积了
                        if(uordset_visitedIslandId.find(id_tmp)!=uordset_visitedIslandId.end()){
                            continue;
                        }


                        now_area += unordmap_id_area[id_tmp];                //累加这个岛的面积
                        uordset_visitedIslandId.insert(id_tmp);


                    }
                }

                if (now_area>max_area){
                    max_area = now_area;
                }


            }
        }


        //--------------------------------------------------------------------


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
    cout<<endl;

    // 开始
    int  rs1 = solut1->getLargestIslandAfterOneFlip_dfs(islandMapInts1);


    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


