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
 * You are given two binary trees root1 and root2.
 * Imagine that when you put one of them to cover the other,
 * some nodes of the two trees are overlapped while the others are not.
 * You need to merge the two trees into a new binary tree.
 * The merge rule is that if two nodes overlap,
 * then sum node values up as the new value of the merged node.
 * Otherwise, the NOT null node will be used as the node of the new tree.
 *
 *
 * Return the merged tree.
 * Note: The merging process must start from the root nodes of both trees.
 *
                                    1
                    |                               |
                    3                               2
            |               |               |               |
            5             null             null              null
       |       |
     null     null

    和
                                    2
                    |                               |
                    1                               3
            |               |               |               |
          null             4             null              7
                        |       |                      |       |
                      null     null                   null     null

    形成了

                                    3(1+2)
                    |                               |
                    4(3+1)                          5(2+3)
            |               |               |               |
           5                4             null              7
                                                        |       |
                                                       null     null

 * Example1:
 * Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
 * Output: [3,4,5,5,4,null,7]
 *
 *
 * 其实就是 如果相同的位置
 *      都 存在数字 就相加
 *      有一个 不是数字 就 把数字 和其下的所有子树搬上去
 *      都不存在 则不理
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

    // 这么写当然 刷题是没问题，
    // 但如果删除 原来的root1,root2的时候 你这个merge出来的树就会出问题了
    //      因为你现在这个merge就像是一个蜘蛛网 连接这root1和 root2
    TreeNode* mytraversal(TreeNode* root1, TreeNode* root2){
        if(root1 == nullptr && root2== nullptr){
            return nullptr;
        }
        else if(root1 != nullptr && root2== nullptr){
            return root1;
        }
        else if(root1 == nullptr && root2!= nullptr){
            return root2;
        }
        else if(root1 != nullptr && root2!= nullptr){

            TreeNode* now_root =new TreeNode(0);
            now_root->val = root1->val + root2->val;

            now_root->left = mytraversal(root1->left,root2->left);
            now_root->right = mytraversal(root1->right,root2->right);

            return now_root;
        }
        return nullptr;

    }

    // 时间复杂度:
    //      最坏情况: 最多递归O(max(n1, n2)) 层。
    //      一般情况: 如果两棵树高度相近，递归深度为 O(log n)，每个层级遍历所有节点。
    //
    //空间复杂度:
    //      最坏情况（链状树）：O(max(n1, n2))（最深递归栈）。
    //      平衡二叉树：O(log max(n1, n2))（二叉树深度）。
    //    额外空间：
    //      你创建了新的二叉树，所以 空间复杂度等于新树的大小，即 O(min(n1, n2))。
    //  所以最终空间复杂度是 O(min(n1, n2))
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        TreeNode* root = mytraversal(root1, root2);
        return root;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};

    std::vector<std::optional<int>> intopt_vec1_tree1 = {1,3,2,5};
    intopt_vec1_tree1.reserve(100);

    std::vector<std::optional<int>> intopt_vec1_tree2 = {2,1,3,std::nullopt,4,std::nullopt,7};
    intopt_vec1_tree2.reserve(100);

    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);
    Solution::TreeNode* tree2 = solut1->initLinkedlist_ints(intopt_vec1_tree1);

    //std::vector<int> vec1_nums = {3,2,1,6,0,5};

    Solution::TreeNode* rs = solut1->mergeTrees(tree1,tree2);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


