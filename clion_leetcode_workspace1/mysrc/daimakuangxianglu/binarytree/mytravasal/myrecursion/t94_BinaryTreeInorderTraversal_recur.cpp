#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
using namespace std;

/**
 *
 * 中序遍历(迭代)
 *
 */
class Solution {
private:

public:
    Solution(){

    }
    ~Solution(){

    }
   struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };


// [1,null,2,3,4,5,6,7,null]
    //           1
    //    |            |
    //   null          2
    //            |         |
    //            3         4
    //         |     |   |    |
    //         5     6   7   null
    // 塞1进去根节点队列
    // queue:[1]
    //
    // 弹出1 然后对根节点(局部) 1 进行其 子节点的 装配
    // 装配完 左边null 右边2, 然后把2 丢到 根节点队列
    // queue:[2]
    //       1
    //    |      |
    //   null    2
    //
    // 弹出2 然后对根节点(局部) 2 进行其 子节点的 装配
    // 装配完 左边3 右边4, 然后把3和4 丢到 根节点队列
    // queue:[3, 4]
    //       2
    //    |     |
    //    3     4
    //
    // 弹出3 然后对根节点(局部) 3 进行其 子节点的 装配
    // 装配完 左边5 右边6, 然后把 5和6 丢到 根节点队列
    // queue:[3, 4, 5, 6]
    //       3
    //    |     |
    //    5     6
    //
    // 弹出4 然后对根节点(局部) 4 进行其 子节点的 装配
    // 装配完 左边7 右边null, 然后把 7 丢到 根节点队列
    // queue:[5, 6, 7]
    //       4
    //    |     |
    //    7     null
    //
    // 弹出5 然后对根节点(局部) 5 进行其 子节点的 装配
    // 装配完 左边null 右边null, 没有任何东西 丢到 根节点队列
    // queue:[6, 7]
    //       5
    //
    // 弹出6 然后对根节点(局部) 6 进行其 子节点的 装配
    // 装配完 左边null 右边null, 没有任何东西 丢到 根节点队列
    // queue:[7]
    //       6
    //
    // 弹出7 然后对根节点(局部) 7 进行其 子节点的 装配
    // 装配完 左边null 右边null, 没有任何东西 丢到 根节点队列
    // queue:[]
    //       7
    // 结束
    //
    // const 代表不能修改 arr
    // & 代表的是引用  而不是 拷贝个副本进来
    TreeNode* initLinkedlist_ints(const vector<optional<int>> &arr){
        // 如果需要初始化的长度 <=0 就没必要初始化了
        // 或者如果 提供的数组本身 <=0 也没必要初始化了
        // 我这里这么做 是提供 有可能 数组长度很长(例如100), 但我只需要初始化其中比较短的一部分(5)
        //int len = sizeof(arr)/sizeof(arr[0]);
        int len = arr.size();
        if(len<=0){
            return nullptr;
        }

        if(arr[0].has_value()==false){
            return nullptr;
        }


        // 开始装配
        TreeNode *rs_head =new TreeNode(arr[0].value());
        TreeNode *rs_head_tmp =rs_head;

        // 用来存放 Treenode类型的 根节点,方便到时给他们加子节点
        queue<TreeNode*> q_root;
        q_root.push(rs_head_tmp);

        // idx=0已经弄过了 然后从idx=1开始弄
        int i=1;
        while(!q_root.empty() &&  i<=len-1){
            // 给当前要装备的 根节点(局部) 装配孩子节点
            rs_head_tmp = q_root.front();
            q_root.pop();


            // 装配左孩子
            if(i<=len-1 && arr[i].has_value()){
                TreeNode* l_tmp = new TreeNode(arr[i].value());
                rs_head_tmp->left=l_tmp;
                // 放到队列里 到时给他上 他的child节点
                q_root.push(l_tmp);
            }
            i++;     //无论是否是nullopt 他都占了一个 vector<optional<int>>的位置

            // 装配右孩子
            if(i<=len-1 && arr[i].has_value()){
                TreeNode* r_tmp = new TreeNode(arr[i].value());
                rs_head_tmp->right=r_tmp;
                // 放到队列里 到时给他上 他的child节点
                q_root.push(r_tmp);
            }
            i++;     //无论是否是nullopt 他都占了一个 vector<optional<int>>的位置

        }


        return rs_head;
    }



    void myOutput_Treenode_int(TreeNode* root){
        if(root == nullptr){
            return;
        }

        queue<TreeNode*> q_root;
        q_root.push(root);

        while(!q_root.empty()){

            int level_size=q_root.size();
            for(int i=0; i<=level_size-1; i++){
                TreeNode* current = q_root.front();
                q_root.pop();

                cout<< current->val<< "  ";

                //
                if(current->left!= nullptr){
                    q_root.push(current->left);
                }

                if(current->right!= nullptr){
                    q_root.push(current->right);
                }
            }

            // 遍历完一行
            cout<<endl;
        }

    }



    //时间复杂度: O(n)
    //空间复杂度:
    // [1,null,2,3,4,5,6,7,null]
    //           1
    //    |            |
    //   null          2
    //            |         |
    //            3         4
    //         |     |   |    |
    //         5     6   7   null
    // 塞1进去根节点队列
    // stack:[1]
    //
    // 滑到1 然后对根节点(局部) 1 准备进行其 左叶子节点方向滑动
    // stack:[1]
    //       1
    //    |      |
    //   null    2
    //
    // 左边为null 弹出1      vec={1}
    // 然后准备 对根节点(局部) 向 1 的右叶子节点方向滑动
    // 然后把 右叶子节点 2 丢到 根节点栈
    // stack:[2]
    //       1
    //    |      |
    //   null    2
    //
    // 滑到2
    // 左边不为null 不弹出2
    // 然后对根节点(局部) 2 准备进行其 左叶子节点方向滑动
    // 然后把 左叶子节点 3 丢到 根节点栈
    // stack:[2, 3]
    //       2
    //    |     |
    //    3     4
    //
    // 滑到3
    // 左边不为null 不弹出3
    // 然后对根节点(局部) 3 准备进行其 左叶子节点方向滑动
    // 然后把 左叶子节点 5 丢到 根节点栈
    // stack:[2, 3, 5]
    //       3
    //    |     |
    //    5     6
    //
    // 滑到5
    // 左边为null 弹出5      vec={1, 5}
    // stack:[2, 3]
    //       5
    //
    // 然后发现 5 的右边也为null
    // 弹出3                vec={1, 5, 3}
    // 然后准备 对根节点(局部) 向 3 的右叶子节点方向滑动
    // 然后把 右叶子节点 6 丢到 根节点栈
    // stack:[2, 6]
    //       3
    //    |     |
    //    5     6
    //
    // 滑到6
    // 左边为null 弹出6        vec={1, 5, 3, 6}
    // stack:[2]
    //       6
    //
    // 然后发现 6 的右边也为null
    // 弹出2                  vec={1, 5, 3, 6, 2}
    // 然后准备 对根节点(局部) 向 2 的右叶子节点方向滑动
    // 然后把 右叶子节点 4 丢到 根节点栈
    // stack:[4]
    //       2
    //    |     |
    //    3     4
    //
    // 滑到4
    // 左边不为null 不弹出4
    // 然后对根节点(局部) 4 准备进行其 左叶子节点方向滑动
    // 然后把 左叶子节点 7 丢到 根节点栈
    // stack:[4, 7]
    //       4
    //    |     |
    //    7     null
    //
    // 滑到7
    // 左边为null 弹出7          vec={1, 5, 3, 6, 2, 7}
    // stack:[4]
    //       7

    // 然后发现 7 的右边为null
    // 弹出4                    vec={1, 5, 3, 6, 2, 7, 4}
    // 然后准备 对根节点(局部) 向 4 的右叶子节点方向滑动
    // 可是右边为null
    // stack:[]
    //       4
    //    |     |
    //    7     null
    //
    // 结束
    //
    // 还没弄成功
    vector<int> inorderTraversal_notcompleted(TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        vector<int> rs_vec = {};
        TreeNode* root_tmp=root;
        stack<TreeNode*> st_root;

        st_root.push(root);

        // 根节点栈
        for(;st_root.empty()== false;){

            // 左侧叶子节点不为空
            if(root_tmp->left!= nullptr){
                st_root.push(root_tmp->left);
                //
                //然后继续往左下延伸
                root_tmp = root_tmp->left;
            }
            // 当前的根节点 左侧叶子节点为空, 那么就是剩下 左中右 里 的中和右
            else{
                //中
                cout<<root_tmp->val<<endl;
                rs_vec.push_back(root_tmp->val);

                //弹出当前根节点
                st_root.pop();

                //然后处理右侧
                //右侧叶子节点不为空
                if(root_tmp->right!= nullptr){
                    st_root.push(root_tmp->right);
                    //
                    //然后继续往右下延伸
                    root_tmp = root_tmp->right;
                }
                // 右侧叶子节点为空
                else{
                    // 该根节点下方所有的子节点 已完成
                    // 需要 准备下一轮 处理 之前未搜寻过右侧孩子节点 的根节点
                    root_tmp = st_root.top();
                    cout<<root_tmp->val<<endl;
                    rs_vec.push_back(root_tmp->val);    //根节点放入
                    //弹出此时的根节点
                    st_root.pop();

                    root_tmp = root_tmp->right;    //下一轮直接搜寻他的右节点
                    st_root.push(root_tmp->right);  //下轮他是根节点 所以也要放进去
                }


            }

        }

        return rs_vec;
    }

    //时间复杂度: O(n)
    //空间复杂度:
    // [1,null,2,3,4,5,6,7,null]
    //           1
    //    |            |
    //   null          2
    //            |         |
    //            3         4
    //         |     |   |    |
    //         5     6   7   null
    //
    // 注意一下stack里的null不代表任何null节点, 只是作为访问过得节点的标记而已
    // 塞1进去根节点队列
    // stack:[1]
    //
    // 弹出1, 因为不是null, 则属于第一种情况
    // 右: 塞入2,
    // 中: 再塞如2 的跟节点1,
    //     1已经访问过, 所以再塞入一个null 只是 当作访问过1的标记
    // 左: 左边为空 则 不塞入 也不需要塞入null
    // stack:[2, 1， null]
    //       1
    //    |      |
    //   null    2
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 现在应当搜索的就是上一轮 1节点 的左叶子作为根节点, 所以 现在搜索的是1节点的右手边)
    // 再弹出 stack上的top 1 并塞入结果集里 vec={1}
    // stack:[2]
    //       1
    //    |      |
    //   null    2
    //
    // 弹出2, 因为不是null, 则属于第一种情况 (所以 现在搜索的是2节点 左叶子和右叶子节点)
    // 右: 塞入4,
    // 中: 再塞入4 的根节点2,
    //     2已经访问过, 所以再塞入一个null 只是 当作访问过2的标记
    // 左: 塞入3
    // stack:[4, 2, null, 3]
    //       2
    //    |     |
    //    3     4
    //
    // 弹出3, 因为不是null, 则属于第一种情况 (所以 现在搜索的是3节点 左叶子和右叶子节点)
    // 右: 塞入6,
    // 中: 再塞如6 的根节点3,
    //     3已经访问过, 所以再塞入一个null 只是 当作访问过3的标记
    // 左: 左边为5
    // stack:[4, 2， null, 6, 3, null, 5]
    //       3
    //    |     |
    //    5     6
    //
    // 弹出5, 因为不是null, 则属于第一种情况 (所以 现在搜索的是5节点 左叶子和右叶子节点)
    // 右: 右边为空 则 不塞入 也不需要塞入null
    // 中: 再塞入 的根节点5,
    //     5已经访问过, 所以再塞入一个null 只是 当作访问过5的标记
    // 左: 左边为空 不塞入 也不需要塞入null  (这过程就是 搜索 5的左叶子节点)
    // stack:[4, 2， null, 6, 3, null, 5, null]
    //       5
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 现在应当搜索的就是上一轮 5 的左叶子作为根节点, 但是 现在搜索的是5节点的右手边)
    // 再弹出 stack上的top 5 并塞入结果集里 vec={1, 5}
    // stack:[4, 2， null, 6, 3, null]
    //       5
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 搜索的就是上一轮 5 的左叶子 或右叶子节点!!!!!!!, 但是 现在搜索的是3节点的右手边)
    // 再弹出 stack上的top 3 并塞入结果集里 vec={1, 5, 3}
    // stack:[4, 2， null, 6]
    //       3
    //    |     |
    //    5     6
    //
    // 弹出6, 因为不是null, 则属于第一种情况 (所以 现在搜索的是6节点 左叶子和右叶子节点)
    // 右: 右边为空 则 不塞入 也不需要塞入null
    // 中: 再塞入 的根节点6,
    //     6已经访问过, 所以再塞入一个null 只是 当作访问过6的标记
    // 左: 左边为空 不塞入 也不需要塞入null (这过程就是 搜索 6的左叶子节点)
    // stack:[4, 2， null, 6, null]
    //       6
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 搜索的就是上一轮 6 的左叶子, 所以 现在搜索的是6节点的右手边)
    // 再弹出 stack上的top 6 并塞入结果集里 vec={1, 5, 3, 6}
    // stack:[4, 2， null]
    //       6
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 搜索的就是上一轮 6 的左叶子或右叶子, 所以 现在搜索的是2节点的右手边)
    // 再弹出 stack上的top 2 并塞入结果集里 vec={1, 5, 3, 6, 2}
    // stack:[4]
    //       2
    //    |     |
    //    3     4
    //
    // 弹出4, 因为不是null, 则属于第一种情况 (所以 现在搜索的是4 的右叶子节点)
    // 右: 右边为空 则 不塞入 也不需要塞入null
    // 中: 再塞入 的根节点4,
    //     4已经访问过, 所以再塞入一个null 只是 当作访问过2的标记
    // 左: 塞入7
    // stack:[4, null, 7]
    //       4
    //    |     |
    //    7    null
    //
    //
    // 弹出7, 因为不是null, 则属于第一种情况 (所以 现在搜索的是7 的右叶子节点)
    // 右: 右边为空 则 不塞入 也不需要塞入null
    // 中: 再塞入 的根节点7,
    //     7已经访问过, 所以再塞入一个null 只是 当作访问过2的标记
    // 左: 左边为空 不塞入 也不需要塞入null (这过程就是 搜索 7的左叶子节点)
    // stack:[4, null, 7, null]
    //       7
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 搜索的就是上一轮 7 的左叶子, 所以 现在搜索的是7节点的右手边)
    // 再弹出 stack上的top 7 并塞入结果集里 vec={1, 5, 3, 6, 2, 7}
    // stack:[4, null]
    //       7
    //
    // 弹出null, 因为是null, 则属于第二种情况 (也就是说如果此时不为null, 搜索的就是上一轮 7 的左叶子 或右叶子 !!!, 所以 现在搜索的是4节点的右手边)
    // 再弹出 stack上的top 4 并塞入结果集里 vec={1, 5, 3, 6, 2, 7, 4}
    // stack:[]
    //       4
    //    |     |
    //    7    null
    //
    // 结束
    //
    // 统一迭代方案
    // 统一迭代 的代码当中 在 前中后序这三种遍历 没有任何代码的增加 或减少
    // 统一迭代 的代码当中 只有 情况一中的 右 中 左 代码的顺序不同
    //
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        vector<int> rs_vec = {};
        TreeNode* root_tmp=root;
        stack<TreeNode*> st_root;

        st_root.push(root);
        for(;st_root.empty()== false;){
            root_tmp = st_root.top();

            // 情况一:
            // 如果不为空 因为我们是stack 所以要反顺序,
            // 也就是需要先把 右边的放进 根节点stack
            // 因为我们的stack 会放一个null作为一个 已经搜寻过跟节点的标记
            // 所以这里会比其他两种 多一个null的判断 !!!!!!
            if(root_tmp != nullptr){
                st_root.pop();      //先弹出这个中间节点

                //反顺序 放进去 因为我们用的是stack ------------------------------------
                // 先放右
                if(root_tmp->right != nullptr){
                    st_root.push(root_tmp->right);
                }
                //-----------------------------------------------------------------
                // 放中
                st_root.push(root_tmp);
                // 放null 用来到 stack弹出的时候 代表中间的已经 访问过左手边的节点了 (因为是反顺序放的)
                st_root.push(nullptr);
                //-----------------------------------------------------------------
                //再放左
                if(root_tmp->left != nullptr){
                    st_root.push(root_tmp->left);
                }
            }
            // 情况二:
            // 如果空 则弹出这个null
            // 并且 再弹出这个 跟节点
            else{
                //弹出null
                st_root.pop();

                //将中间节点 并且塞入结果集合
                root_tmp = st_root.top();
                rs_vec.push_back(root_tmp->val);
                cout<<root_tmp->val<<endl;

                //弹出中间节点
                st_root.pop();
            }

        }

        return rs_vec;
    }
};

/**
 * @return
 */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();



    std::vector<std::optional<int>> intopt_vec1 = {1, 2, 3, 4, 5, std::nullopt, 8, std::nullopt, std::nullopt, 6, 7, 9};
    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    vector<int> rs_vec1= solut1->inorderTraversal(tree1);
    cout<<"result"<<endl;


    return 0;
}


