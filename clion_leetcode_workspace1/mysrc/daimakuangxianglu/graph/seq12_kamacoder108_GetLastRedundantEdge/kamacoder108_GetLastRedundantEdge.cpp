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
 * 有一个图，它是一棵树，他是拥有 n 个节点（节点编号1到n）和 n - 1 条边的连通无环无向图，例如如图：
 * 现在在这棵树上的基础上，添加一条边（依然是n个节点，但有n条边），使这个图变成了有环图，如图：
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
 *输入顺序：(2,1), (1,4), (2,3), (3,5), (4,5)
 *
 * 因为我们发现他是形成一个环的 删除哪一个 都可以解除环
 * 此时我们要 删除最后一个能使 其变成环 的边
 *
 * 例如
 *处理过程：
 *  1. (2,1): 2和1不连通 → 连接它们
 *  2. (1,4): 1和4不连通 → 连接它们
 *  3. (2,3): 2和3不连通 → 连接它们
 *  4. (3,5): 3和5不连通 → 连接它们
 *  5. (4,5): 4和5已经连通了！→ 这是冗余边
 *
 *  答案：(4,5)
 *
 * 注意:
 *  这一题 是 一边prepare这个并查集
 *      一边同时 进行判断
 *
 *      因为每次 新加进来的 两个点, 如果成环
 *          打比方
 *              加入上面的 边(4和5)
 *                  这条边 他们的两个点的 root就是相同的
 *                  因为他们 之前已经 有相同的root 连通了
 *
 *  而不是 整个并查集准备好了以后
 *      才开始答题
 *
 *
 * 而且这个题目只有 一个环
 * 我们只需要返回 使得其形成环 的那个最后一条边 就可以了!!!!!!!!!
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

    // 边添加新edge 边判断
    vector<vector<int>> prepare_disjointFindUnion_and_GetLastRedundantEdge(vector<vector<int>> edges, vector<int>& father){
        vector<vector<int>> rs;

        //连接两个点 形成边
        for(int i=0;i<=edges.size()-1;i++){
            //如果相同根
            if(judgeRootSame(father,edges[i][0],edges[i][1])==true){
                rs.push_back({edges[i][0],edges[i][1]});
                break;
            }
            else{
                join(father, edges[i][0], edges[i][1]);
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


    vector<int> father1 = solut1->init_disjointFindUnion_vector_ints(node_n);       //每个独立元素 都init一下
    vector<vector<int>> rs = solut1->prepare_disjointFindUnion_and_GetLastRedundantEdge(edges,father1);                          // 根据题目已知 建立好那个已知的 并查表
    //solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);


    //int rs1 = solut1->judgeRootSame(father1,node1,node2);



    cout<<"result"<<endl;
    //cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);

    cout << rs[0][0]<<" "<<rs[0][1] << endl;
    return 0;
}


