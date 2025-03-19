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
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST.
 *
 * Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Search for a node to remove.
 * If the node is found, delete the node.
 *
 *
 *
 *
 * 但注意一下 你这个本身不是AVL树 不带height的 所以 就不要用AVL树那种东西来搞了，别管什么左旋右旋了
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
    //
    // 树的构造一般不会用backtracking
    // 直接 利用 BST 的  左<根<右 就好了
    TreeNode* mytraversal(TreeNode* root, int val){

        // limit
        if(root == nullptr){
            return nullptr;
        }

        //去左
        if(val < root->val){
            root->left = mytraversal(root->left, val);
            return root;
        }
        //去右
        else if(val > root->val){
            root->right = mytraversal(root->right, val);
            return root;
        }
        else if(val == root->val){
            TreeNode* lchild = root->left;
            TreeNode* rchild = root->right;

            if(lchild == nullptr && rchild== nullptr){
                delete(root);
                return nullptr;
            }
            //          preroot
            //              |
            //            root
            //         |        |
            //         9        null
            else if(lchild != nullptr && rchild== nullptr){
                delete(root);
                return lchild;
            }
            //          preroot
            //              |
            //            root
            //         |        |
            //        null     10
            else if(lchild == nullptr && rchild!= nullptr){
                delete(root);
                return rchild;
            }
            //                      preroot
            //              |                   |
            //            root                  18
            //         |        |
            //        9        10
            //      |    |    |   |
            //     11   12   13   14
            //
            //  此时有两种方法
            //      第一种 9和其的所有子节点   移动到 10 的节点左子树的最左边
            //      第二中 10和其的所有子节点  移动到 9 的节点右子树的最右边
            //
            //      我这里采用的是第一种, 其实这两种 没什么太大区别的, 怎么舒服怎么来就好
            //
            //                      preroot
            //              |                   |
            //             10                  18
            //         |        |
            //        13        14
            //     |
            //     9
            //   |   |
            //  11  12
            //
            else if(lchild != nullptr && rchild!= nullptr){
                TreeNode* tmp =rchild;
                for(;tmp->left!= nullptr;){
                    tmp=tmp->left;
                }
                tmp->left = lchild;


                delete(root);
                return rchild;
            }
        }

        return nullptr;
    }

    // 时间复杂度:
    //      平衡BST            :O(logn)
    //      最坏情况（链状树）   :O(n)（最深递归栈）。
    //
    //空间复杂度:
    //      平衡二叉树：O(logn)（二叉树深度）。
    //      最坏情况（链状树）：O(n)（最深递归栈）。
    TreeNode* deleteNode(TreeNode* root, int key) {
        return mytraversal(root, key);
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};

    std::vector<std::optional<int>> intopt_vec1_tree1 = {6,2,8,0,4,7,9,std::nullopt,std::nullopt,3,5};
    intopt_vec1_tree1.reserve(100);

//    std::vector<std::optional<int>> intopt_vec1_tree2 = {2,1,3,std::nullopt,4,std::nullopt,7};
//    intopt_vec1_tree2.reserve(100);
//
//    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
//    Solution::TreeNode* tree2 = solut1->initLinkedlist_ints(intopt_vec1_tree1);

    //std::vector<int> vec1_nums = {3,2,1,6,0,5};

    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
    Solution::TreeNode* rs = solut1->insertIntoBST(tree1,3);


    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    //cout<<rs<<endl;
    return 0;
}


