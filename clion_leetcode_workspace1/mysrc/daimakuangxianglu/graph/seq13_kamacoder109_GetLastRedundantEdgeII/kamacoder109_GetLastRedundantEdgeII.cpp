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
 * 本题涉及有向树, 有向树 只有一个根!!!!!!!!!!!!!!!!!!!!
 *
 * 有一种有向树,该树只有一个根节点，所有其他节点都是该根节点的后继。
 * 该树除了根节点之外的每一个节点都有且只有一个父节点，而根节点没有父节点。有向树拥有 n 个节点和 n - 1 条边
 *
 * 现在有一个有向图，有向图是在有向树中的两个没有直接链接的节点中间添加一条有向边
 *      因此 这题里 最大可能的度的情况 只有2
 *
 * 输入:
 *      第一行输入一个整数 N，表示有向图中节点和边的个数。
 *      后续 N 行，每行输入两个整数 s 和 t，代表这是 s 节点连接并指向 t 节点的单向边
 *
 * 输出
 *      输出一条可以删除的边，若有多条边可以删除，请输出标准输入中最后出现的一条边。
 *
 *
 * 例如
 * 5 4   也就是4个节点   4条边
 * 2 1
 * 1 4
 * 2 3
 * 3 5
 * 4 5
 *
 *
 *
 *
 *
 *
                                    2
                    |                               |
                    1                               3
            |               |               |               |
           4    ------------------------------------------  5

 *
 * 情况一(情况顺序 和代码狂想录不同 但涵盖的情况一样, 只是我这样的顺序 比较好理解)
 * 大家度数都为1 但是成环了
 * 删除最后加进来的边就可以了
 *
                                    1
                    |                               /\
                    |                               |
                   \/                               |
                    2  --------------------------> 3
 *
 * 情况二
 * 你会发现 3 这个 入度 的度数是 =2
 * 删除最后加进来的边就可以了
 *
                                    1
                    |                               |
                    |                               |
                   \/                              \/
                    2  --------------------------> 3

 *
 * 情况三
 * 你会发现 3 这个 入度 的度数是 =2
 * 但是 他肯定不能删除最后加进来 使得3度数为2的边 (3,4),
 * 因为这样的话 有向树 还是仍然有两个根,
 *      那就仍然不是 有向树
 *      所以不符合题目结果的要求
 *      也就是说 他不能像 kamacoder108那样简单的 找到 使得变成环的 最后一条边
 *
                                    1
                    /\                               |
                    |                               |
                    |                              \/
                    2  <-------------------------- 3  <-------------------------- 4
 *
 *
 * 注意 input里面的 每个pair里的顺序 是带有方向的!!!!!!!!!!!!!!!!!!!!:
 * 也就是说 在有向图中  我们join 当中  第一个数字 和第二个数字 是有方向 关系 不能搞反了
 *      第一个元素是parent, 第二个元素是child
 *      {{2,1},{1,3},{3,2},{4,3}}
 *
 * 我们是不需要考虑 度数=3的情况的
 *      因为题目说了 初始是一个有向树(所以入度不可能=2), 那就意味着最开始 不会存在 入度=2的情况
 *      然后加了一条边 才有可能造成 入度=2的情况
 *
 *
 * 操作如下
 * 1. 找到入度为2的所有边
 * 2. 从后往前遍历,也就是先遍历 最近后进来造成入度为2的边
 *          每次遍历 从0开始建立 并查集,
 *              用来判断 删除这个边 后所成的并查集 是否能成功
 *
 *
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
    //----------------------------------------------------------------------------------



    // ------------------------------情况 分类---------------------------------------------------

    // 情况一, 情况二 用的代码
    // 这部分代码 会和 之前的那些prepare 有些像
    // 只不过他这里 构造 并查集 最终不是为了 返回并查集
    // 而是返回 删除这个边后, 这个并查集 符不符合要求
    //
    // 流程:
    // 1. 如果是 要删除的边 则不放入
    // 2. 检查 是否形成的 并查集的 这个图 成环
    //      如果仍然成环 则证明删除的边无效
    //
    bool judgeTreeAfterRemoveEdge(const vector<vector<int>>& edges, int node_n, int idx_edgeToDelete) {
        // 从0开始建立并查集
        vector<int> parent = init_disjointFindUnion_vector_ints(node_n);

        bool rs = true;

        for(int i=0;i<=edges.size()-1;i++){

            //构造时不把边 加进来 就当于删除这个边
            // 不让这个边 在图里出现
            if(i == idx_edgeToDelete){
                continue;
            }
            else{
                // 一旦形成环了 就证明 删除那个边, 是没有用的
                // 因为删除了 还是有环
                if(judgeRootSame(parent,edges[i][0],edges[i][1])==true){
                    //rs.push_back({edges[i][0],edges[i][1]});
                    rs = false;
                    break;
                }
                else{
                    join(parent, edges[i][0], edges[i][1]);
                }
            }
        }

        return rs;
    }

    // 情况三 用的代码
    // 当入度只有1,且成环的情况
    // 这个代码 和以前的 prepare_disjointFindUnion_vector_ints 非常像,
    // 只是我们把 parent放这里面了
    vector<vector<int>> getRemoveEdge(const vector<vector<int>>& edges, int node_n) {

        vector<int> parent = init_disjointFindUnion_vector_ints(node_n);
        vector<vector<int>> rs;

        //连接两个点 形成边
        for(int i=0;i<=edges.size()-1;i++){
            //如果相同根
            if(judgeRootSame(parent,edges[i][0],edges[i][1])==true){
                rs.push_back({edges[i][0],edges[i][1]});
                break;
            }
            else{
                join(parent, edges[i][0], edges[i][1]);
            }

        }

        return rs;
    }
    //----------------------------------------------------------------------------------



    // 根据不同情况 调用 上方的 两块代码
    //
    // 1.先获取入度为2的边
    // 2. 根据情况删边
    vector<vector<int>> getLastRedundantEdgeII(vector<vector<int>> edges, int node_n){
        vector<vector<int>> rs;
        vector<int> inDegree(node_n+1,0);          //每个节点的入度

        vector<int> idx_edges_2indegree;            //使得入度为2的边

        //1.
        for(int i=0;i<=edges.size()-1;i++){
            ++inDegree[edges[i][1]];        //第二个参数 是child, 所以这样记录入度
            if(inDegree[edges[i][1]]==2){
                idx_edges_2indegree.push_back(i);
            }
        }

        //2.
        //把所有度为2的边都找出来
        //我们倾向性 选择最后加进来的,
        //所以在我们检查时 就用倒序, 先查 后进来的
        // 如果不对 再往前查
        std::reverse(idx_edges_2indegree.begin(),idx_edges_2indegree.end());

        //入度=2 (情况2, 情况三)
        if(idx_edges_2indegree.size()>0){
            int edge_idx = idx_edges_2indegree[0];
            if(judgeTreeAfterRemoveEdge(edges, node_n, edge_idx)==true){
                rs.push_back({edges[edge_idx][0],edges[edge_idx][1]});
            }
            //因为最多两个, 所以idx_edges_2indegree[1]就可以了
            else{
                edge_idx = idx_edges_2indegree[1];
                rs.push_back({edges[edge_idx][0],edges[edge_idx][1]});
            }

        }
        //入度=1 (情况三)
        else if (idx_edges_2indegree.size()==0){
            rs=getRemoveEdge(edges,node_n);
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
    vector<vector<int>> edges = {{1,2},{2,3},{1,3}};
    int node_n =5;
    int edge_m = 4;

    int node1 = 1;
    int node2 = 4;


    vector<int> parent1 = solut1->init_disjointFindUnion_vector_ints(node_n);       //每个独立元素 都init一下
    vector<vector<int>> rs = solut1->getLastRedundantEdgeII(edges,node_n);                          // 根据题目已知 建立好那个已知的 并查表
    //solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);


    //int rs1 = solut1->judgeRootSame(parent1,node1,node2);



    cout<<"result"<<endl;
    //cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);

    cout << rs[0][0]<<" "<<rs[0][1] << endl;
    return 0;
}


