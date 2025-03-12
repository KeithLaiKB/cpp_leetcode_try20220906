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
 * Given two integer arrays inorder and postorder
 * where inorder is the inorder traversal of a binary tree
 * and postorder is the postorder traversal of the same tree,
 * construct and return the binary tree.
 *
                                    6
                    |                               |
                    3                               5
            |               |               |               |
           null             2               0              null
                        |       |       |       |
                      null      1     null     null


 * Example1:
 * Input: nums = [3,2,1,6,0,5]
 * Output: [6,3,5,null,2,0,null,null,1]
 * Explanation: The recursive calls are as follow:
 *      The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
 *          The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
 *              Empty array, so no child.
 *              The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
 *                  Empty array, so no child.
 *                  Only one element, so child is a node with value 1.
 *          The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
 *              Only one element, so child is a node with value 0.
 *              Empty array, so no child.
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
    //[3,2,1,6,0,5]
    //                                  6
    //                  |                               |
    //                  3                               5
    //          |               |               |               |
    //         null             2               0              null
    //                      |       |       |       |
    //                    null      1     null     null
    //
    // for 数组 获得 当前数组中的 max
    // Node(max)->left = mytraversal(max的左边);
    // ode(max)->right = mytraversal(max的右边);
    TreeNode* mytraversal(vector<int>&nums, int st_now, int ed_now){
        int max_num = INT_MIN;
        int max_num_idx = INT_MIN;
        for(int i=st_now;i<=ed_now;i++){
            if(max_num<nums[i]){
                max_num=nums[i];
                max_num_idx=i;
            }
        }

        if(max_num_idx==INT_MIN) return nullptr;


        TreeNode* root_now = new TreeNode(max_num);
        //
        // st_now .... max_idx .... ed_now
        // [st_now, max_idx-1]
        root_now->left = mytraversal(nums, st_now, max_num_idx-1);
        // [max_idx+1, ed_now]
        root_now->right = mytraversal(nums, max_num_idx+1, ed_now);

        return root_now;

    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode* root = mytraversal(nums, 0, nums.size()-1);
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
/*
    std::vector<std::optional<int>> intopt_vec1_inorder = {5,4,8,11,std::nullopt,13,4,7,2,std::nullopt,std::nullopt,std::nullopt,1};
    intopt_vec1_inorder.reserve(100);

    std::vector<std::optional<int>> intopt_vec1_postorder = {5,4,8,11,std::nullopt,13,4,7,2,std::nullopt,std::nullopt,std::nullopt,1};
    intopt_vec1_postorder.reserve(100);
*/

    std::vector<int> vec1_nums = {3,2,1,6,0,5};

    Solution::TreeNode* rs = solut1->constructMaximumBinaryTree(vec1_nums);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


