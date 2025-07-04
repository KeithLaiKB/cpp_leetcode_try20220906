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
 * 给定一个有向图，包含 N 个节点，节点编号分别为 1，2，...，N。现从 1 号节点开始，如果可以从 1 号节点的边可以到达任何节点，则输出 1，否则输出 -1。
 *
 * 输入:
 * 第一行包含两个正整数，表示节点数量 N 和边的数量 K。 后续 K 行，每行两个正整数 s 和 t，表示从 s 节点有一条边单向连接到 t 节点。
 *
 *
 * 输出:
 *  如果可以从 1 号节点的边可以到达任何节点，则输出 1，否则输出 -1
 *
 *
 *
 * 例如
 * 4 4   也就是4个节点   4条边
 * 1 2
 * 2 1
 * 1 3
 * 2 4
 *
 *
 *
 *
 *
 *
 * 这就是有向图了
                        <--------
                     1             2
                        --------->
                     |             |
                     |             |
                    \/            \/
                    3             4




 *
 * 结果:
 * 1
 * 因为
 *  从节点1 可以走到 里面的所有节点
 *
 *
 * 可以用dfs/bfs
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




    // 邻接表
    vector<vector<int>> init_AdjacencyList_vector_ints(int node_n, vector<vector<int>> edges){

        //----------------- 模拟console 进来的参数  ---------------------

        // simulate input,
        // 我这里 就不用 cin>>x1>>x2; 来搞了,
        // 不然输入太麻烦了
        //vector<vector<int>> simul_input ={{1,3}, {3,5}, {1,2}, {2,4}, {4,5}};


        //因为不一定每个点 都有多少条边的, 所以 总边数是不一样的, 纵轴 就代表 每个边
        // 例如
        //        1 3       1和3 有一条边相连接
        //        3 5       3和5 有一条边相连接
        //        1 2       1和2 有一条边相连接
        //        2 4       2和5 有一条边相连接
        //        4 5       4和5 有一条边相连接
        // 当然啦, 这个edge num 只是 为了从控制台 那里 for loop 多少次 来输入边而已
        //int edge_m = simul_input.size();
        //int nodes_n = 5;        // 一共有5个节点

        //--------------------------------------------------------------


        //创建 邻接表
        // 这里的 list<int>() 不会创建什么 值为0的节点 先塞进去 之类的,
        //      因为他是链表, 此时 是空的链表
        vector<vector<int>> adjList (node_n+1, vector<int>());         // 和 邻接矩阵 不同, 这里的 vector 不需要指定 固定多少个！！！！！！！！！！！！！！！
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
        for(int i=0;i<=edges.size()-1;i++){
            int node_tmp1 = edges[i][0];
            int node_tmp2 = edges[i][1];

            // 第一行 和 第一列 都是0 基本是不用的,
            // 我们只要按照数字 作为下标 当作Node就可以了
            adjList[node_tmp1].push_back(node_tmp2);                    // 和 邻接矩阵 不同！！！！！！！！！！！！！！！
        }

        return adjList;
    }


    //时间复杂度:
    //空间复杂度:
    //
    // 邻接表 基于dfs 但不是回溯的方式
    // 我们这里用的是 visited 用 unordered_map
    // unordered_map 访问时间 平均 O(1)，最坏 O(n)
    int backtracking_dfs_unordmap (const vector<vector<int>>& graph, int node_st,  unordered_map<int,int> &visited) {

        //limit
        //已经都访问过了, 可以结束了


        //
        //deal before for loop
        //
        //for
        // 因为 他是邻接矩阵, 所以每一行 的数量都是固定的 用graph[0].size() 是没问题的,
        // 当然 你也可以用 i <= max_num
        for(const int& dst_tmp : graph[node_st]){

            //如果访问过
            if(visited.find(dst_tmp)!=visited.end()){
                //则跳过
                continue;
            }


            visited[dst_tmp]=1;
            backtracking_dfs_unordmap (graph, dst_tmp,visited) ;

            //
            //不需要pop, 因为只看点 不用记录路径

        }

        return 0;
    }

// 邻接表 基于dfs 但不是回溯的方式
    // 我们这里用的是 visited 用 unordered_map
    // unordered_map 访问时间 平均 O(1)，最坏 O(n)
    int backtracking_dfs(const vector<vector<int>>& graph, int node_st,  vector<int> &visited) {

        //limit
        //已经都访问过了, 可以结束了


        //
        //deal before for loop
        //
        //for
        // 因为 他是邻接矩阵, 所以每一行 的数量都是固定的 用graph[0].size() 是没问题的,
        // 当然 你也可以用 i <= max_num
        for(const int& dst_tmp : graph[node_st]){

            //如果访问过
            if(visited[dst_tmp]==1){
                //则跳过
                continue;
            }


            visited[dst_tmp]=1;
            backtracking_dfs (graph, dst_tmp,visited) ;

            //
            //不需要pop, 因为只看点 不用记录路径

        }

        return 0;
    }



    //时间复杂度: O(V + E)
    //
    //      V：节点数量（每个节点最多被访问一次）
    //      E：边的数量（每条边最多被遍历一次）
    //      最后的验证 for 查是否全visited 过 :O(V)
    //
    //空间复杂度: O(V + E)
    //
    // 只要 从1 节点 出发, 能达到所有 节点
    // 就返回1 否则返回-1
    int checkFullReachability(int nodes_num,vector<vector<int>> graph){
        int rs =1;

        // unordered_map的写法-----------------------------
        //unordered_map<int,int> visited;
        //visited[1]=1;

        //因为visited是没有把0放进去的!!!!!!!!!!!!!!!!
        // 而且0也不会被访问的
        // 所以总size要-1， 但这样的 写法还是不够 好
/*        if(visited.size()==graph.size()-1){
            rs=1;
        }*/

        //从1开始 一个个核对 是最好的
//        for(int i=1;i<=graph.size()-1;i++){
//            if(visited.find(i)==visited.end()){
//                return -1;
//            }
//        }
        // -----------------------------

        // vector<int>的写法-----------------------------
        vector<int> visited(nodes_num+1,0);             //不仅邻接表是 n+1, 这里对应的visited 数组也要 n+1
        visited[1]=1;
        backtracking_dfs(graph,1,visited);

        for(int i=1;i<=nodes_num;i++){

            //如果发现 有node没有被访问过, 则返回值-1
            if(visited[i]==0){
                return -1;
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
    vector<vector<int>> edges = {{1,2},{2,1},{1,3},{2,4}};
    int node_num=4;

    vector<vector<int>> adjacencyList1 = solut1->init_AdjacencyList_vector_ints(node_num,edges);
    solut1->myOutput_VectorBvecBtBB(adjacencyList1, 0, adjacencyList1.size()-1);

    // 我这里 就把 最后的那个 点 当作 终点好了,
    //      例如 我们有 1~5 个node, 我们实际会有 5+1个空间,
    //          我这里打算 把 5 当作终点
    //      因为 本题我们会有n 个节点，因为节点标号是从1开始的，为了节点标号和下标对齐，我们申请 n + 1 * n + 1 这么大的二维数组。
    // 当然 你也可以改终点
    //int dest_node = adjacencyList1.size()-1;
    int rs1 = solut1->checkFullReachability(node_num,adjacencyList1);



    cout<<"result"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1, 0, rs1.size()-1);
    return 0;
}


