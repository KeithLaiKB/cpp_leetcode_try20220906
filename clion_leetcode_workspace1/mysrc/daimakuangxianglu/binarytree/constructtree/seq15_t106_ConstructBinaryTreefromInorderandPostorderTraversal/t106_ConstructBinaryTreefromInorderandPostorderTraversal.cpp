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
                                    3
                    |                                   |
                    9                                   20
            |               |                   |               |
           null               null             15               7



                          inorder:(9)   (3)   (15,20,7)
                        postorder:(9) (15,7,20)     (3)
                    |                                   |
                   (9)                             (15)(20)  (7)
                   (9)                             (15) (7) (20)
            |               |                   |               |
           null               null             15               7

           //你会发现一个规律  中序遍历 (左子树的A......) 根节点 (右子树的B....)
           //               后序遍历 (左子树的A......) 根节点 (右子树的B....)
 * Example1:
 * Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
 * Output: [3,9,20,null,null,15,7]
 *
 * Example2:
 * Input: inorder = [-1], postorder = [-1]
 * Output: [-1]
 *
 * Constraints:
 * 1 <= inorder.length <= 3000
 * postorder.length == inorder.length
 * -3000 <= inorder[i], postorder[i] <= 3000
 *
 * inorder and postorder consist of unique values.！！！！！！！！！！！
 *
 * Each value of postorder also appears in inorder.
 * inorder is guaranteed to be the inorder traversal of the tree.
 * postorder is guaranteed to be the postorder traversal of the tree.
 *
 * 中序遍历 + 后序遍历 来弄一个树
 * 左中右+左右中
 *
 * 我们可以很确定的是
 * 后序遍历的 最后一位 就是 根节点
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

    // 1. 从后序遍历 中 找到 当前根节点
    // 2. 找到 当前根节点 在 中序遍历中的位置
    //      从而可以 分割 中序遍历 中的 左子树 和 右子树
    //          因此也获得了 左子树的长度  和 右子树的长度
    // 3. 在后序遍历中 根据上面所得的 长度  进行分割
    //
    // 注意 inEnd-inStart+1 = psEnd - psStart+1 他们的长度始终是保持一致的
    TreeNode* backtracking(vector<int>& inorder, vector<int>& postorder, TreeNode* root){

        //limit
        // 这样可以使得 如果后面要用rgchld_len
        // postorder.size() 要 >=2
        // 肯定 rgchld_len>=1,
        if(inorder.size()==0){
            return nullptr;
        }
        else if(inorder.size()==1){
            return new TreeNode(postorder[0]);
        }
        //
        // 因为前面的判断过了
        // 后面使用时 记住 此时的必定是>=2
        // 边界的时候稍微注意以下就好
        //
        //
        //从后续遍历 中 找到 当前根节点
        TreeNode nowRoot=postorder[postorder.size()-1];

        //找到 当前根节点 在 中序遍历中的位置
        int idx_inord_nowRoot=-1;
        for(int i=0;i<=inorder.size()-1;i++){
            if(nowRoot.val == inorder[i]){
                idx_inord_nowRoot=i;
                break;
            }
        }
        if(idx_inord_nowRoot==-1){
            cout<<"cannot find the num"<<endl;
            return nullptr;
        }


        // inorder:
        //      左子树                     根                       右子树
        // (0....idx_inord_nowRoot-1) (idx_inord_nowRoot) (idx_inord_nowRoot+1..........inorder.size()-1)

        // 左子树
        vector<int> inord_lfchild(&inorder[0],&inorder[0]+(idx_inord_nowRoot-1+1));
        // 右子树 (因为 inorder此时>=2 所以尾端的边界不会有问题的)
        vector<int> inord_rgchild(&inorder[0]+(idx_inord_nowRoot+1),&inorder[0]+(inorder.size()-1+1));
        // 此时获得了 左子树的长度, 和右子树的长度
        int lfchld_len = (idx_inord_nowRoot-1 -0) +1;
        int rgchld_len = ((inorder.size()-1)-(idx_inord_nowRoot+1)) +1;
        //

        //

        // 分割后序遍历
        // 根据左子树的 长度 获得
        // inorder:
        //      左子树                             右子树                                     根
        // (0....lfchld_len-1)      (lfchld_len-1+1..........postorder.size()-1-1)   (postorder.size()-1)
        //
        // 左子树  [0....lfchld_len-1],
        // 如果lfchild_len=0,
        // vector<int> psord_lfchild(&postorder[0],&postorder[0]+0)
        // 则产生的是空的vector,所以 没有关系
        vector<int> psord_lfchild(&postorder[0],&postorder[0]+ (lfchld_len-1+1));
        // 右子树  [lfchld_len-1+1..........postorder.size()-1-1]
        // 不用担心边界问题, postorder和 inorder 长度相同的, postorder.size()>=2, 所以这里的 尾端的边界不会有问题的
        // 如果lfchild_len=0,
        // vector<int> psord_rgchild(&postorder[0]+1,&postorder[0]+1)
        // 则产生的是空的vector,所以也 没有关系!!!!
        vector<int> psord_rgchild(&postorder[0]+(lfchld_len-1+1),&postorder[0]+ (postorder.size()-1-1+1));



        return;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size()==0){
            return nullptr;
        }
        TreeNode* root =new TreeNode(postorder[postorder.size()-1]);
        backtracking(inorder, postorder, root);

        return nullptr;
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

    std::vector<int> vec1_inorder = {9,3,15,20,7};
    std::vector<int> vec1_postorder = {9,15,7,20,3};

    Solution::TreeNode* rs = solut1->buildTree(vec1_inorder,vec1_postorder);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    solut1->myOutput_Treenode_int(rs);





    //solut1->myOutput_VectorBtB(rs,0,rs.size()-1);
    cout<<rs<<endl;
    return 0;
}


