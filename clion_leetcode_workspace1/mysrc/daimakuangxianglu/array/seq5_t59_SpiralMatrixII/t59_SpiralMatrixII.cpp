#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

/**
 *
 * Given a positive integer n,
 * generate an n x n matrix filled with elements from 1 to n2 in spiral order.
 *
 * Example:
 * Input: n = 3
 * Output: [[1,2,3],[8,9,4],[7,6,5]]
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_VectorBVectorBBintBB(vector<vector<int>>& nums){
        for(int i=0;i<=nums.size()-1;i++){
            vector<int> vec_tmp = nums[i];
            for(int j=0;j<=vec_tmp.size()-1;j++){
                cout<<nums[i][j]<<"\t";
                if(j==vec_tmp.size()-1){
                    cout<<endl;
                }
            }
        }
    }

    // 时间复杂度：O(n*n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> nums(n, vector<int>(n));
        int st_y = 0;
        int st_x = 0;

        int max_range_idx = n-1 -1;
        int loop = n/2;
        bool need_final_fill = n%2!=0?true:false;

        int now_num = 1;

        int row=st_y;
        int col=st_x;

        if (n==1) {
            nums[0][0] = 1;
            return nums;
        }

        for (;loop>0; loop--) {

            row=st_y;
            col=st_x;

            // top border (left to right)
            for (;col<=max_range_idx;) {
                nums[st_y][col] = now_num;
                ++col;
                ++now_num;
                myOutput_VectorBVectorBBintBB(nums);
                cout<<"max_range_idx:"<<max_range_idx<<endl;
                cout<<endl;
            }

            // right border (top to bottom)
            for (;row<=max_range_idx;) {
                nums[row][col] = now_num;
                ++row;
                ++now_num;
                myOutput_VectorBVectorBBintBB(nums);
                cout<<endl;
            }

            // bottom border (right to left)
            for (;col>=st_x+1;) {
                nums[row][col] = now_num;
                --col;
                ++now_num;
                myOutput_VectorBVectorBBintBB(nums);
                cout<<endl;
            }

            // left border (bottom to top)
            for (;row>=st_y+1;) {
                nums[row][col] = now_num;
                --row;
                ++now_num;
                myOutput_VectorBVectorBBintBB(nums);
                cout<<endl;
            }

            st_y = row+1; //because left border would minus one more
            st_x = col+1;
            --max_range_idx;
        }

        if (need_final_fill) {
            nums[n/2][n/2] = now_num;
            cout<<"filled middle one"<<endl;
        }

        return nums;
    }

};



int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    int target = 4;


    vector<vector<int>> result= solut1->generateMatrix(target);

    solut1->myOutput_VectorBVectorBBintBB(result);
    /*for(int i=0;i<=intvec_result.size()-1;i++){
        cout<<intvec_result[i]<<"\t";
        if(i==intvec_result.size()-1){
            cout<<endl;
        }
    }*/



    return 0;
}




