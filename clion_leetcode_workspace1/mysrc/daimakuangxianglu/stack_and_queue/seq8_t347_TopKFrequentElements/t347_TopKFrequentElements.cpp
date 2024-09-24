#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
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
class MyComparison{
public:
    // 小根堆
    // 谁的second值越小 放的就是越top, 然后就是top 的先被Pop掉
    bool operator()(const pair<int,int> &num1_freq1, const pair<int,int> &num2_freq2){
        return num1_freq1.second > num2_freq2.second;
    }
};
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



    //时间复杂度: O(nlogk) n代表的是n个元素, k代表个数,
    //      这一次他使用了priorityqueue 这个是使用了 heap的
    //          heap每次插入就需要整个堆预先知道的大小k 也就是时间复杂度每次要 O(log(k))
    //          哪怕是删除也只是 O(log(k)), 大不了也就是 O(2*log(k))
    //          然后一共用n个数字 进行for循环 考虑是否插入 是n 次
    //          所以是O(nlog(k))
    //空间复杂度: O(k)
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //
        unordered_map<int,int> map;
        // count 每个数字的出现频数 并放入map
        for(int i=0;i<nums.size();i++){
            int key = nums[i];
            map[key]++;
        }

        // 建立优先队列
        priority_queue< pair<int, int>, vector<pair<int,int>>, MyComparison> prique1;
        // 塞进去
        for(unordered_map<int,int>:: iterator it_tmp=map.begin();it_tmp!=map.end();it_tmp++){
            prique1.push(*it_tmp);

            // 下面这段代码只是优化使用空间 把n个空位的队列缩小成k个而已
            // 可以删掉这段
            // 例如 假设题目要求k=3
            // 频数 2 4 11  已经再插入一个频数8的了
            // 此时 为 2 4 8 11 >k=3
            // 于是把2给弹出
            if(prique1.size()>k){
                prique1.pop();
            }
        }

/*        while (!prique1.empty()) {
            cout<<"nums:"<<prique1.top().first<<" freq:"<<prique1.top().second << endl; // 打印优先级最高的元素
            prique1.pop(); // 移除优先级最高的元素
        }*/

        // 把最大频数的对应那个数字 放在最前面
        vector<int> rs1(k);
        for(int i=k-1;i>=0;i--){
            rs1[i]=prique1.top().first;
            prique1.pop();
        }
        return rs1;
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


    //vector<int> str_vec1={1,3,-1,-3,5,3,6,7};
    //vector<int> str_vec1={1,-1};
    //vector<int> str_vec1={1,3,1,2,0,5};
    vector<int> str_vec1={1,1,1,2,2,3};
    str_vec1.reserve(100);


    int k = 3;



    vector<int> rs1 = solut1->topKFrequent(str_vec1,k);
    cout<<"result"<<endl;

    solut1->myOutput_VectorBintB(rs1, 0, rs1.size()-1);




    return 0;
}


