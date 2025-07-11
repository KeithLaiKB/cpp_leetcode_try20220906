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
 * 给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。
 * 请编写一个函数，
 *
 * 找出并返回所有从节点 1 到 节点 n 的路径。每条路径应以节点编号的列表形式表示。
 * 也就是说 n这个数字 就是 最终的节点
 * 1 则一定是起点
 *
 * 例如 n=5
 *      他指的是 终点只能为5的路径
 *
 *
        1  ------>  2
        |           |
        |           |
       \/           \/
       3            4
         |        |
           |   |
          \/  \/
            5
 *
 * 结果:
 * 1->3->5
 * 1->2->4->5
 *
 *
 * 这里 我们是用邻接表
 * 但是 我们这里
 * vector<list<int>> 来存放 邻接表
 *
 *
 * 本题我们会有n 个节点，因为节点标号是从1开始的，为了节点标号和下标对齐，我们申请 n + 1 * n + 1 这么大的二维数组。
 * 所以 纵向(n+1) * 横向(n+1)
 * 所以有
 * 方案一(当前代码文件 使用的方案):
 *      vector<list<int>> graph(n + 1);
 * 或者
 *
 * 方案二:
 *      vector<vector<int>> graph(n + 1, vector<int>);
 *          但是 这种 和邻接矩阵 很像, 但会有点不一样,
 *          因为 这里里面的  vector 他的长度是不固定的
 *
 *
 *
 * 对于邻接表
 * 所以 纵向(n+1) * 横向(list 未知)
 * vector<list<int>> graph(n + 1); // 邻接表，list为C++里的链表
 *
 * 当然 chatgpt说邻接表
 *      vector<vector<int>> graph;
 * 这样更推荐
 *
 * 所以 具体 题目给你的 vector<vector>
 *      他有可能使 邻接矩阵 也可能是 邻接表
 *      具体要看它的 输入内容
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




    // 邻接表
    vector<list<int>> init_AdjacencyList_list_ints(){

        //----------------- 模拟console 进来的参数  ---------------------

        // simulate input,
        // 我这里 就不用 cin>>x1>>x2; 来搞了,
        // 不然输入太麻烦了
        vector<vector<int>> simul_input ={{1,3}, {3,5}, {1,2}, {2,4}, {4,5}};


        //因为不一定每个点 都有多少条边的, 所以 总边数是不一样的, 纵轴 就代表 每个边
        // 例如
        //        1 3       1和3 有一条边相连接
        //        3 5       3和5 有一条边相连接
        //        1 2       1和2 有一条边相连接
        //        2 4       2和5 有一条边相连接
        //        4 5       4和5 有一条边相连接
        // 当然啦, 这个edge num 只是 为了从控制台 那里 for loop 多少次 来输入边而已
        int edge_m = simul_input.size();
        int nodes_n = 5;        // 一共有5个节点

        //--------------------------------------------------------------


        //创建 邻接表
        // 这里的 list<int>() 不会创建什么 值为0的节点 先塞进去 之类的,
        //      因为他是链表, 此时 是空的链表
        vector<list<int>> adjList (nodes_n+1, list<int>());         // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
        //vector<list<int>> adjList (nodes_n+1);                            //和上面的写法 等价
        //

        // 这个表也 和 邻接矩阵 不同！！！！！！！！！！！！！！！
        //
        // idx     list(链表)
        //  0
        //  1       2    3
        //  2       4
        //  3       5
        //  4       5
        //  5
        // ...
        //  n
        //
        // 也可以看到 一共是n+1
        //
        // 开始
        // 根据 console 进来的参数 进行 邻接矩阵的 填写
        for(int i=0;i<=edge_m-1;i++){
            int node_tmp1 = simul_input[i][0];
            int node_tmp2 = simul_input[i][1];

            // 第一行 和 第一列 都是0 基本是不用的,
            // 我们只要按照数字 作为下标 当作Node就可以了
            adjList[node_tmp1].push_back(node_tmp2);                    // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
        }

        return adjList;
    }





    //时间复杂度:
    //空间复杂度:
    //
    // 邻接表 基于dfs 走回溯的方式
    void backtracking_dfs (const vector<list<int>>& graph, int node_num, int dest_node, vector<int> &now_path, vector<vector<int>>& rs) {

        //limit
        //当前已经到达了目的地了
        if(node_num == dest_node){
            rs.push_back(now_path);
            return;
        }

        //
        //deal before for loop
        //
        //for
        // 因为 他是邻接矩阵, 所以每一行 的数量都是固定的 用graph[0].size() 是没问题的,
        // 当然 你也可以用 i <= max_num
        for(const int& dst_tmp : graph[node_num]){                                              // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
            now_path.push_back(dst_tmp);                                                    // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
            backtracking_dfs (graph, dst_tmp, dest_node, now_path, rs);     // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
            //
            //pop
            // 本来回溯 就像树一样的逻辑, 一条子路径搞完, 就看另外一条子路径
            now_path.pop_back();
        }

    }


    vector<vector<int>> getAllReachablePath(const vector<list<int>>graph, int dest_node){
        vector<vector<int>> rs;
        vector<int> now_path;

        //start node from 1, 所有的路径的起始点都是1
        now_path.push_back(1);

        backtracking_dfs(graph,1,dest_node,now_path,rs);
        return rs;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();

    // 初始化 图
    vector<list<int>> adjacencyList1 = solut1->init_AdjacencyList_list_ints();
    solut1->myOutput_VectorBlistBtBB(adjacencyList1, 0, adjacencyList1.size()-1);

    // 我这里 就把 最后的那个 点 当作 终点好了,
    //      例如 我们有 1~5 个node, 我们实际会有 5+1个空间,
    //          我这里打算 把 5 当作终点
    //      因为 本题我们会有n 个节点，因为节点标号是从1开始的，为了节点标号和下标对齐，我们申请 n + 1 * n + 1 这么大的二维数组。
    // 当然 你也可以改终点
    int dest_node = adjacencyList1.size()-1;
    vector<vector<int>> rs1 = solut1->getAllReachablePath(adjacencyList1,dest_node);



    cout<<"result"<<endl;
    //cout<<rs<<endl;
    solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


