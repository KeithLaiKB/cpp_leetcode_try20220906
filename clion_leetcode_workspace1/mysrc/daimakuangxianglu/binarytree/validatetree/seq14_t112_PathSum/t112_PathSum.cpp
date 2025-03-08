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
 * Given the root of a binary tree and an integer targetSum,
 *
 * return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
 *
 * A leaf is a node with no children.
 *
                                    5
                    |                                   |
                    4                               8
            |               |                   |               |
           11               null                13               4
        |       |                           |       |       |       |
        7       2                           null   null    null      1
 * Example1:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
 * Output: true
 * Explanation: The root-to-leaf path with the target sum is shown.
 * 5->4->11->2=5+4+11+2=9+11+2=22
 * 所有路径中 存在 一条路径上 的sum=22
 *
 *
 * 我一看就知道要DFS了
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


    int backtracking(TreeNode* root, const int targetSum, int &nowSum){
        //limit
        // root == nullptr  如果是原来那个大树的根节点 已经在上面那个大入口已经解决了
        //                  如果是后面的节点, 他们在for里是不会继续 用backtracking的,
        // 所以我们这里不需要 判定 if(root == nullptr)!!!!!
        //
        // 所以我们直接判断 他是叶子节点就可以了
        if(root->left== nullptr && root->right== nullptr){
            //如果相同 则返回值
            if(nowSum == targetSum){
                return nowSum;
            }
            //找不到则
            else{
                return INT_MIN;
            }
        }

        //deal
        vector<TreeNode*> children1= {root->left,root->right};
        int rs_flag=INT_MIN;

        //for
        for(TreeNode* chld : children1){
            if(chld!= nullptr){

                nowSum += chld->val;        // 子节点的值在这里处理
                rs_flag = backtracking(chld, targetSum, nowSum);
                nowSum -= chld->val;        // 子节点的值在这里pop

                // 如果不相同就证明找到了 可以返回了
                if(rs_flag!=INT_MIN){
                    return rs_flag;
                }
            }
            else if(chld== nullptr){
                // do nothing with backend because it is null
            }
        }
        return  rs_flag;

    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        int nowSum=0;

        int rs=INT_MIN;

        if (root == nullptr){
            return false;
        }

        // 原始根节点的值在这里就开始 处理,
        // 因为到backtracking就不处理原始根节点了
        nowSum +=root->val;
        rs = backtracking(root,targetSum,nowSum);

        //当然了你也可以 在这里pop掉根节点的值, 只是多数情况下没必要
        //因为这里主要以rs的值为返回值, 并且 nowSum在这里只是值传递
        //nowSum -=root->val;

        if (rs!=INT_MIN){
            return true;
        }
        else{
            return false;
        }
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    //std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,std::nullopt,std::nullopt,6,5};
    //std::vector<std::optional<int>> intopt_vec1 = {3,9,20,std::nullopt,std::nullopt,15,7};
    std::vector<std::optional<int>> intopt_vec1 = {5,4,8,11,std::nullopt,13,4,7,2,std::nullopt,std::nullopt,std::nullopt,1};
    intopt_vec1.reserve(100);
    int targetsum=22;


    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    solut1->myOutput_Treenode_int(tree1);



    int rs = solut1->hasPathSum(tree1,targetsum);
    cout<<"result"<<endl;
    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


