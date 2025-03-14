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
 * Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
 *
 *
 *
 * 总之就是 这是二叉搜索树
 *
 * 里面的任意节点 做减法 然后呢 绝对值的最小值
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


    //
    // BST
    // 中序遍历 就会出现 递增 的顺序
    int mytraversal(TreeNode* root1, vector<int> &rs1){
        if(root1== nullptr){
            return -1;
        }

        //左
        mytraversal(root1->left,rs1);
        //中
        rs1.push_back(root1->val);
        //右
        mytraversal(root1->right,rs1);
        return 0;
    }

    // 时间复杂度: O(n)
    //      中序遍历一次所有节点，n 为树的节点总数。遍历后计算最小差值也为 O(n)，整体为 O(n)。
    //空间复杂度:	O(n)
    // 使用额外数组 vector<int> 保存所有节点值，因此额外空间为 O(n)。另外递归栈空间，最坏 O(n)，综合后仍为 O(n)。
    int getMinimumDifference(TreeNode* root) {
        vector<int> rs = {};
        mytraversal(root, rs);

        int min_dif= INT_MAX;
        for(int i=0;i<=rs.size()-1-1;i++){
            int min_tmp=rs[i+1]-rs[i];
            if(min_tmp<min_dif){
                min_dif = min_tmp;
            }
        }

        return min_dif;
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

    bool rs = solut1->getMinimumDifference(tree1);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    //solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


