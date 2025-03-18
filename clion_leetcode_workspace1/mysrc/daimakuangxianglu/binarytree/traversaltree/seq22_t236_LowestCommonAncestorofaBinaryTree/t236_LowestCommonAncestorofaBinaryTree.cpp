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
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * According to the definition of LCA on Wikipedia:
 * “The lowest common ancestor is defined between two nodes p and q as the lowest node in T
 * that has both p and q as descendants (where we allow a node to be a descendant of itself).”
 *
                                    1
                    |                               |
                    2                               3
            |               |               |               |
            4               5               6               7
       |       |        |       |       |       |       |       |
       8       9       null    11      12      null    14       15

       例如
 *          8 和 9 的最近祖先 是 4
 *          2 和 9 的最近祖先 是 2
 *          8 和 5 的最近祖先 是 2
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

    template <typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    //
    // 从下往上
    // 那肯定是DFS
    TreeNode* backtracking(TreeNode* root1, TreeNode* p, TreeNode* q){

        // limit
        if(root1== nullptr){
            return nullptr;
        }
        else if(root1 != nullptr && (root1==p||root1==q)){
            return root1;
        }

        // construct

        // for
        vector<TreeNode*> children1 = {root1->left,root1->right};
        //
        // rs 只能是 p 或q, 或者是root
        // rs 是nullptr就证明没找到
        TreeNode* lf_rs = nullptr;
        TreeNode* rg_rs = nullptr;

        for(TreeNode* child_tmp: children1){

            if(child_tmp == root1->left){
                lf_rs = backtracking(root1->left, p, q);
            }
            else if(child_tmp == root1->right){
                rg_rs = backtracking(root1->right, p, q);
            }
        }

        //左右边 都不为空 证明两边都找到了
        if(lf_rs!= nullptr && rg_rs!= nullptr){
            return root1;
        }
        //只找到左边有, 可能是p, 可能是q, 也有可能是 lowest common ancestor, 当然p和q 也可以是lowest common ancestor
        else if(lf_rs!= nullptr && rg_rs== nullptr){
            return lf_rs;
        }
        //只找到右边有, 可能是p, 可能是q, 也有可能是 lowest common ancestor, 当然p和q 也可以是lowest common ancestor
        else if(lf_rs== nullptr && rg_rs!= nullptr){
            return rg_rs;
        }


        return nullptr;

    }

    // 时间复杂度:
    //      遍历所有的节点所以是O(n)
    //
    //空间复杂度:
    //      最坏情况（链状树）：O(n)（最深递归栈）。
    //      平衡二叉树：O(logn)（二叉树深度）。
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return backtracking(root,p,q);
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};

    std::vector<std::optional<int>> intopt_vec1_tree1 = {3,5,1,6,2,0,8,std::nullopt,std::nullopt,7,4};
    intopt_vec1_tree1.reserve(100);

//    std::vector<std::optional<int>> intopt_vec1_tree2 = {2,1,3,std::nullopt,4,std::nullopt,7};
//    intopt_vec1_tree2.reserve(100);
//
//    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
//    Solution::TreeNode* tree2 = solut1->initLinkedlist_ints(intopt_vec1_tree1);

    //std::vector<int> vec1_nums = {3,2,1,6,0,5};

    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
    Solution::TreeNode* rs = solut1->lowestCommonAncestor(tree1,tree1->left,tree1->right);


    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    //cout<<rs<<endl;
    return 0;
}


