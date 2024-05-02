#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given the head of a linked list, return the node where the cycle begins.
 * If there is no cycle, return null.
 *
 * There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
 * Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed).
 * It is -1 if there is no cycle.
 * Note that pos is not passed as a parameter.
 * Do not modify the linked list.
 *
 * Example:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: tail connects to node index 1
 * 也就是 [2,0,-4]
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}


    };

    ListNode* initLinkedlist_ints(int*& arr, size_t len){
        // 如果需要初始化的长度 <=0 就没必要初始化了
        // 或者如果 提供的数组本身 <=0 也没必要初始化了
        // 我这里这么做 是提供 有可能 数组长度很长(例如100), 但我只需要初始化其中比较短的一部分(5)
        if(len<=0 || sizeof(arr)/sizeof(arr[0])<=0){
            return nullptr;
        }

        ListNode *rs_head =new ListNode(arr[0]);
        ListNode *rs_tail =rs_head;

        for(int i=1; i<=len-1;i++){
            ListNode *tmp =new ListNode(arr[i]);
            rs_tail->next = tmp;
            rs_tail=tmp;
        }
        return rs_head;
    }

    void myOutput_linklist_int(ListNode*& head){
        ListNode *ed_tmp =head;
        for(; ed_tmp!= nullptr; ed_tmp=ed_tmp->next){
            cout<<ed_tmp->val<<"\t";
        }
        cout<<endl;
    }

    void myOutput_linklist_int(ListNode*& head, int len){
        ListNode *ed_tmp =head;
        for(int i=0; ed_tmp!= nullptr && i<=len-1; i++){
            cout<<ed_tmp->val<<"\t";
            ed_tmp=ed_tmp->next;
        }
        cout<<endl;
    }



    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    // head = [1,2,3,4,5], n = 2
    ListNode *detectCycle(ListNode *head) {
        if(head == nullptr){
            return nullptr;
        }

        ListNode* cur_slow = head;
        ListNode* cur_fast = head;
        //
        ListNode* cur_cyclenode= nullptr;

        ListNode* cur_indx_x = head;
        ListNode* cur_indx_z = nullptr;

        for(;cur_fast!= nullptr && cur_fast->next!=nullptr;){
            cur_slow = cur_slow->next;
            cur_fast = cur_fast->next->next;

            if(cur_slow == cur_fast){
                int pos=0;
                cur_indx_z = cur_fast;

                for(;cur_indx_x != cur_indx_z;){
                    cur_indx_x = cur_indx_x->next;
                    cur_indx_z = cur_indx_z->next;
                    pos = pos + 1;
                }
                cur_cyclenode = cur_indx_x;
                cout<<"find pos:"<<pos<<endl;
                break;
            }
        }

        return cur_cyclenode;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    //int int_arr1[] ={1,2,3,4,5};
    int int_arr1[] ={3,2,0,-4};
    int* int_arr1P = int_arr1;
    int len = sizeof(int_arr1)/sizeof(int_arr1[0]);

    //构造普通链表
    Solution::ListNode* head1 = solut1->initLinkedlist_ints(int_arr1P,len);
    //构造回环
    int pos = 1;
    Solution::ListNode* tail1 = head1;
    for(;tail1->next!= nullptr;){
        tail1=tail1->next;
    }
    Solution::ListNode* cyclenode = head1;
    for(int i=0;i<=pos-1;i++){
        cyclenode = cyclenode->next;
    }
    tail1->next = cyclenode;      //做环
    cout<<"tail next"<<endl;
    cout<<tail1->next->val<<endl;


    solut1->myOutput_linklist_int(cyclenode,len-pos);

    Solution::ListNode* rs_head1 = solut1->detectCycle(head1);
    cout<<"result"<<endl;
    cout<<rs_head1->val<<endl;





    return 0;
}


