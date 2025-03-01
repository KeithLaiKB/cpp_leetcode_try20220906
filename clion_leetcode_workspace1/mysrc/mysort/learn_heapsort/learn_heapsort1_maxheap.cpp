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

    void myOutput_arrInt(int arr[], int st_indx, int ed_indx){
        int len = ed_indx - st_indx +1;
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<arr[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    //  先做初始小根堆, 最后heapsort出来的就是大根堆
    // 这个方法只处理 idx_root 为根节点下的 所有节点
    // 小根堆
    //   2
    //  |  |
    //  8  5
    // 初始化小根堆 他 不一定非要 叶子节点的左边大于右边！！！！
    // 例如不需要像这样
    //   2
    //  |  |
    //  5  8
    //
    // 描述一下
    // step1 从 len/2-1 开始看, 也就是 a[6/2-1]=a[2]=5, 看其下的6和4
    //           9
    //     |          |
    //     8          5
    //  |     |    |      |
    //  1     2    6      4
    //
    // step2
    //           9
    //     |          |
    //     8          4
    //  |     |    |      |
    //  1     2    6      5
    //
    // step3
    //           9
    //     |          |
    //     1          4
    //  |     |    |      |
    //  8     2    6      5
    //
    // step4
    //           1
    //     |          |
    //     9          4
    //  |     |    |      |
    //  8     2    6      5
    //
    // step5
    //           1
    //     |          |
    //     2          4
    //  |     |    |      |
    //  8     9    6      5
    //
    // 从这里看到 他并不是 一个真正完整的堆
    //
    //时间复杂度: O(nlogn)
    //空间复杂度: O(1)
    void SiftHeap_min(int r[], int len, int idx_root){
        int root_tmp, lchild_tmp;    // index
        int temp;
        int idx_compchild;
        root_tmp = idx_root;
        lchild_tmp = idx_root * 2 + 1;
        for(;lchild_tmp<=len-1;){
            idx_compchild=lchild_tmp;

            //如果<len-1 而不是<=len-1 也就是有 right_child
            if(lchild_tmp<len-1){
                int rchild_tmp=lchild_tmp+1;
                //           9
                //     |          |
                //     8          5
                //  |     |    |      |
                //  1     2    6      4
                //
                // 则找出 比较后的最小的那个的index
                if(r[lchild_tmp]>r[rchild_tmp]){                    //如果想把当前的小根堆改成大根堆, 改动这里的 > 变成<
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
            //
            // 注意 我们现在的 这个 初始化小根堆 他 不一定非要 叶子节点的左边大于右边！！！！
            if(r[root_tmp]>r[idx_compchild]){                       //如果想把当前的小根堆改成大根堆, 改动这里的 > 变成<
                temp = r[root_tmp];
                r[root_tmp] = r[idx_compchild];
                r[idx_compchild] = temp;
            }
            else{
               break;
            }

            //
            root_tmp = idx_compchild;
            lchild_tmp = root_tmp * 2 + 1;


            myOutput_arrInt(r, 0, len-1);
        }

    }

    //当前这个function
    //时间复杂度: O(n)
    //空间复杂度: O(1)
    //
    // 但加上了 里面包含的SiftHeap_min 则是
    //时间复杂度: O(nlogn)
    //空间复杂度: O(1)
    //
    // heapsort的前提是完全二叉树, 自己去看我笔记什么是完全二叉树 哪种不属于
    //
    void Heapsort(int r[], int len) {
        int i=len/2-1;
        int temp;
        for(;i>=0;i--){
            SiftHeap_min(r, len, i);
        }
        // ××××××××××××××××××
        // 解释一下 上面这里为什么 要从len/2-1开始
        // 举例一下 当前这个小例子, 与下面的例子无关, 和后面的例子是没有连贯性的
        // len=15; len/2-1=6, 此时a[6]=3
        //                                          1
        //                          |                               |
        //                          2                               2
        //                  |               |               |               |
        //                  3               4               4               3
        //              |       |       |       |       |       |       |       |
        //              5       6       1       8       8       2       6       5
        // ××××××××××××××××××
        //
        //myOutput_arrInt(r, 0, len-1);
        // step5
        //           1
        //     |          |
        //     2          4
        //  |     |    |      |
        //  8     9    6      5
        //
        // step6.1 首尾节点交换
        //           5
        //     |          |
        //     2          4
        //  |     |    |      |
        //  8     9    6     (1)
        //
        // step6.2 siftheap 是从r[0]开始下沉, 也许会从r[2]=4 沉下去 但无论如何这一步是不允许动 1 的
        //           2
        //     |          |
        //     5          4
        //  |     |    |      |
        //  8     9    6     (1)
        //
        // step7.1 首尾节点交换
        //           6
        //     |          |
        //     5          4
        //  |     |    |      |
        //  8     9   (2)    (1)
        //
        // step7.2 siftheap 是从r[0]开始下沉
        // 即使 1<6 但也不能动 1 和 2
        // 因为 1和2已经被要求不动了
        //           4
        //     |          |
        //     5          6
        //  |     |    |      |
        //  8     9   (2)    (1)
        //
        // step8.1 要首尾节点交换
        //           9
        //     |          |
        //     5          6
        //  |     |    |      |
        //  8    (4)  (2)    (1)
        //
        // step8.2 siftheap 是从r[0]开始下沉, 也许会从r[1]=9 沉下去 但无论如何这一步是不允许动动 4 和 2 和 1的
        //           5
        //     |          |
        //     9          6
        //  |     |    |      |
        //  8    (4)  (2)    (1)
        //
        // step8.3 siftheap 是从r[0]开始下沉, 也许会从r[1]=9 沉下去 但无论如何这一步是不允许动动 4 和 2 和 1的
        //           5
        //     |          |
        //     8          6
        //  |     |    |      |
        //  9    (4)  (2)    (1)
        //
        // step9.1 要首尾节点交换
        //           9
        //     |          |
        //     8          6
        //  |     |    |      |
        // (5)   (4)  (2)    (1)
        //
        // step9.2 siftheap 这一步是不能动 5 和 4 和 2 和 1的
        //           6
        //     |          |
        //     8          9
        //  |     |    |      |
        // (5)   (4)  (2)    (1)
        //
        // step10.1 要首尾节点交换
        //           9
        //     |          |
        //     8         (6)
        //  |     |    |      |
        // (5)   (4)  (2)    (1)
        //
        // step10.2 siftheap 这一步是不能动 6 和 5 和 4 和 2 和 1的
        //           8
        //     |          |
        //     9         (6)
        //  |     |    |      |
        // (5)   (4)  (2)    (1)
        //
        // step11.1 要首尾节点交换
        //           9
        //     |          |
        //    (8)        (6)
        //  |     |    |      |
        // (5)   (4)  (2)    (1)
        //
        // step11.2 siftheap 这一步是不能动 8 和 6 和 5 和 4 和 2 和 1的
        //           9
        //     |          |
        //    (8)        (6)
        //  |     |    |      |
        // (5)   (4)  (2)    (1)

        for(i=0;i<=len-1;i++){
            // step6.1 首尾节点交换
            // 变成的样子
            //           5
            //     |          |
            //     2          4
            //  |     |    |      |
            //  8     9    6     (1)
            // 原来的 r[6]=5 = r[(len-1)-i]  和 r[0]=1 进行交换
            //              = r[(7  -1)-0]= r[6]
            // 然后接下来 下一步的调整的范围 是不包含r[6]的
            // 所以 范围 长度就是 len = 6 = len-(i+1) = 7 - (0+1)= 6
            //
            temp=r[0];
            r[0]=r[(len-1)-i];
            r[(len-1)-i]=temp;
            SiftHeap_min(r,len-(i+1), 0);
        }

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


    int arr1[]={9,8,5,1,2,6,4};
    //int arr1[]={9,0,5,1,1,6,4};
    int len = sizeof(arr1)/sizeof(arr1[0]);

    std::vector<int> str_vec1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    str_vec1.reserve(100);


    //solut1->Heapsort(arr1,len);
    //solut1->myOutput_arrInt(arr1, 0, len-1);

    solut1->Heapsort(str_vec1.data(),len);
    solut1->myOutput_VectorBintB(str_vec1, 0, str_vec1.size()-1);



    return 0;
}


