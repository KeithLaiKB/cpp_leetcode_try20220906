#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
using namespace std;

/**
 *
 * Given an integer array nums and an integer k,
 * return the k most frequent elements. You may return the answer in any order.
 *
 * Example1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 *
 *
 * Example2:
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 * Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 */
class MyComparison{
public:
    // 小根堆
    // 谁的second值越小 放的就是越top, 然后就是top 的先被Pop掉
    bool operator()(const pair<int,int> &num1_freq1, const pair<int,int> &num2_freq2){
        return num1_freq1.second > num2_freq2.second;
    }
};
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


    // [1,null,2,3]
    //       1
    //    |      |
    //   null    2
    //         |    |
    //         3    null
    //
    //
    // 塞1进去根节点队列
    // queue:[1]
    //
    // 弹出1 然后对根节点(局部) 1 进行其 子节点的 装配
    // 装配完 左边null 右边2, 然后把2 丢到 根节点队列
    // queue:[2]
    //       1
    //    |      |
    //   null    2
    //
    // 弹出2 然后对根节点(局部) 2 进行其 子节点的 装配
    // 装配完 左边3 右边null, 然后把3 丢到 根节点队列
    // queue:[3]
    //       2
    //    |      |
    //    3      null
    //
    //
    // const 代表不能修改 arr
    // & 代表的是引用  而不是 拷贝个副本进来
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
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr){
            return {};
        }

        vector<int> rs_vec = {};

        //左
        vector<int> left_tmp=inorderTraversal(root->left);
        rs_vec.insert(rs_vec.end(),left_tmp.begin(),left_tmp.end());

        //中
        rs_vec.push_back(root->val);
        cout<<root->val<<endl;

        //右
        vector<int> right_tmp=inorderTraversal(root->right);
        rs_vec.insert(rs_vec.end(),right_tmp.begin(),right_tmp.end());
        return rs_vec;
    }


};

/**
 * @return
 */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();



    std::vector<std::optional<int>> intopt_vec1 = {1, 2, 3, 4, 5, std::nullopt, 8, std::nullopt, std::nullopt, 6, 7, 9};
    intopt_vec1.reserve(100);




    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);
    //solut1->myOutput_Treenode_int(tree1);

    vector<int> rs_vec1= solut1->inorderTraversal(tree1);
    cout<<"result"<<endl;


    return 0;
}


