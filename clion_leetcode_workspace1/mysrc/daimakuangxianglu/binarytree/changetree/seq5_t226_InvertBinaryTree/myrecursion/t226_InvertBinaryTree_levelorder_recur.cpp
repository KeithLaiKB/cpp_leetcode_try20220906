#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
using namespace std;

/**
 *  * 前序遍历(迭代)
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



    //时间复杂度: O(n)
    //空间复杂度:
    //  对于平衡二叉树（例如完全二叉树），递归调用的最大深度是树的高度: O(logn)
    //      所以是 O(logn)
    //  对于非平衡的二叉树（例如退化成链表的二叉树），递归调用的最大深度会达到: O(n)
    //      所以是 O(n)
    //
    // 它的主要代码基本 和 level的迭代 一致, 只是弄了个swap而已
    TreeNode* invertTree_preorder(TreeNode* root) {
        //vector<vector<int>> rs_vec = {};
        //rs_vec.reserve(100);

        if(root == nullptr){
            return {};
        }

        queue<TreeNode*> q_root;
        q_root.push(root);

        while(!q_root.empty()){
            vector<int> rs_vec_tmp = {};
            rs_vec_tmp.reserve(100);

            // 看此时这层 右多少个节点 在 跟节点队列里
            int level_size = q_root.size();


            for(int i=0;i<=level_size-1;i++){
                TreeNode* root_tmp = q_root.front();
                q_root.pop();

                //cout<< root_tmp->val<<"  ";
                //rs_vec_tmp.push_back(root_tmp->val);
                //进行swap------------
                TreeNode *temp_toswap = root_tmp->left;
                root_tmp->left = root_tmp->right;
                root_tmp->right = temp_toswap;
                //-------------------


                if(root_tmp->left!= nullptr){
                    q_root.push(root_tmp->left);
                }

                if(root_tmp->right!= nullptr){
                    q_root.push(root_tmp->right);
                }
            }

            //rs_vec.push_back(rs_vec_tmp);
            //cout<<endl;
        }

        return root;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    std::vector<std::optional<int>> intopt_vec1 = {1, 2, 3, 4, 5, std::nullopt, 8, std::nullopt, std::nullopt, 6, 7, 9};
    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    solut1->invertTree_preorder(tree1);
    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(tree1);

    return 0;
}


