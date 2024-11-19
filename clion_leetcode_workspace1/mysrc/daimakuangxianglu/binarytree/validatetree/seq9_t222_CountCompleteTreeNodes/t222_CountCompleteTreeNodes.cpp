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
 * 计算完全二叉树的节点个数
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 *
 * According to Wikipedia, every level, except possibly the last,
 * is completely filled in a complete binary tree,
 * and all nodes in the last level are as far left as possible.
 * It can have between 1 and 2h nodes inclusive at the last level h.
 *
 * Design an algorithm that runs in less than O(n) time complexity.
 *
                    2
            |               |
            3               4
        |       |       |       |
        5       6       8       8

第三层的个数为 2^(3-1)=4
总个数 = 2^3 -1=7
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





    //时间复杂度: 不确定
    //空间复杂度: 不确定
    // 但是这次用的是栈迭代版的DFS
    // 这个是成功的
    int countNodes (TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        vector<int> rs_vec = {};
        TreeNode* root_tmp=root;
        queue<TreeNode*> q_root;


        //和maximum depth 相比, 从0改成了INT_MAX---------------------------
        int rs_depth=INT_MAX;
        //----------------------------------------------

        //放入根节点
        q_root.push(root_tmp);

        int now_depth=0;
        int count_node=0;

        for(;q_root.empty()==false;){

            root_tmp = q_root.front();
            q_root.pop();
            ++now_depth;



            int left_depth=0;
            TreeNode* left_tmp = root_tmp->left;
            for(;left_tmp!= nullptr;){
                ++left_depth;
                left_tmp= left_tmp->left;
            }

            int right_depth=0;
            TreeNode* right_tmp = root_tmp->right;
            for(;right_tmp!= nullptr;){
                ++right_depth;
                right_tmp= right_tmp->right;
            }

            //                        2
            //                |               |
            //                3               4
            //            |       |       |       |
            //            5       6       8       8
            //          |   |   |    |
            //          9   9   9    9
            //2^n-1
            //1<<0 =1
            //1<<1 =2
            //
            // 如果此时 root_tmp 是3
            // left_depth == right_depth = 2
            // 从 root_tmp 开始的总层数 = left_depth+1
            if(left_depth == right_depth){
            /*
             *  这是详细拆解 可以成功的
                int root_tmp_total_depth = (left_depth+1);
                int sub_node_tmp = (1<<root_tmp_total_depth) -1;
                cout<<"count node bf: "<<count_node<<endl;
                cout<<"sub_node_tmp: "<<sub_node_tmp<<endl;

                count_node = count_node + sub_node_tmp;
                cout<<"count node af: "<<count_node<<endl;*/

                // 从 root_tmp 开始的总层数
                int root_tmp_total_depth = (left_depth+1);
                // 从 root_tmp 开始的 节点总数 ( 包括 root_tmp)
                int sub_node_tmp = (1<<root_tmp_total_depth) -1;
                // root_tmp 之前计算过的节点的个数 + 当前
                count_node = count_node + sub_node_tmp;

            }
            else if(left_depth != right_depth){
                ++count_node;
                if(root_tmp->left!= nullptr){
                    q_root.push(root_tmp->left);
                }
                if(root_tmp->right!= nullptr){
                    q_root.push(root_tmp->right);
                }

            }
        }

        return count_node;
    }


    //时间复杂度: O(log n × log n)
    //空间复杂度: O(log n)
    // 但是这次用的是 递归版的DFS
    int countNodes_iter (TreeNode* root) {
        if(root == nullptr){
            return 0;
        }

        TreeNode* left_tmp = root->left;
        TreeNode* right_tmp = root->right;

        int count_node;

        int left_depth=0;
        for(;left_tmp!= nullptr;){
            ++left_depth;
            left_tmp= left_tmp->left;
        }

        int right_depth=0;
        for(;right_tmp!= nullptr;){
            ++right_depth;
            right_tmp= right_tmp->right;
        }

        if(left_depth == right_depth){
            // 从 root_tmp 开始的总层数
            int root_tmp_total_depth = (left_depth+1);
            // 从 root_tmp 开始的 节点总数 ( 包括 root_tmp)
            // 2^n - 1
            int sub_node_tmp = (1<<root_tmp_total_depth) -1;

            return sub_node_tmp;
        }
        else if(left_depth != right_depth){
            // 当前根节点 + 左子树总结点 + 右子树总结点
            return 1 + countNodes_iter(root->left)+countNodes_iter(root->right);
        }

    }

};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    std::vector<std::optional<int>> intopt_vec1 = {1,2,3,4,5,6};
    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    //int rs = solut1->countNodes(tree1);
    int rs = solut1->countNodes_iter(tree1);
    cout<<"result"<<endl;
    cout<<rs<<endl;

    return 0;
}


