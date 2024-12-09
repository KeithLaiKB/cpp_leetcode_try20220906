#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
using namespace std;

/**
 *  层序遍历
 *  [1,2,2,3,4,4,3,5,6,null,8,8,null,6,5]

                                    1
                    |                               |
                    2                               2
            |               |               |               |
            3               4               4               3
        |       |       |       |       |       |       |       |
        5       6     null      8       8      null     6       5

    [1]
    [2, 2]
    [2l,    2'r,    2r,     2'l]
    [3,     3,      4,      4]

    取出 并弹出 2l 和2'r 判断相等
        然后才塞入   [3l, 3'r, 3r, 3'l]
    [2r,    2'l,    3l,     3'r,    3r,     3'l]
    [4,     4,      5,      5,      6,      6]

    取出 并弹出 2r 和2'l' 判断相等
        然后塞入  [4l, 4'r, 4r, 4'l]
            因为 4l 和 4'r 的值是 null 所以不塞入
    [3l,     3'r,    3r,     3'l,   4r,     4'l]
    [5,      5,      6,      6,     8,      8]

    取出 并弹出  3l 和 3'r 后 3l 和 3'r 的所有左右叶子节点都是null所以都不塞入
    [3r,     3'l,   4r,     4'l]
    [6,      6,     8,      8]

    取出 并弹出  3r 和 3'l后 3r 和 3'l 的所有左右叶子节点都是null所以都不塞入
    [4r,     4'l]
    [8,      8]

    取出 并弹出  4r 和 4'l后 4r 和 4'l 的所有左右叶子节点都是null所以都不塞入
    []
    []
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
    //  对于BFS来说  影响 主要迭代(iteration)是queue的大小
    //  最低部的叶子节点有可能接近n/2所以
    //      所以是 O(n)
    //
    // 如果你使用DFS 他每一层不是所有节点都存储的, 所以他就会出现 O(logn)~O(n)的状况
    // 如果完全平衡二叉树 每一层就存储一个, 总个数 是 2^n=k
    // 所以 层数n =log(2n)=O(logn)
    bool isSymmetric(TreeNode* root) {

        if(root == nullptr){
            return false;
        }

        queue<TreeNode*> q_root;
        bool rs1=true;

        q_root.push(root->left);
        q_root.push(root->right);
        for(;q_root.empty()==false;){
            TreeNode* left_tmp = q_root.front();
            q_root.pop();
            TreeNode* right_tmp = q_root.front();
            q_root.pop();

            // 都是空相等
            if(left_tmp== nullptr && right_tmp==nullptr){
                continue;
            }
            else if(left_tmp!= nullptr && right_tmp!=nullptr){
                if(left_tmp->val == right_tmp->val){
                    //放入左和右分别的叶子节点
                    q_root.push(left_tmp->left);        //ll
                    q_root.push(right_tmp->right);      //rr
                    q_root.push(left_tmp->right);       //lr
                    q_root.push(right_tmp->left);       //rl
                }
                // 左右的值不想等, 结束
                else{
                    rs1=false;
                    break;
                }
            }
            // 左右有一个是空的 一个不是空的, 导致不相等
            else{
                rs1=false;
                break;
            }

        }


        return rs1;
    }


};

/**
 * @return
 */
int main() {
    Solution* solut1 = new Solution();



    std::vector<std::optional<int>> intopt_vec1 = {1,2,2,3,4,4,3,5,6,std::nullopt,8,8,std::nullopt,6,5};
    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    bool rs = solut1->isSymmetric(tree1);
    cout<<"result"<<endl;
    cout<<rs<<endl;

    return 0;
}


