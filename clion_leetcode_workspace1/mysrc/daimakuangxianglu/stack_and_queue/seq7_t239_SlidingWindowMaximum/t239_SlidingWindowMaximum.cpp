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





    }
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
    //空间复杂度: O(n)
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
    // 一个个加入
    // 每次加入, 判断是否比前面的大, 如果大 则弹出前面的
    vector<int> maxSlidingWindow(vector<int>& nums, int k){
        deque<int> dqe1;
        vector<int> rs1;

        int i=0;

        // 先塞原始K个
        for(;i<=k-1;i++){
            if(dqe1.empty()){
                dqe1.push_back(nums[i]);
            }
            // 7 3 8 4
            // 7
            // 7 3
            // 7 3 8    最后的大
            //     8    弹出前面, 并准备下一个k组合
            //

            else if(dqe1.empty()==false && nums[i]>=dqe1.back()){

                //弹走前面的
                for(;dqe1.empty()!=false;){
                    dqe1.pop_back();
                }
                //再插入
                dqe1.push_back(nums[i]);
            }
        }
        rs1.push_back(dqe1.front());
        dqe1.pop_front();


        if(i<=k-1){
            //not enough element to composit in to 3
            return {};
        }


        int now_k=1;
        // 后续再一个个加
        for(i=2+1; i<=nums.size()-1; i++,now_k++){

            // logic start
            // 塞入
            // 如果为空 直接插入
            if(dqe1.empty()){
                dqe1.push_back(nums[i]);
            }

            // 如果不为空 并且
            // 假设是
            // 7 8 8(还没插入) 但我算它是准备的组合
            //          先弹走前面的7 8
            //     8    再插入
            else if(dqe1.empty() == false && nums[i] >= dqe1.front() ) {
                //弹走前面的
                for(;dqe1.empty()!=false;){
                        dqe1.pop_front();
                }
                //再插入
                dqe1.push_back(nums[i]);
            }
            // 如果不为空 并且 并之前的都小 则不插入
            else if(dqe1.empty() == false && nums[i] < dqe1.front() ) {
                //do nothing
            }

            //
            if(now_k==3){
                rs1.push_back(dqe1.front());
            }
        }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();


    vector<int> str_vec1={1,3,-1,-3,5,3,6,7};
    str_vec1.reserve(100);


    int k = 3;



    vector<int> rs1 = solut1->maxSlidingWindow(str_vec1,k);
    cout<<"result"<<endl;

    solut1->myOutput_VectorBintB(rs1, 0, rs1.size()-1);




    return 0;
}


