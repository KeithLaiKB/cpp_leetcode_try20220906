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
//did not start yet
/**
 * 某个大型软件项目的构建系统拥有 N 个文件，文件编号从 0 到 N - 1，
 * 在这些文件中，某些文件依赖于其他文件的内容，这意味着如果文件 A 依赖于文件 B，
 * 则必须在处理文件 A 之前处理文件 B （0 <= A, B <= N - 1）。请编写一个算法，用于确定文件处理的顺序。
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
 * 这就是有向图了
                     0  ---------> 1
                                        --------->      --------->  5 <-------- 8
                                                    4               |           /\
                                        --------->                  |           |
                     2  ---------> 3                               \/           |
                                                                    6---------> 7
 * 用类似邻接表的方式
 *      他是用 unordered_map<int, vector<int>> umap;
 *      而不是vector<int, vector<int>>
 * 1. 先把所有每个点的入度找出来
 * 2. 把所有入度0的放进 零入度队列(这个队列放的都是 当前 入度为0 的节点)
 * 3. 遍历这个零入度队列
 *      把这些入度为0的节点/经过删除后入度为0的节点 指向 的其他的节点 的入度 减去1
 *          这些其他节点如果当减去1 以后 入度为0
 *              则放入队列


 *
 *输入:
 *第一行输入两个正整数 N, M。表示 N 个文件之间拥有 M 条依赖关系。
 *后续 M 行，每行两个正整数 S 和 T，表示 T 文件依赖于 S 文件
 *
 *输出:
 *输出共一行，如果能处理成功，则输出文件顺序，用空格隔开。
 *如果不能成功处理（相互依赖），则输出 -1。
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
    //--------------------------------------------

    // 边添加新edge 边判断
    vector<vector<int>> prepare_disjointFindUnion_and_GetLastRedundantEdge(vector<vector<int>> edges, vector<int>& parent){
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
    vector<vector<int>> rs = solut1->prepare_disjointFindUnion_and_GetLastRedundantEdge(edges,parent1);                          // 根据题目已知 建立好那个已知的 并查表
    //solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);


    //int rs1 = solut1->judgeRootSame(parent1,node1,node2);



    cout<<"result"<<endl;
    //cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);

    cout << rs[0][0]<<" "<<rs[0][1] << endl;
    return 0;
}


