#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>
#include <list>
#include <algorithm>


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



    //--------------------构建 并查集 ------------------------------
    vector<int> init_disjointFindUnion_vector_ints(int node_n){
        vector<int> parent(node_n+1,0);

        //初始化的时候 默认所有节点 都是独立的
        //所以parent都指向自己
        for(int i=0;i<=node_n;i++){
            parent[i]=i;
        }

        return parent;
    }
    // 单次最坏时间复杂度：O(n)（第一次查找链式结构）
    // 摊还时间复杂度：O(α(n))（阿克曼函数的反函数）
    // 空间复杂度：O(h)（递归栈，h是树高度）
    //
    // 虽然不是 学术上说的的dfs
    //      毕竟每次find都是有可能要做 链路压缩
    // 但是实现的类型是非常像dfs的
    //
    // 找出num的 root 在哪
    // 稍微说一下 那个vector<int> 不能叫 root 只能叫parent,
    //      虽然 可以通过parent 一直往上找 找到root,
    //      但是 那个数组 只指向他们直接的parent
    // 这里我们是一直往上找 所以我这里 显示说明是找root的
    int findRoot(vector<int> &parent, int num){
        if(num==parent[num]){
            return num;
        }
        else{
            int root = findRoot(parent, parent[num]);
            parent[num] = root;                                 //每次find 都会优化 也就是压缩路径, 这个位置是非常重要的!!!!!!!!!!!!!!!!!!!!!!!

            return root;
        }

    }

    // 如果根不相同, 则把v的根 放在 u的根的 下方
    void join(vector<int> &parent,int u, int v){
        int root_u = findRoot(parent, u);
        int root_v = findRoot(parent, v);

        if(root_u == root_v){
            return;
        }

        //注意这里 不是简单的就 u 和 v连接,
        // 而是 他们的root  相连接
        parent[root_v] = root_u;
    }

    //--------------------------------------------


    // 时间复杂度：
    //      O(α(n))（调用两次findRoot）
    // 空间复杂度：O(h)
    //      （findRoot的递归栈）

    bool judgeRootSame(vector<int> &parent,int u, int v){
        int root_u = findRoot(parent, u);
        int root_v = findRoot(parent, v);

        return root_u==root_v;
    }
    //--------------------------------------------

    //对最后的权重进行排序
    bool static mycomp(const vector<int> &a, const vector<int> &b) {
        return a[2] < b[2];
    }

    // 上面的基本代码 和  kamacoder107 一样, 除了 这里用了 mycomp
    // 除了 这个方法 写的会有一些区别
    // 边添加新edge 边判断
    int prepare_disjointFindUnion_and_GetShortestPath(vector<vector<int>> edges, vector<int>& parent, int& rs_totalweight, vector<vector<int>>& rs_path){
        //vector<vector<int>> rs_path;        //路径

        sort(edges.begin(),edges.end(),mycomp);

        //连接两个点 形成边
        for(int i=0;i<=edges.size()-1;i++){
            //如果相同根
            if(judgeRootSame(parent,edges[i][0],edges[i][1])==true){
                //rs.push_back({edges[i][0],edges[i][1]});
                //break;
                continue;
            }
            //如果 不相同根
            else{
                rs_path.push_back({edges[i][0],edges[i][1]});
                rs_totalweight +=  edges[i][2];
                join(parent, edges[i][0], edges[i][1]);
            }

        }

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

    int rs_weight=0;
    vector<vector<int>> rs_shortest_path;

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
    //int rs_weight=0;

    vector<int> parent1 = solut1->init_disjointFindUnion_vector_ints(node_n);       //每个独立元素 都init一下

    // 初始化 图
    solut1->prepare_disjointFindUnion_and_GetShortestPath(edges,parent1,rs_weight,rs_shortest_path);                           // 根据题目已知 建立好那个已知的 并查表

    solut1->myOutput_VectorBvecBtBB(rs_shortest_path, 0, rs_shortest_path.size()-1);
    cout<<endl;




    cout<<"result"<<endl;
    cout<<rs_weight<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    solut1->myOutput_VectorBtB(rs_parent, 0, rs_parent.size()-1);
    return 0;
}

