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
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane.
 * The balloons are represented as a 2D integer array points
 * where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend.
 *
 * You do not know the exact y-coordinates of the balloons.
 * Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis.
 * A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend.
 *
 * There is no limit to the number of arrows that can be shot.
 * A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
 *
 * Given the array points,
 * return the minimum number of arrows that must be shot to burst all balloons.
 *
 *
 * Example1:
 * Input: points = [[10,16],[2,8],[1,6],[7,12]]
 * Output: 2
 * Explanation: The balloons can be burst by 2 arrows:
 * - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
 * - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
 *
 *
 * Example2:
 * Input: points = [[1,2],[3,4],[5,6],[7,8]]
 * Output: 4
 * Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.
 *
 *
 * Example3:
 * Input: points = [[1,2],[2,3],[3,4],[4,5]]
 * Output: 2
 * Explanation: The balloons can be burst by 2 arrows:
 * - Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
 * - Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    template <typename T>
    void myOutput_VectorBvecBtBB(vector<vector<T>> &nums,int st_indx, int ed_indx){
        for(int i=st_indx; i<=ed_indx;i++){
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


    // 时间复杂度：O(nlog n)
    //              sort 用了 O(nlogn)
    // 空间复杂度：O(n)
    //              因为快排 最差情况是倒序, 因此需要O(n)的栈空间
    int findMinArrowShots(vector<vector<int>>& points) {
        int count_arrow=1;

        if(points.size()==0){
            return 0;
        }

        sort(points.begin(), points.end(), mycomp);

        int now_right_bound_idx=points[0][1];
        for(int i=1;i<= points.size()-1;i++){

            // 上一个范围的最右侧  和  当前这个范围的左侧  相离
            if(now_right_bound_idx < points[i][0]){
                now_right_bound_idx = points[i][1];
                ++count_arrow;
            }
            else{
                // 下面min()
                // 相当于剪掉 右侧 不重叠的部分
                // 因为 本身就是 按照左侧大小进行排序
                //      所以剪掉右侧以后, 上一份的范围 肯定是 >= 当前这个剪掉右侧部分 的范围的,
                //      换句话说         当前这个剪掉右侧部分 的范围  是   上一份范围 的子集
                now_right_bound_idx = min ( now_right_bound_idx, points[i][1]);
            }

        }


        return count_arrow;
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


