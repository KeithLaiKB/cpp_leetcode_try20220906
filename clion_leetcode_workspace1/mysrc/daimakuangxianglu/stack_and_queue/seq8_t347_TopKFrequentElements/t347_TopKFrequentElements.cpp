#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
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
class Solution {
private:

public:
    Solution(){

    }
    ~Solution(){

    }


    void myOutput_VectorBintB(vector<int>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    //  先做初始小根堆, 最后heapsort出来的就是大根堆
    //
    // 小根堆
    //   2
    //  |  |
    //  5  8
    void SiftHeap(int r[], int len, int idx_root){
        int root_tmp, lchild_tmp;    // index
        int temp;
        int idx_compchild;
        root_tmp = idx_root;
        lchild_tmp = idx_root * 2 + 1;
        for(;lchild_tmp<=len-1;){

            //如果<len-1 而不是<=len-1 也就是有 right_child
            if(lchild_tmp<len-1){
                int rchild_tmp=lchild_tmp+1;
                //   9
                //  |  |
                //  8  5
                // 则找出 比较后的最小的那个的index
                if(r[lchild_tmp]>r[rchild_tmp]){
                    idx_compchild = rchild_tmp;
                }
                else{
                    idx_compchild = lchild_tmp;
                }
            }
            //   9
            //  |  |
            //  8  5
            // 调换成
            //   5
            //  |  |
            //  8  9
            if(r[root_tmp]>r[idx_compchild]){
                temp = r[root_tmp];
                r[root_tmp] = r[idx_compchild];
                r[idx_compchild] = r[temp];
            }
            else{
               break;
            }
        }

    }

    //时间复杂度: O(n)
    //空间复杂度: O(k)
    vector<int> topKFrequent(vector<int>& nums, int k) {

    }


};

/**
 * 思路:
 * 1. 出现的频数
 *      一个for统计 丢数组里
 * 2. 找出 出现频数 的前K个
 * @return
 */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    //vector<int> str_vec1={1,3,-1,-3,5,3,6,7};
    //vector<int> str_vec1={1,-1};
    //vector<int> str_vec1={1,3,1,2,0,5};
    vector<int> str_vec1={-7,-8,7,5,7,1,6,0};
    str_vec1.reserve(100);


    int k = 4;



    vector<int> rs1 = solut1->maxSlidingWindow(str_vec1,k);
    cout<<"result"<<endl;

    solut1->myOutput_VectorBintB(rs1, 0, rs1.size()-1);




    return 0;
}


