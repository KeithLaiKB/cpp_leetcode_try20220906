#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include <cstring>  // 确保包含了 <cstring> 头文件, 这个提供了memset
using namespace std;

/**
 *
 * Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
 * Each letter in magazine can only be used once in ransomNote.

 * Example1:
 * Input: ransomNote = "a", magazine = "b"
 * Output: false

 *
 * Example2:
 * Input: ransomNote = "aa", magazine = "ab"
 * Output: false
 *
 * Example3:
 * Input: ransomNote = "aa", magazine = "aab"
 * Output: true
 *
 */
class Solution {
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

    // 时间复杂度：O(n^2)
    // 空间复杂度：O(n^2)
    bool canConstruct(string ransomNote, string magazine) {


        int arr1[122-65]={0};
        int len = sizeof (arr1)/sizeof (arr1[0]);
        int rs_bool=-1;

        for(int i=0; i<=ransomNote.size()-1; i++){
            char  ch_tmp= ransomNote[i];
            ++arr1[ch_tmp-'A'];
        }

        for(int i=0; i<=magazine.size()-1; i++){
            char  ch_tmp= magazine[i];
            --arr1[ch_tmp-'A'];
        }

        int loop_tmp=0;
        for(; loop_tmp<=len-1;loop_tmp++){
            if(arr1[loop_tmp]>0){
                rs_bool=0;
                break;
            }
        }
        if( loop_tmp==len && rs_bool ==-1){
            return true;
        }
        else{
            return false;
        }

    }


};

/**
 * feature:
 *
 *
 * 思路():
 *
 *
 *
 * */
int main() {
    Solution* solut1 = new Solution();

    string target = "aa";
    string inventory = "ab";

    int rs_int=solut1->canConstruct(target,inventory);

    cout<<"result"<<endl;
    cout<<rs_int<<endl;





    return 0;
}


