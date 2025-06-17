#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
//#include <cstdint>
#include <climits>


using namespace std;

/**
 *
 * Given an array of intervals intervals where intervals[i] = [starti, endi],
 *
 * return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
 * Note that intervals which only touch at a point are non-overlapping.
 * For example, [1, 2] and [2, 3] are non-overlapping.
 *
 *
 * Example1:
 * Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
 *
 *
 * Example2:
 * Input: intervals = [[1,2],[1,2],[1,2]]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.
 *
 *
 * Example3:
 * Input: intervals = [[1,2],[2,3]]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 *
 * 和t452比较像
 * 先根据 左边的那个点的大小 拿来排序
 *
 * 因为我们要尽可能的 减少remove的量
 *      每次比较都取右边 的最小值, 从而形成一个 比较紧实的 range
 *      这样可以给 更多的区间 给 后面的集合
 *          从而减少remove的数量
 *
 *  和t452区别
 *  他不是对overlap进行切割, 而是把范围大的 那个范围直接删除
 *  例如此时已经拍好序了
 *      {{1,5},{2,3},{3,7},{7,12}}
 *  当{1,5} 的最右是5> {2,3}里的3
 *  则删掉{1,5}
 *  最终结果是
 *  {{2,3},{3,7},{7,12}}
 *
 */
class Solution {
public:
    Solution() {

    }

    ~Solution() {

    }

    template<typename T>
    void myOutput_VectorBvecBtBB(vector<vector<T>> &nums, int st_indx, int ed_indx) {
        for (int i = st_indx; i <= ed_indx; i++) {
            vector<T> vec_tmp = nums[i];
            for (int j = 0; j <= vec_tmp.size() - 1; j++) {
                cout << vec_tmp[j] << "\t";
            }
            cout << endl;
        }
    }

    bool static mycomp(const vector<int> &a, const vector<int> &b) {
        if (a[0] == b[0]) {
            return a[1] < b[1];
        } else {
            return a[0] < b[0];
        }
    }


    // 时间复杂度：O(nlog n)
    //              sort 用了 O(nlogn)
    // 空间复杂度：O(n)
    //              因为快排 最差情况是倒序, 因此需要O(n)的栈空间
    //
    // 局部优化:
    // 尽量保证 往左靠, 不要霸占右边的位置
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        // 先根据 左边的那个点的大小 拿来排序
        sort(intervals.begin(), intervals.end(), mycomp);

        int removed_count = 0;

        int now_left_bound_idx = intervals[0][0];
        int now_right_bound_idx = intervals[0][1];
        for(int i=1;i<=intervals.size()-1;i++){

            if(now_left_bound_idx<=intervals[i][0] && intervals[i][0]<now_right_bound_idx){
                // {1,5},{2,6} 则 删了 {2,6},
                // 因为 6 会占住右边的位置
                if(now_right_bound_idx<=intervals[i][1]){
                    ++removed_count;
                }
                // {1,5},{2,3} 则 删了 {1,5},
                // 因为 5 会占住右边的位置
                else if(intervals[i][1]<now_right_bound_idx){
                    ++removed_count;
                    now_left_bound_idx = intervals[i][0];
                    now_right_bound_idx=intervals[i][1];
                }
            }
            else{
                now_left_bound_idx = intervals[i][0];
                now_right_bound_idx=intervals[i][1];
            }
        }

        return removed_count;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    vector<vector<int>> vec_vec_int1={{10,16},{2,8},{1,6},{7,12}};



    int rs1 = solut1->findMinArrowShots(vec_vec_int1);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    //solut1->myOutput_VectorBvecBtBB(rs1,0,rs1.size()-1);
    return 0;
}


