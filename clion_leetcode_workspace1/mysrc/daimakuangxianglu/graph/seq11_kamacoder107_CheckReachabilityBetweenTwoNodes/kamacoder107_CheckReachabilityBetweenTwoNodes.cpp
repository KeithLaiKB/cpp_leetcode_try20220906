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
 * 给定一个包含 n 个节点的 无向图 中，节点编号从 1 到 n （含 1 和 n ）。
 * 你的任务是判断是否有一条从节点 source 出发到节点 destination 的路径存在。
 *
 * 输入:
 * 第一行包含两个正整数 N 和 M，N 代表节点的个数，M 代表边的个数。
 * 后续 M 行，每行两个正整数 s 和 t，代表从节点 s 与节点 t 之间有一条边。
 * 最后一行包含两个正整数，代表起始节点 source 和目标节点 destination。
 *
 *
 * 输出:
 *  输出一个整数，代表是否存在从节点 source 到节点 destination 的路径。如果存在，输出 1；否则，输出 0。
 *
 *
 *
 * 例如
 * 5 4   也就是4个节点   4条边
 * 1 2
 * 1 3
 * 2 4
 * 3 4
 * 1 4
 *
 *
 *
 *
 *
 *
 * 注意题目中说的是 无向图(undirected graph)

                     1  --------   2
                     |             |
                     |             |            5
                     |             |
                    3  ----------- 4




 *
 * 结果:
 * 1
 * 因为
 *  从节点1 可以走到 里面的所有节点
 * 成功返回 1 不成功返回-1
 *
 *
 * 简单的说:
 *      做这道题 并没有什么特别 说查询 reachability的 难度
 *
 *      它考察重点 是从 0 开始写代码
 *
 * 就是说
 *      1. 根据输入参数 写出一个并查集                           (主要是这个位置)
 *      2. 再 从我们建立好的 并查集 找出 这两个点 是否 连通
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
            // 比如 会出现这种 里面有空的情况 {{1}，{1,2},{},{4,5,6}}
            if (vec_tmp.empty()==true){
                cout<<"this is empty element(row)"<<endl;
                continue;
            }

            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<vec_tmp[j]<<"\t";
            }
            cout<<endl;
        }
    }


    template <typename T>
    void myOutput_VectorBlistBtBB(vector<list<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            list<T> vec_tmp = nums[i];
            for(int &num: vec_tmp){
                cout<<num<<"\t";
            }
            cout<<endl;
        }
    }

    //--------------------构建 并查集 ------------------------------
    vector<int> init_disjointFindUnion_vector_ints(int node_n){
        vector<int> father(node_n+1,0);

        //初始化的时候 默认所有节点 都是独立的
        //所以father都指向自己
        for(int i=0;i<=node_n;i++){
            father[i]=i;
        }

        return father;
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
    // 稍微说一下 那个vector<int> 不能叫 root 只能叫father,
    //      虽然 可以通过father 一直往上找 找到root,
    //      但是 那个数组 只指向他们直接的father
    // 这里我们是一直往上找 所以我这里 显示说明是找root的
    int findRoot(vector<int> &father, int num){
        if(num==father[num]){
            return num;
        }
        else{
            int root = findRoot(father, father[num]);
            father[num] = root;                                 //每次find 都会优化 也就是压缩路径, 这个位置是非常重要的!!!!!!!!!!!!!!!!!!!!!!!

            return root;
        }

    }

    // 如果根不相同, 则把v的根 放在 u的根的 下方
    void join(vector<int> &father,int u, int v){
        int root_u = findRoot(father, u);
        int root_v = findRoot(father, v);

        if(root_u == root_v){
            return;
        }

        //注意这里 不是简单的就 u 和 v连接,
        // 而是 他们的root  相连接
        father[root_v] = root_u;
    }

    //--------------------------------------------


    // 时间复杂度：
    //      O(α(n))（调用两次findRoot）
    // 空间复杂度：O(h)
    //      （findRoot的递归栈）

    bool judgeRootSame(vector<int> &father,int u, int v){
        int root_u = findRoot(father, u);
        int root_v = findRoot(father, v);

        return root_u==root_v;
    }
    //--------------------------------------------


    int prepare_disjointFindUnion_vector_ints(vector<vector<int>> edges, vector<int>& father){

        //初始化的时候 默认所有节点 都是独立的
        //所以father都指向自己
        for(int i=0;i<=edges.size()-1;i++){
            join(father, edges[i][0], edges[i][1]);
        }

        return 1;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();

    // 初始化 图
    vector<vector<int>> edges = {{1,2},{1,3},{2,4},{3,4}};
    int node_n =5;
    int edge_m = 4;

    int node1 = 1;
    int node2 = 4;

/*    // -------------------因为从题目来看 它给的 node_n=5 证明 最大的数字 有5 在edges 里是没有出现过的 我们要求出最大的值， 从而知道 father要设置多大----------------------
    int node_num=INT_MIN;

    for(int i=0;i<=edges.size()-1;i++){
        node_n = edges[i][0] > node_num? edges[i][0] : node_num;
        node_n = edges[i][1] > node_num? edges[i][0] : node_num;
    }

    node_n = node_n > node_num? node_n : node_num;
    // --------------------------------------------------------------------------------------------------------------*/

    vector<int> father1 = solut1->init_disjointFindUnion_vector_ints(node_n);       //每个独立元素 都init一下
    solut1->prepare_disjointFindUnion_vector_ints(edges,father1);                           // 根据题目已知 建立好那个已知的 并查表
    //solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);

    // 我这里 就把 最后的那个 点 当作 终点好了,
    //      例如 我们有 1~5 个node, 我们实际会有 5+1个空间,
    //          我这里打算 把 5 当作终点
    //      因为 本题我们会有n 个节点，因为节点标号是从1开始的，为了节点标号和下标对齐，我们申请 n + 1 * n + 1 这么大的二维数组。
    // 当然 你也可以改终点
    //int dest_node = adjacencyList1.size()-1;
    int rs1 = solut1->judgeRootSame(father1,node1,node2);



    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


