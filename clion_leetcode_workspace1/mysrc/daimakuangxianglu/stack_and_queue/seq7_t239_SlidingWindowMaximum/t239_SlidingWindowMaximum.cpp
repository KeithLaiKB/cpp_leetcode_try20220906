#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;

/**
 *
 *You are given an array of integers nums,
 * there is a sliding window of size k which is moving from the very left of the array to the very right.
 * You can only see the k numbers in the window.
 * Each time the sliding window moves right by one position.
 * Return the max sliding window.
 *
 * Example1:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * Explanation:
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 *  1 [3  -1  -3] 5  3  6  7       3
 *  1  3 [-1  -3  5] 3  6  7       5
 *  1  3  -1 [-3  5  3] 6  7       5
 *  1  3  -1  -3 [5  3  6] 7       6
 *  1  3  -1  -3  5 [3  6  7]      7
 *
 * Example2:
 * Input: nums = [1], k = 1
 * Output: [1]
 *
 *
 *
 */
class Solution {
private:
    class MyQueue{
    private:
        deque<int> dqe1;

    public:
        void mypop(){

        }

        void mypush(int num){

        }

        int front(){
            return dqe1.front();
        }





    };
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
    //时间复杂度: O(n)
    //空间复杂度: O(k)
    //
    // 假设k=3
    // 第一种情况 最前的大
    // 7 3 5 4
    // 7
    // 7 3
    // 7 3 5    最前的大
    //   3 5    准备下一个k组合
    //   3 5 4  这个k组合 (3 5 4)
    //
    // 第二种情况 中间的大
    // 7 9 5 4
    // 7
    // 7 9      中间的大
    //   9      弹出前面
    //   9 5    暗示当前组合是 (7,9,5) 并准备下一个k组合
    //   9 5 4  这个k组合 (9 5 4)
    //
    // 第三种情况 最后的大
    // 7 3 8 4
    // 7
    // 7 3
    // 7 3 8    最后的大
    //     8    弹出前面, 并准备下一个k组合
    //     8 4  这个k组合 暗示了(3 8 4)
    //

    //
    // 总规律是
    // 初始有一组然后选出最大的放头部
    // 此时 已经满足了k元组了
    // 然后一个个加入 每一次加入 都是新的k元组!!!(这个很重要)
    // 每次加入 成为新的k元组, 判断是否比 队头 大,
    //      如果大 则弹出前面的
    //          从而 保证队头是最大的
    //      如果小 则记录下来
    // k个元素中, 队头是最大的,
    //  每增加一个元素 如果当前元素 比上一个元素小 则记录下来放进去
    //  如果当前元素
    //
    // 1 3 1 2 0 5
    //   3 1
    //   3 1 2
    //       2 0 5
    //
    // 1 3 1 2 0 5
    //   3 1
    //     1
    //       0 0 5
    vector<int> maxSlidingWindow(vector<int>& nums, int k){
        deque<int> dqe1;
        vector<int> rs1;

        int i=0;

        // 先塞原始K个
        for(;i<=k-1;i++){
            if(dqe1.empty()){
                dqe1.push_back(nums[i]);
            }
            else if(dqe1.empty()==false){
                // 0 1 2
                // 8 6 (7)
                // 8 6          弹出6                                 i=2, 因为要准备处理7
                // 8
                for(;dqe1.empty()==false && dqe1.back()<nums[i];){
                    dqe1.pop_back();
                }

                // 经过了for循环以后
                // 此时 没有之前的大 或者 队列为空, 直接插入
                dqe1.push_back(nums[i]);
            }
        }
        rs1.push_back(dqe1.front());
        if(dqe1.front()==nums[0]){
            dqe1.pop_front();
        }

        for(;i<=nums.size()-1;i++){
            if(dqe1.empty()){
                dqe1.push_back(nums[i]);
                //然后直接插入结果集合
                rs1.push_back(dqe1.front());
            }
            else if(dqe1.empty()==false){
                // 0 1 2   3
                // 8 6 (7) (9)
                // 8 6          弹出6                                 i=2, 因为要准备处理7
                // 8
                // 8 7          插入7, 然后准备第2轮开始                 i=3>=k, 因为要准备处理9
                // 7            新的一轮k元组是不包括a[i-k]=a[0]的, 此时正好队头是a[0]没有被后来的比下去从而被处理掉过, 所以必须弹出8
                //              弹出7
                // 9            插入9
                for(;dqe1.empty()==false && dqe1.back()<nums[i];){
                    //不要用<= 防止到时准备下一轮的时候 容易把刚插入的给pop掉
                    // 例如
                    // -7 -8 7 5 7 1 6 0
                    // 当中
                    //    -8 7 5 7 过程中的
                    //       7 7 1
                    // 如果不等于的话 会导致 两个7 都会容易丢失
                    dqe1.pop_back();
                }

                // 经过了fore循环以后
                // 此时 没有之前的大 或者 队列为空, 直接插入
                dqe1.push_back(nums[i]);

                //然后插入结果集合
                //因为队头最大, 把队头插入到结果集合里
                rs1.push_back(dqe1.front());

                // 准备下一轮
                // 如果此时 审查的元素 不再是最初的原始 k元组
                // 那么 每一次 添加都需要 删除 每一轮原本应该删除的那个元素
                if(dqe1.front()==nums[i-k+1] ){
                    dqe1.pop_front();
                }
            }
        }


        return rs1;
    }


};


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


