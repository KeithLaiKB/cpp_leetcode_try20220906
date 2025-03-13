#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>

using namespace std;

/**
 *
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * A valid BST is defined as follows:
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 * 就验证 这个是不是 二叉搜索树
 *
 *
 *
 * -2^31 <= Node.val <= 2^31 - 1
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


    TreeNode* initLinkedlist_ints(const vector<optional<int>> &arr){
        // 如果需要初始化的长度 <=0 就没必要初始化了
        // 或者如果 提供的数组本身 <=0 也没必要初始化了
        // 我这里这么做 是提供 有可能 数组长null度很长(例如100), 但我只需要初始化其中比较短的一部分(5)
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

    template <typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    // 搜索二叉树的 中序便利一定是递增的
    //
    //
    //                                  12
    //                  |                                  |
    //                  5                                   18
    //          |               |                   |               |
    //          2               9                   14             23
    //      |       |       |       |           |       |       |       |
    //      1       3       7       10          13       17     20       25
    // 这个55就不对,
    // 这个4也不对
    // 这可以DFS 起手

    // 因为是左中右,
    // 上一个搜索过的节点 一定要比 下一个搜索节点要小
    //
    // 搜索完 5 的左子树后
    // 要确保 上一个搜索节点(3) 比当前节点(5)小
    // 然后
    // 然后再去搜索 5 的右子树
    //
    // 因为DFS直接下到 5 的右子树 18 里面的左子树 13
    // 要确保 上一个搜索节点(5) 比当前节点(13)小
    // 然后一直下去
    //
    // 又或者说
    // 搜索完 12 的左子树后
    // 要确保 当前root左子树已经搜索过的最后一个节点(例如上面的 12) 要 比当前root(上面的12) 小
    // 然后再去搜索 12 的右子树
    TreeNode* searched_prev_node = nullptr;
    bool mytraversal(TreeNode* root1){
        // 这个判断的是子树里的 不包括源树一开始就是空树的情况
        // 因为源树是空树的情况 早就在 之前的 入口函数 判断了
        if(root1== nullptr){
            return true;
        }


        bool left = false;
        bool right = false;

        //左
        left = mytraversal(root1->left);
        //中
        // 不能出先重复数值, 而且必须搜索的结果要递增
        // 如果 他是第一次搜下来的 那么 searched_prev_node 会出现 nullptr
        // 因为刚开始搜, 那么就相当于 一个数组 的a[0]
        // 那么就没必要作对比, 继续往下走就好饿
        if(searched_prev_node!= nullptr && searched_prev_node-> val >= root1->val){
            return false;
        }
        searched_prev_node = root1;

        //右
        right = mytraversal(root1->right);

        return left && right;
    }


    // 时间复杂度:
    //      最坏情况: 链状 BST    :O(n)
    //      一般情况: 平衡 BST    :O(log n)
    //空间复杂度:
    //      最坏情况: 链状 BST    :O(n)
    //      一般情况: 平衡 BST    :O(log n)
    //      递归在底层 本来就是类似一个栈一样的东西 就是 callstack
    bool isValidBST(TreeNode* root) {
        //空树
        if(root == nullptr){
            return true;
        }
        return mytraversal(root);
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};

//    std::vector<std::optional<int>> intopt_vec1_tree1 = {1,3,2,5};
//    intopt_vec1_tree1.reserve(100);
//
//    std::vector<std::optional<int>> intopt_vec1_tree2 = {2,1,3,std::nullopt,4,std::nullopt,7};
//    intopt_vec1_tree2.reserve(100);
//
//    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
//    Solution::TreeNode* tree2 = solut1->initLinkedlist_ints(intopt_vec1_tree1);

    //std::vector<int> vec1_nums = {3,2,1,6,0,5};

    std::vector<std::optional<int>> intopt_vec1_tree1 = {2,1,3};
    intopt_vec1_tree1.reserve(100);
    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);


    int target_num= 2;

    bool rs = solut1->isValidBST(tree1);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    //solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


