#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
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

        return nums;
    }

};



int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    int target = 3;


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

void myOutput_VectorBVectorBBintBB(vector<vector<int>> vector1) {

}


