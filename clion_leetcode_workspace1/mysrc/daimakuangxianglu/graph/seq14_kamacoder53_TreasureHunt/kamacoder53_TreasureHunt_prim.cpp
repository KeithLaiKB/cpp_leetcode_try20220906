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
 * 在世界的某个区域，有一些分散的神秘岛屿，每个岛屿上都有一种珍稀的资源或者宝藏。国王打算在这些岛屿上建公路，方便运输。
 * 不同岛屿之间，路途距离不同，国王希望你可以规划建公路的方案，
 * 如何可以以最短的总公路距离将所有岛屿联通起来。
 *
 * 给定一张地图，其中包括了所有的岛屿，以及它们之间的距离。以最小化公路建设长度，确保可以链接到所有岛屿。
 *
 * 输入:
 * 第一行包含两个整数V和E，V代表顶点数，E代表边数。顶点编号是从1到V。例如：V=2，一个有两个顶点，分别是1和2。
 * 接下来共有E行，每行三个整数v1，v2和val，v1和v2为边的起点和终点，val代表边的权值。
 *
 *
 * 输出:
 *  输出输出联通所有岛屿的最小路径总距离
 *
 *
 *
 * 例如
 * 7 11   也就是7个节点   11条边
 * 1 2 1
 * 1 3 1
 * 1 5 2
 * 2 6 1
 * 2 4 2
 * 2 3 2
 * 3 4 1
 * 4 5 1
 * 5 6 2
 * 5 7 1
 * 6 7 1
 *
 *
 *
 *
 *
 *
 * 注意这里是无向图

                    (1)  ------ 1 ------ (2)
                     |                    |
                     |                    |            5
                     1                    2
                     |                    |
                     |                    |
                    (3)  ------ 1 ------ (4)




 *
 * 邻接矩阵

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

    template <typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }




    // 他虽然也是 二维数组
    // 但他并不是邻接矩阵,
    // 因为临界矩阵 里面的含义是
    // 从 x 到 y 点 是否可达, 然后这里还带有权重
    //  无向图的 邻接矩阵 那么 如果说2到5 权重是3，
    //      那么graph[2][5] 和 graph[5][2] 都要填写3
    vector<vector<int>> init_undirectedGraph_ints(int nodes_n, int edge_m, vector<vector<int>> edges_with_weight){

        //创建 邻接矩阵
        vector<vector<int>> adjMatrix1 (nodes_n+1, vector<int>(nodes_n+1,INT_MAX));

        // 打个比方 例如 我们用 INT_MAX 表示他们不连通, a为了好看 所以用a 代表INT_MAX
        // 我们可以看到这个邻接矩阵 是跟以前普通的不同,
        // 他们不连接的位置 不使用0
        //      而使用INT_MAX来代替
        // idx/idx  0    1    2    3    4    5
        //  0       a    a    a    a    a    a
        //  1       a    a    1    1    a    a
        //  2       a    1    a    a    2    a
        //  3       a    1    a    a    a    3
        //  4       a    a    2    a    a    4
        //  5       a    a    a    3    4    a
        //
        // 开始
        // 根据 console 进来的参数 进行 邻接矩阵的 填写
        for(int i=0;i<=edge_m-1;i++){
            int node1=edges_with_weight[i][0];
            int node2=edges_with_weight[i][1];
            int wgt=edges_with_weight[i][2];

            //
            //  无向图的 邻接矩阵 那么 如果说2到5 权重是3，
            //      那么graph[2][5] 和 graph[5][2] 都要填写3
            adjMatrix1[node1][node2] = wgt;
            adjMatrix1[node2][node1] = wgt;
        }

        return adjMatrix1;
    }



    // 根据已有的邻接矩阵 来弄
    int prim(vector<vector<int>>& graph, int node_n, int& rs_totalweight, vector<int> &rs_parent) {
        // 假设有100个数字 则 需要101
        // 因为100个数字 意味着 也可能需要 100, 那么idx就需要有100，
        // 所以才是 node_n+1
        vector<int> minDist(node_n+1, INT_MAX);

        vector<bool> judgeInTree(node_n+1, false);

        vector<int> parent(node_n+1, -1);

        // 从节点1开始
        minDist[1] = 0;
        int totalWeight = 0;

/*
 *      不按照代码狂想路来, 他那个有点tricky
 *      // 注意 我们这里的i 是从1开始, 因为0应该是不用的
        // 然后你可能问 我们明明有 node_n +1 的size,
        //      为什么 还要 node_n +1 -1 -1
        //          因为 我们总体看 我们要看的是那 一共有100个点
        //          而不是我们所谓的vector 的size
        //              那么 我们只有 100-1 条边
        //
        // 开始搞边, 因为我们prim这个最小生成树 肯定是不会重复走的, 不然 就不是最小生成树了
        // 因此 总体 只需要 遍历  总结点数-1 个边数就可以了*/


        // 我们有node_n 个节点
        // 我们每个节点都要查, 那就运行 node_n 次
        // 这里的 i 不参与 里面的任何操作, 只运行 node_n 次
        //      也就是说 每个点 都要插进树里
        //              并且每次插进去 都要更新一次 每个点离这个棵树的距离
        for(int i=1;i<=node_n;i++){


            int idx_node_toadd = -1;

            // 1. 找出需要add的那个node
            // 遍历端点 1~node_n
            //
            // 当整个程序 第一次来这时,
            //      idx=1的 node 还没进 树
            //      所以这个for 结束时, idx_node_toadd = 1
            //          因为例如 minDist[1]=0 < minDist[2]=INT_MAX
            for(int j=1;j<=node_n;j++){


                // 为什么要这么写这个判断, 因为 不单独拿出来 做第一次符合规则 的初始化
                // 会导致 下面那个判断 minDist[i] < minDist[idx_node_toadd] 出现越界
                if(judgeInTree[j]==false && idx_node_toadd == -1){
                    idx_node_toadd = j;
                }
                //                                  minDist[1]=0 < minDist[2]=INT_MAX
                else if(judgeInTree[j]==false &&  minDist[j] < minDist[idx_node_toadd] ){
                    idx_node_toadd = j;
                }
            }

            //2. 把找出来的node 放进tree里
            //   并且更新 去增加权重(因为树里有新节点了)
            //   idx=1 不用担心, minDist[1]为0
            judgeInTree[idx_node_toadd]=true;
            totalWeight = totalWeight + minDist[idx_node_toadd];


            //3. idx_node_toadd 进树以后
            //      还要把其他点 离这个树的距离进行更新
            //      也就是对 graph[idx_node_toadd][j] 这一行 进行搜寻
            //          情况一: 某个点原来 和这个树的距离 没办法直接相连,
            //                  但是现在 树 加了 这个点了以后, 可以直接相连了
            //          情况二: 某个点原来 和这个树的距离 相连, 但是 加了这个点以后
            //                  某个点 因为这个 新加的点 离这个树 更近了
            //          情况三: 某个点原来 和这个树的距离 相连, 但是 加了这个点以后,
            //                  并没有 离这个树更近, 也就是保持不变
            for(int j=1;j<=node_n;j++){

                // 如果 情况一 和 情况二,
                //      则需要更新 某个点 到这个树的距离
                //      并且 更新 某个点 的parent (因为是这个点 使得 某个点离这颗树更近了, 所以选择更好的parent)
                if(judgeInTree[j]==false && graph[idx_node_toadd][j] < minDist[j]){

                    minDist[j] = graph[idx_node_toadd][j];      // 更新 遍历的点 到树的最小距离

                    parent[j]= idx_node_toadd;                  // 更新 遍历的点 的parent 是哪个
                }

            }
        }

        rs_totalweight = totalWeight;
        rs_parent = parent;             // vector 拷贝赋值


        //myOutput_VectorBtB(minDist, 0, minDist.size()-1);
        return 0;
    }







};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();

    int node_n =7;              //记得要跟下面的edges 中的内容一起改变
    //int edge_m = 4;
    vector<vector<int>> edges = {
            {1, 2, 1},
            {1, 3, 1},
            {1, 5, 2},
            {2, 6, 1},
            {2, 4, 2},
            {2, 3, 2},
            {3, 4, 1},
            {4, 5, 1},
            {5, 6, 2},
            {5, 7, 1},
            {6, 7, 1}
    };


    vector<int> rs_parent;              //默认初始化
    int rs_weight=0;

    // 初始化 图
    vector<vector<int>> undirectedGraphInts1 = solut1->init_undirectedGraph_ints(node_n,edges.size(), edges);
    solut1->myOutput_VectorBvecBtBB(undirectedGraphInts1, 0, undirectedGraphInts1.size()-1);
    cout<<endl;

    // 开始
    solut1->prim(undirectedGraphInts1,node_n,rs_weight,rs_parent);


    cout<<"result"<<endl;
    cout<<rs_weight<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    solut1->myOutput_VectorBtB(rs_parent, 0, rs_parent.size()-1);
    return 0;
}

