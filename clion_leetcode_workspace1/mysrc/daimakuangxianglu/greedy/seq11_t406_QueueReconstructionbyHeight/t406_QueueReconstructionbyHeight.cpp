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
 * You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order).
 *
 * Each people[i] = [hi, ki] represents
 * the ith person of height hi
 * with exactly ki other people in front who have a height greater than or equal to hi.
 *
 * Reconstruct and return the queue that is represented by the input array people.
 *
 * The returned queue should be formatted as an array queue,
 * where queue[j] = [hj, kj] is the attributes of the jth person in the queue
 * (queue[0] is the person at the front of the queue).
 *
 *
 * Example1:
 * Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 * Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
 * Explanation:
 * Person 0 has height 5 with no other people taller or the same height in front.
 * Person 1 has height 7 with no other people taller or the same height in front.
 * Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
 * Person 3 has height 6 with one person taller or the same height in front, which is person 1.
 * Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
 * Person 5 has height 7 with one person taller or the same height in front, which is person 1.
 * Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
 *
 * Example2:
 * Input:  people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
 * Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
 *
 *
 * 根据{h,k} 中的k 对 h 进行排序
 * Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
 * 排序后 = {{7,0},{7,1},{6,1},{5,0},{5,2},{4,4}}
 * rs =
 *   position:        0       1       2      3        4       5
 *                  {7,0}
 *                  {7,0}   {7,1}
 *                  因为我们身高按照从大到小已经 预先排序好了, 需要把 {6,1} insert 到 idx = 1的时候的时候
 *                  就会在{7,1}的前面插入, 于是得到
 *                  {7,0}   {6,1}   {7,1}
 *                  {5,0}   {7,0}   {6,1}   {7,1}
 *                  下一步, 把 {5,2} insert 到 idx = 2 ,
 *                  检测 发现 确实 {5,0} 和 {7,0} 中的 5 和 7 都是小于或等于 {5,2}中的5
 *                  5 和 7 这一共2个数字, 对得上:
 *                  {5,0}   {7,0}   {5,2}   {6,1}   {7,1}
 *                  {5,0}   {7,0}   {5,2}   {6,1}   {4,4}   {7,1}
 *
 * Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
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
            return a[0]>b[0];
        }
    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(1)

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),mycomp);

        vector<vector<int>> rs={};
        rs.reserve(people.size());      //这样可以稍微优化一下效率, 不然每次insert 都有可能 底层浪费时间去扩容

        for(int i=0;i<=people.size()-1;i++){
            int insert_pos_tmp = people[i][1];
            rs.insert(rs.begin()+ insert_pos_tmp, people[i]);
        }

        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    //vector<int> vec_int1={5,5,10,10,20};
    //vector<int> vec_int2={2,-3,-1,5,-4};
    vector<vector<int>> vec_vec_int1={{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}};



    vector<vector<int>> rs1 = solut1->reconstructQueue(vec_vec_int1);
    cout<<"result:"<<endl;
    //cout<<rs1<<endl;
    solut1->myOutput_VectorBvecBtBB(rs1,0,rs1.size()-1);
    return 0;
}


