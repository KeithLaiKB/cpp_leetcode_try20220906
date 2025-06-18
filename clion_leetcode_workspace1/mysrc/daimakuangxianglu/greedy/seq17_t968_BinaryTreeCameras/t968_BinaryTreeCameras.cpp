#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
//#include <cstdint>
#include <climits>

#include <optional>
#include <queue>


using namespace std;

/**
 *
 * You are given the root of a binary tree.
 * We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 *
 *
 * Example1:
 * Input: root = [0,0,null,0,0]
 * Output: 1
 * Explanation: One camera is enough to monitor all nodes if placed as shown.
 *
 *
 * Example2:
 * Input: root = [0,0,null,0,null,0,null,null,0]
 * Output: 2
 * Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.
 *
 *
 *
 *
 *

 */
class Solution {
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


    // 时间复杂度：O(n)
    //
    //
    // 空间复杂度：O(h) 虽然代码狂想录说是O(n)
    //
    int rs=0;

    // 0 代表没有被监控
    // 1 代表这就是监控
    // 2 代表该节点作为父节点 正在监控范围内 (就像是被摄像头画了个圈  不仅能覆盖子节点 还能一样能够覆盖到父节点)
    //                                              (1)
    //                              |                               |
    //                              0                               null
    //                  |                   |
    //                  2                   null
    //          |               |
    //         (1)               null
    //       |     |
    //     null    0
    int postOrderTravesal(TreeNode* root){
        int placedCamera=-1;

        if(root->left == nullptr && root->right == nullptr){
            return 0;
        }

        //
        int left = -1;
        int right = -1;
        if(root->left!= nullptr){
            left = postOrderTravesal(root->left);
        }

        if(root->right!= nullptr){
            right = postOrderTravesal(root->right);
        }

        //只要有一个子节点 是没有装camera (0)
        //这里一定要放监控
        if(left==0||right==0){
            ++rs;
            placedCamera=1;
        }
        // 如果 所有的直接子节点 同时 都是监控范围 (如果只有一个子节点, 那么这个字节点就要==2),
        // 那么此时这个节点 是没法跳跃式的获得 监控的
        // 那么 camera  留着 他的父节点来 放, 这里就不用放了
        else if((left==2&&right==2) || (left==2&&right==-1) ||(left==-1&&right==2)){
            placedCamera=0;
        }
        // 此处是父节点为监控范围(2):
        // 其中一个孩子 是camera, 并且另外一个 是camera(1) 或者是 监控范围内(2)
        // 不能孩子出现0, 因为出现0的话 这里就要放 camera了 也就是1 而不是2了
        else if((left==1&&right!=0)||(left!=0&&right==1)){
            placedCamera=2;
        }


        return placedCamera;
    }

    int minCameraCover(TreeNode* root) {

        // 因为root没有父节点, 而我们的状态是根据父节点来增加的
        // 所以如果root 不是camera 而且 不是 被监控范围, 我们这里需要 自己再加一个 camera
        int root_status = postOrderTravesal(root);
        if(root_status==0){
            ++rs;
        }
        return rs;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    //vector<vector<int>> vec_vec_int1={{1,3},{2,6},{8,10},{15,18}};

    //string str1 = "babacacbdfgdhshf";
    //string str1 = "ababcbacadefegdehijhklij";

    //int num=973;
    //int num=100;
    //int num=120;
    //std::vector<std::optional<int>> intopt_vec1 = {1,2,3,4,std::nullopt,5,6,std::nullopt,std::nullopt,7};
    std::vector<std::optional<int>> intopt_vec1 = {0,0,std::nullopt,0,std::nullopt,0,std::nullopt,std::nullopt,0};
    //std::vector<std::optional<int>> intopt_vec1 = {0,0,std::nullopt,std::nullopt,0,0,std::nullopt,std::nullopt,0,0};

    intopt_vec1.reserve(100);

    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    solut1->myOutput_Treenode_int(tree1);

    int rs1 = solut1->minCameraCover(tree1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1,0,rs1.size()-1);
    return 0;
}


