#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 *
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
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



    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    ListNode* reverseList(ListNode* head){

        //
        //         1 -> 2 -> 3 -> 4 -> 5
        // st      ed
        // null <- 1 -> 2 -> 3 -> 4 -> 5
        //         st   ed
        // null <- 1 <- 2 -> 3 -> 4 -> 5
        //              st   ed
        // null <- 1 <- 2 <- 3 -> 4 -> 5
        ListNode* cur_st = nullptr;     //第一个很重要, 他最开始成为st
        ListNode* cur_ed = head;
        //
        ListNode* cur_tmp= nullptr;
        for(;cur_ed!= nullptr;){
            cur_tmp = cur_ed ->next;
            cur_ed ->next = cur_st;

            cur_st = cur_ed;
            cur_ed = cur_tmp;
        }
        return cur_st ;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    int int_arr1[] ={1,2,3,4,5};
    int* int_arr1P = int_arr1;
    int len = sizeof(int_arr1)/sizeof(int_arr1[0]);
    Solution::ListNode* head1 = solut1->initLinkedlist_ints(int_arr1P,len);
    solut1->myOutput_linklist_int(head1);

    Solution::ListNode* rs_head1 = solut1->reverseList(head1);

    solut1->myOutput_linklist_int(rs_head1);





    return 0;
}


