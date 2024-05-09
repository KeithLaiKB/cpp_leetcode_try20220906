#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given two integer arrays nums1 and nums2, return an array of their intersection.
 * Each element in the result must be unique and you may return the result in any order.
 *
 * Example1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 *
 * Example2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * Explanation: [4,9] is also accepted.
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    void myOutput_VectorBstringB(vector<string>& vec, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<vec[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }

    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    // head = [1,2,3,4,5], n = 2
    //
    //
    // 并集(不是并集), 先用建立 一个vector 带频率的, 当然也可以直接 26个数组 当作 hashtable
    //      然后先把第一个塞进去, 后面的跟他 做 类似并集(不是并集)
    //          我们可以做一个最小值, 因为已经塞了第一个进去了
    //              如果第二个 没有相同的元素 是0, 那么结果也是0, 意味着没有相同的元素
    //          如果第一个元素 有2个, 第二个元素有1个, 那么最小值也是1个， 符合我们的预期
    //              例如 cookie, coke  这两个当中 o 在hashtable中 的次数应该是min(2,1)=1
    vector<string> commonChars(vector<string>& words) {
        int arr_alpb_min[26]={0};
        int arr_alpb_tmp[26] = {0};
        int aplb_len = sizeof(arr_alpb_min)/sizeof(arr_alpb_min[0]);
        char ch_tmp= NULL;
        string str_tmp;

        vector<string> result_vec;

        //先把第一个先丢进去
        for(int i=0;i<=words[0].size()-1;i++){
            ch_tmp = words[0][i];
            ++arr_alpb_min[ch_tmp-'a'];
        }

        //

        for(int i=1;i<=words.size()-1;i++){
            str_tmp=words[i];
            memset(arr_alpb_tmp,0,26*sizeof(int));

            for(int j=0;j<=str_tmp.size()-1;j++){
                ch_tmp = str_tmp[j];
                ++arr_alpb_tmp[ch_tmp-'a'];
            }

            //做min
            for(int k=0;k<=aplb_len-1;k++) {
                arr_alpb_min[k] = min(arr_alpb_min[k], arr_alpb_tmp[k]);
            }
        }


        for(int i=0;i<=aplb_len-1;i++){
            if(arr_alpb_min[i]!=0){
                for(int j=0;j<=arr_alpb_min[i]-1;j++){
                    result_vec.push_back(string(1,'a'+i));
                }
            }
        }
        return result_vec;
    }

};

/**
 * feature:
 * 1. 每个字符串的每个字符 出现的频率
 * 2.1 只返回 所有字符串都能 共同出现的字符
 * 2.2 并且 返回的是vector 里面的 字符 不包含次数, 次数依赖于 这个字符重复出现在这个vector当中, 要多次打印
 *
 * 思路(原来是想着追加的, 因为第一条想出来以后发现这是思路):
 * 1. 那么可以根据返回的vector中 每个字符出现的次数 来output
 * 2. 想出现交集-> 想做一个类似并集的东西, 但是 并集是不包含 重复的元素的
 *      而我们这里是要包括重复元素的
 *
 * 追加:
 * 1. 因为, 出现的 类似并集的东西(不是并集) 并且返回是一个vector 这个是不包含 频率的
 *          所以 根据 之前的feature 我做一个 类似并集的东西(不是并集)的 hashtable (a-z, 并且包含次数)
 *              到时候吧 这个hashtable filter一下 过度给 返回的vector就可以了
 *
 *
 * */
int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<string> strvec1 = {"bella","label","roller"};

    vector<string> rs_strvec1=solut1->commonChars(strvec1);


    cout<<"result"<<endl;
    solut1->myOutput_VectorBstringB(rs_strvec1,0,rs_strvec1.size()-1);





    return 0;
}


