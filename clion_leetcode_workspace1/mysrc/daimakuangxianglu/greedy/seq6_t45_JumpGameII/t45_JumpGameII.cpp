#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

/**
 *
 * You are given a 0-indexed array of integers nums of length n.
 * You are initially positioned at nums[0].
 * Each element nums[i] represents the maximum length of a forward jump from index i.
 * In other words, if you are at nums[i], you can jump to any nums[i + j] where:
 *
 * 0 <= j <= nums[i] and
 * i + j < n
 *
 * Return the minimum number of jumps to reach nums[n - 1].
 *
 * The test cases are generated such that you can reach nums[n - 1]. !!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *
 *
 * 和t55一样的位置:
 * nums[i] 代表的是 你最大 可以跨多少而已, 不是必须跨多少
 *
 * 和t55的区别
 * 1 .首先它有 说了 所有的test case都是基于 能够到达最后的终点的,
 *      而t55是有可能到达不了的
 * 2. 就是他有一个 特别要求:
 *      返回的是 最少进行多少跳 就能完成任务
 *
 *  0 1 2 3 4 5 6 7 8
 * {3,3,4,0,1,1,2,1,1}
 *  i=0,    cur_max_id=3            next_max_id=0+(3)
 *  i=1,                            next_max_id=1+(3)             =4 > 3,             keep     better_idx_now=1,        当前位置idx 虽然改变但不需要 count_step++
 *  i=2,                            next_max_id=1+1+(4)           =6 > 4,           change     better_idx_now=2,        当前位置idx 虽然改变但不需要 count_step++,
 *                                                                                                                          你想想看 上一步 如果是因为 better_idx_now 改变了, 从而count_step++
 *                                                                                                                          此时 count_step =2,
 *                                                                                                                          也就是       idx0 -> idx1 ->idx2
 *                                                                                                                          然而是事实是,     idx0 -> idx2 只需要 一步
 *                                                                                                                          也就是 count_step=1(但此时不用操作去加的, 只是这么告诉你)
 *
 *  i=3,    cur_max_id=6            next_max_id=1+1+1+(0)         =3 < 6,             keep     better_idx_now=2,        当 i == cur_max_id 时, next_max_id > cur_max_id
 *                                                                                                                          此时证明 我们是可以走的更远的, 也证明我们可以
 *                                                                                                                          通过在 cur_max_id=3的范围内 跳一次
 *                                                                                                                          然后 走的更远 可达 cur_max_id=6 的位置
 *                                                                                                                          所以 count_step ++
 *  i=4,                            next_max_id=1+1+1+1+(1)       =5 < 6,             keep     better_idx_now=2,
 *  i=5,    cur_max_id=6            next_max_id=1+1+1+1+1+(1)     =6 == 6,            keep     better_idx_now=2,
 *  i=6,    cur_max_id=8            next_max_id=1+1+1+1+1+1+(2)   =8 > 6 && 8==8,   change     better_idx_now=6,        当 i == cur_max_id 时, next_max_id > cur_max_id
 *                                                                                                                          此时证明 我们是可以走的更远的, 也证明我们可以
 *                                                                                                                          通过在 cur_max_id=3的范围内 跳一次
 *                                                                                                                          然后 走的更远 可达 cur_max_id=6 的位置
 *                                                                                                                          所以 count_step ++
 *                                                                                                                      此外 因为 next_max_id == nums[len-1]
 *                                                                                                                          我们就不用看后面的了, 直接跳到最尾巴
 *                                                                                                                          所以 再进行一次 count_step ++
 *  0 -> 2 -> 6 ->8, 一共三次step
 *
 *
 *  每次都 和之前 最大范围 的方案 做比较
 *  一旦 此时走到 cur_max_id, 并且还有 next_max_id > cur_max_id, 则 继续往下走
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    // 首先这种就是分钟类
    //
    int jump(vector<int>& nums) {

        int better_range_idx =0;        //代表从idx=0 开始 到 better_range_idx 这个位置


        int rs=0;

        //只有一个元素的 时候就相当于直接到目的地了
        if(nums.size()==1){
            return 0;
        }


        int cur_max_id=0;
        int next_max_id=0;

        for(int i=0;i<=nums.size()-1;i++){
            int already_walked_counts = i;
            next_max_id = max (next_max_id, already_walked_counts + nums[i]);

            if(i == cur_max_id){
                //第0步不需要 ++rs
                if(i!=0){
                    ++rs;
                }

                cout<<i<<endl;
                cur_max_id = next_max_id;

                // 发现 i==cur_max_id 以后 已经进行过一次 ++rs
                // 并且当前 next_max_id == nums[len-1]
                // 我们直接 再跳一步 直接到最尾巴 并结束游戏
                if(next_max_id >= nums.size()-1){
                    ++rs;
                    break;
                }
            }

        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={3,3,4,0,1,1,2,1,1};
    //int mytarget = 5;

    bool rs1 = -1;
    rs1 = solut1->jump(vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


