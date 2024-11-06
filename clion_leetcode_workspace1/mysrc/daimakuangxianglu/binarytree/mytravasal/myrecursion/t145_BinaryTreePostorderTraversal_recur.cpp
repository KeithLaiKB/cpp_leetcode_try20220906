#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <algorithm>
using namespace std;

/**
 *
 * 后序遍历(迭代)
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

    template <typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

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
    // 相当于从前序便利的迭代版本 上更改 从 中左右(前序便利)->中右左(代码 的左和右 相反就行了)-> 左右中(把结果集合整体反过来就行了)
    // 这个方法是我的 是可以通过leetcode 的
    vector<int> postorderTraversal_my(TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        vector<int> rs_vec = {};
        TreeNode* root_tmp=root;
        stack<TreeNode*> st_root;

        st_root.push(root);
        for(;st_root.empty()== false;){
            root_tmp = st_root.top();

            //中
            rs_vec.push_back(root_tmp->val);
            cout<<root_tmp->val<<endl;
            st_root.pop();

            //先放左
            if(root_tmp->left != nullptr){
                st_root.push(root_tmp->left);
            }

            //反顺序 放进去 因为我们用的是stack
            //再放右
            if(root_tmp->right != nullptr){
                st_root.push(root_tmp->right);
            }

        }


        //结果集合反过来
        reverse(rs_vec.begin(),rs_vec.end());
        return rs_vec;
    }

    // 统一迭代方案
    // 用null 放在 中节点的后面
    // 统一迭代 的代码当中 在 前中后序这三种遍历 没有任何代码的增加 或减少
    // 统一迭代 的代码当中 只有 情况一中的 中 右 左  代码的顺序不同
    vector<int> postorderTraversal(TreeNode* root) {
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
                // 先放中
                st_root.push(root_tmp);
                // 放null 用来到 stack弹出的时候 代表中间的已经 访问过左手边的节点了 (因为是反顺序放的)
                st_root.push(nullptr);
                //-----------------------------------------------------------------
                //再放右
                if(root_tmp->right != nullptr){
                    st_root.push(root_tmp->right);
                }
                //-----------------------------------------------------------------
                // 放左
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

    //vector<int> rs_vec1= solut1->postorderTraversal_my(tree1);
    vector<int> rs_vec1= solut1->postorderTraversal(tree1);
    cout<<"result"<<endl;
    solut1->myOutput_VectorBtB(rs_vec1,0,rs_vec1.size()-1);

    return 0;
}


