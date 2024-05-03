#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

/**
 *
 * Given two strings s and t, return true if t is an anagram of s, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * Example1:
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 *
 * Example2:
 * Input: s = "rat", t = "car"
 * Output: false
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }


    // 时间复杂度：O(n)
    // 空间复杂度：O(1)   我在sortedSquares中创建了一个数组来做result
    // head = [1,2,3,4,5], n = 2
    //
    // 长度,
    bool isAnagram(string og, string target) {
        int rs_int = -1;

        int myhshtbl[26]={0};
        char tmp =NULL;

        for(int i=0;i<=og.size()-1;i++){
            tmp = og[i];
            myhshtbl[tmp-'a']++;
        }

        for(int i=0;i<=target.size()-1;i++){
            tmp = target[i];
            myhshtbl[tmp-'a']--;
        }

        int checki=0;
        for(checki=0;checki<=26-1;checki++){
            if(myhshtbl[checki]!=0){
                rs_int = 0;
                break;
            }
        }


        if(checki==26 && rs_int==-1){
            return true;
        }
        else{
            return false;
        }


    }

};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    string str1 = "anagram";
    string str2 = "nagaram";
    bool result=solut1->isAnagram(str1,str2);


    cout<<"result"<<endl;
    cout<<result<<endl;





    return 0;
}


