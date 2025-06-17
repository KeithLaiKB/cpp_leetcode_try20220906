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
 * Given an array of intervals where intervals[i] = [starti, endi],
 * merge all overlapping intervals,
 * and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 *
 * Example1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 *
 * Example2:
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 * 和t452 最像
 * 和t436 像
 * 需要进行排序, 但是 他不用进行什么切割, 他就是 取最大的范围, 就是并集
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    template <typename T>
    void myOutput_VectorBvecBtBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            vector<T> vec_tmp = nums[i];
            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<vec_tmp[j]<<"\t";
            }
            cout<<endl;
        }
    }

    bool static mycomp(const vector<int> &a, const vector<int> &b){
        if(a[0]==b[0]){
            return a[1]<b[1];
        }
        else{
            return a[0]<b[0];
        }
    }



    // 时间复杂度：O(nlogn)
    //      sort需要 O(nlogn)
    //
    // 空间复杂度：O(logn)
    //      排序的空间复杂度 是O(logn)
    //
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> rs;
        rs.reserve(100);

        if(intervals.size()==0){
            return {};
        }

        sort(intervals.begin(),intervals.end(), mycomp);

        int now_range_left=intervals[0][0];
        int now_range_right=intervals[0][1];
        rs.push_back({now_range_left, now_range_right});

        for(int i=1;i<=intervals.size()-1;i++){
            int lf_tmp= intervals[i][0];
            int rt_tmp= intervals[i][1];

            // 如果此元素的左边界 在 当前范围内
            if(now_range_left<=lf_tmp && lf_tmp<=now_range_right){
                now_range_right = max(rt_tmp, now_range_right);
                //
                // 更改rs当前最新的右边界
                rs.back()[1]=now_range_right;
            }
            //如果不在
            else{

                // 重置范围
                now_range_left=lf_tmp;
                now_range_right=rt_tmp;

                //放进结果集
                rs.push_back({now_range_left, now_range_right});
            }

        }
        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    vector<vector<int>> vec_vec_int1={{10,16},{2,8},{1,6},{7,12}};

    //string str1 = "babacacbdfgdhshf";
    //string str1 = "ababcbacadefegdehijhklij";

    vector<int> rs1 = solut1->merge(vec_vec_int1);
    cout<<"result:"<<endl;
    //cout<<rs1<<endl;
    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    return 0;
}


