#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given the head of a linked list, remove the nth node from the end of the list and return its head.
 *
 * Example:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
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
    // head = [1,2,3,4,5], n = 2
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == nullptr){
            return nullptr;
        }
        //
        //           1 -> 2 -> 3 -> 4 -> 5
        // st                  ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5
        //           st             ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5
        //               st              ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5 -> null
        //                     st              ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5 -> null

        // 删除倒数第一个
        //           1 -> 2 -> 3 -> 4 -> 5
        // st             ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5
        //                     st        ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5
        //                          st        ed
        // dmhead -> 1 -> 2 -> 3 -> 4 -> 5 -> null
        // 设置在3前面 是为了能够 链接上2 下一个是4 从而达到删除
        ListNode* dmhead = new ListNode(0,head);
        ListNode* cur_st = dmhead;
        ListNode* cur_ed = cur_st;
        //
        ListNode* cur_todelete= nullptr;



        for(int i=0;i<=n;i++){
            cout<<i<<"-"<<cur_ed->val<<endl;
            //还没到最后 就已经提早到nullptr了, 提示错误
            if(i<n && cur_ed==nullptr){
                cout<<"something worng, n is longer than the len of head"<<endl;
                return nullptr;
            }
            cur_ed = cur_ed->next;

        }

        for(;cur_ed!= nullptr;){
            cur_st= cur_st->next;
            cur_ed= cur_ed->next;
        }

        //如果是倒数0个那意味着什么都不删除
        if(n==0){
            //do nothing
            head = dmhead->next;
        }
        else{
            cur_todelete = cur_st->next;
            cur_st->next = cur_st->next->next;
            head = dmhead->next;
        }

        delete cur_todelete;
        cur_todelete = nullptr;
        delete dmhead;
        dmhead = nullptr;

        return head;
    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    //int int_arr1[] ={1,2,3,4,5};
    int int_arr1[] ={1};
    int* int_arr1P = int_arr1;
    int len = sizeof(int_arr1)/sizeof(int_arr1[0]);
    Solution::ListNode* head1 = solut1->initLinkedlist_ints(int_arr1P,len);
    solut1->myOutput_linklist_int(head1);

    Solution::ListNode* rs_head1 = solut1->removeNthFromEnd(head1,1);
    cout<<"result"<<endl;
    solut1->myOutput_linklist_int(rs_head1);





    return 0;
}


