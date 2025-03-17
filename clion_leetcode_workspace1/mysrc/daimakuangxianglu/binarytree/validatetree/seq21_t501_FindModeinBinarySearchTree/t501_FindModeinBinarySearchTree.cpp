#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <optional>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 *
 * Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.
 * If the tree has more than one mode, return them in any order.
 * Assume a BST is defined as follows:
 *      The left subtree of a node contains only nodes with keys less than or equal to the node's key.
 *      The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
 *      Both the left and right subtrees must also be binary search trees.
 *
 * Example1:
 * Input: root = [1,null,2,2]
 * Output: [2]
 *
 * My Example1:
 * Input: root = [1,null,2,2,3,3]
 * Output: [2,3]
 *
 * 因为 最高重复次数 是2
 * 但是
 *  重复两次 的不仅仅只有一个结点
 *  因为重复的有 2和3
 *  所以要返回2和3
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


    //  从大到小
    bool static mycomp(const pair<int,int> &a,const pair<int,int> &b){
        return a.second>b.second;
    }
    //
    // BST
    // 中序遍历 就会出现 递增 的顺序
    //TreeNode searched_prev_node;


    int mytraversal(TreeNode* root1, unordered_map<int,int> &map1){
        if(root1== nullptr){
            return -1;
        }

        //左
        mytraversal(root1->left,map1);
        //中
        // 初始化 或 已存在的对应map的value+1
        if(map1.find(root1->val)!=map1.end()){
            map1[root1->val]++;
        }
        else{
            map1[root1->val]=0;
        }
        //右
        mytraversal(root1->right,map1);
        return 0;
    }


    // 时间复杂度: O(n)
    //      中序遍历一次所有节点，n 为树的节点总数。遍历后计算最小差值也为 O(n)，整体为 O(n)。
    //      unorder_map 插入是O(1), 一共n个数字 所以O(n)
    //      sort: O(nlogn)
    //      然后for vec_map1 是O(n)
    //      所以一共是 O(n)+O(n)+O(nlogn)+O(n) = O(nlogn)
    //
    // 空间复杂度:	O(n)
    // 使用额外数组 vector<int> 保存所有频率值，因此额外空间为 O(n)。另外递归栈空间，最坏 O(n)，综合后仍为 O(n)。

    vector<int> findMode(TreeNode* root) {
        //
        vector<int> rs={};
        rs.reserve(100);

        //
        // num, freq
        unordered_map<int,int> map_num_freq;
        mytraversal(root,map_num_freq);

        //大到小排列
        vector<pair<int,int>> vec_map1(map_num_freq.begin(),map_num_freq.end());
        sort(vec_map1.begin(),vec_map1.end(), mycomp);

        // vec[0] 是最大的，如果例如 2,2,3,3,1
        // 出现最大频率的就有两个，
        // 最后的1发现 只出现1次就可以不理, break就行了
        for(int i=0;i<=vec_map1.size()-1;i++){
            if(vec_map1[i].second==vec_map1[0].second){
                rs.push_back(vec_map1[i].first);
            }
            else{
                break;
            }
        }

        return rs;
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

    std::vector<std::optional<int>> intopt_vec1_tree1 = {1,std::nullopt,2,2};
    intopt_vec1_tree1.reserve(100);
    Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1_tree1);


    int target_num= 2;

    vector<int> rs1 = solut1->findMode(tree1);
    //Solution::TreeNode* tree1 = solut1->initLinkedlist_ints(intopt_vec1);

    cout<<"result"<<endl;
    //solut1->myOutput_Treenode_int(rs);





    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    //cout<<rs1<<endl;
    return 0;
}


