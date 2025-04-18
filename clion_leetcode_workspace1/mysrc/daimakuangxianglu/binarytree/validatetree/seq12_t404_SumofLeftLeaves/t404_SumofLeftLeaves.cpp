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
 * Given the root of a binary tree,
 * return the sum of all left leaves.
 *
 * A leaf is a node with no children.
 * A left leaf is a leaf that is the left child of another node.
 *
 *
 *                          1
 *                  |               |
 *                  2               3
 *             |       |       |       |
 *            null    null     6       7
 *
 * 1->2
 * 1->3->6
 * 2+6=8
 * output: 8
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





    //时间复杂度: O(n)
    //空间复杂度:
    //  对于BFS来说  影响 主要是queue的大小
    //  最低部的叶子节点有可能接近n/2所以
    //      所以是 O(n)
    //
    // 如果你使用DFS 他每一层不是所有节点都存储的, 所以他就会出现 O(logn)~O(n)的状况
    // 如果完全平衡二叉树 每一层就存储一个, 总个数 是 2^n=k
    // 所以 层数n =log(2n)=O(logn)
    //
    // 但是这次用的是DFS 变种的先序遍历
    int backtracking(TreeNode* root) {
        int rs=0;
        //limit
        if(root== nullptr){
            return rs;
        }
/*      //写法1
        vector<TreeNode*> children1 = {root->left, root->right};
        for(TreeNode* chld : children1){
            // 如果   当前节点 不为空 且  lchild 为空
            if(chld!= nullptr){
                cout<<root->val<<" "<<chld->val<<endl;
                //如果当前for的是左叶子, 当前左叶子不为空
                //  并且 该左叶子的左叶子为空 和  该左叶子的右叶子也为空
                //      则把 当前左叶子 放进结果 进行累加
                if(chld == root->left && chld->left== nullptr && chld->right== nullptr){
                    rs += chld->val;
                }
                else{
                    rs += backtracking(chld);
                }
            }
        }*/
        //写法2
        if(root->left!= nullptr && root->left->left== nullptr && root->left->right== nullptr){
            rs += root->left->val;
        }
        else{
            rs += backtracking(root->left);
        }

        if(root->right!= nullptr){
            rs += backtracking(root->right);
        }

        return rs;
    }

    int sumOfLeftLeaves(TreeNode* root) {
        return backtracking(root);
    }



};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};
    std::vector<std::optional<int>> intopt_vec1 = {0,2,4,1,std::nullopt,3,-1,5,1,std::nullopt,6,std::nullopt,8};

    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    int rs = solut1->sumOfLeftLeaves(tree1);
    cout<<"result"<<endl;
    cout<<rs<<endl;

    return 0;
}


