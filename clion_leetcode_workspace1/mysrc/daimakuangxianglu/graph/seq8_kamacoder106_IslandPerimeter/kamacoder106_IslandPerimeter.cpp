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
 * 给定一个由 1（陆地）和 0（水）组成的矩阵，岛屿是被水包围，并且通过水平方向或垂直方向上相邻的陆地连接而成的。
 *
 * 你可以假设矩阵外均被水包围。在矩阵中恰好拥有一个岛屿，假设组成岛屿的陆地边长都为 1，请计算岛屿的周长。岛屿内部没有水域。
 *
 *
 * 输入:
 * 第一行包含两个整数 N, M，表示矩阵的行数和列数。
 * 之后 N 行，每行包含 M 个数字，数字为 1 或者 0，表示岛屿的单元格。
 *
 *
 * 输出:
 *  输出一个整数，表示岛屿的周长。
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
 *      指定 这个地图 只有一个岛屿, 且岛屿 包围区间内不可以掏空 放海格子
 *
 *
 *
 * 例如:
 *  0 0 0 0 0 0 0
 *  0 0 1 0 1 0 0
 *  0 0 1 1 1 0 0
 *  0 1 1 1 1 0 0
 *  0 0 0 1 1 0 0
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
    // 空间复杂度:O(1)
    //      direction 数组：固定大小 4×2，占用常数空间
    //      rs_perimeter、row_tmp、col_tmp 等变量：常数空间
    //
    // +++++++++++++++++++++++++++++
    // 过程如下
    //
    // 这里不需要做什么dfs/bfs
    // 直接对每个格子进行处理就可以了
    //
    // 针对每一个节点 对其上下左右看
    // 1. 如果 触碰到 海 (0)
    //          则边长+1
    // 2. 如果 触碰到 上边界
    //          则边长+1
    // 3. 如果 触碰到 右边界
    //          则边长+1
    // 4. 如果 触碰到 下边界
    //          则边长+1
    // 5. 如果 触碰到 左边界
    //          则边长+1
    //
    //  0 0 1 0 0 0 0
    //  0 0 1 1 1 0 0
    //  0 0 1 1 1 0 0
    //  例如 探测到 左上角 这个 1 节点时
    //      从该节点 上下左右 开始 探测
    //          1. 上边 触碰到上边界,  边+1
    //          1. 右边 触碰到海(0),  边+1
    //          1. 下边 触碰到岛屿(1), 边不做运算, 因为cover了 没有边
    //          1. 上边 触碰到海(0),  边+1
    int getIslandPerimeter(vector<vector<int>>& islandmap) {
        //int row_num = islandmap.size();
        //int col_num = islandmap[0].size();

        //map<int,int> map_id_area;
        vector<vector<int>> direction= {{-1,0},
                                        {0,1},
                                        {1,0},
                                        {0,-1}};

        int rs_perimeter = 0;


        // 我们是 按顺序 每个格子都搜查, 所以不需要什么visited数组
        for(int i=0;i<=islandmap.size()-1;i++){
            for (int j = 0; j <=islandmap[0].size()-1; j++) {

                //如果当前 是 海格子 就不用看了
                if(islandmap[i][j]==0){
                    continue;
                }

                for(int k=0;k<=direction.size()-1;k++){

                    int row_tmp= i + direction[k][0];
                    int col_tmp= j + direction[k][1];

                    //如果是边界 则 +1
                    if(row_tmp<0 || row_tmp > islandmap.size()-1 || col_tmp<0 || col_tmp > islandmap[0].size()-1){
                        ++rs_perimeter;
                    }
                    // 如果是海 +1
                    else if(islandmap[row_tmp][col_tmp]==0){
                        ++rs_perimeter;
                    }
                    else{
                        //do nothing
                    }
                }

                cout<<rs_perimeter<<endl;
            }
        }



        //--------------------------------------------------------------------


        return rs_perimeter;
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
    int  rs1 = solut1->getIslandPerimeter(islandMapInts1);


    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


