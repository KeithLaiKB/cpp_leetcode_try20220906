#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }
    int countSubstrings(string s) {
        int result = -1;

        return result;
    }
};

/**
 * Example 1:
 * Input: s = "abc"
 * Output: 3
 * Explanation: Three palindromic strings: "a", "b", "c".
 *
 *
 * Example 2:
 * Input: s = "aaa"
 * Output: 6
 * Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 *
 *
 *      a       b       a       b       a       a       c
 * a    1^      0       1       0       1^      1       0
 * b    *       1^*     0       1^*     0       0       0
 * a    *       *       1^*$%   0       1%      1       0
 * b    *       *       *       1%@     0       0       0
 * a    *       *       *       *       1       1       0
 * a    *       *       *       *       *       1       0
 * c    *       *       *       *       *       *       1
 *
 *
 * 从上面看出 a b a b a
 *          a * * * a   他们相同    并且index只差>1 所以需要看 里面的字串是否也是相同
 *            b * b     他们也相同  并且index只差>1 所以需要看 里面的字串是否也是相同
 *              a       他们相同    然后往上面return
 *
 * @return
 */
int main() {

    Solution* solut1 = new Solution();

    string str1("abc");
    string str2("aaa");

    string* s1P= new string();
    cin >> *s1P;

    string* s2P= new string();
    cin >> *s2P;

    cout<<"s1:"<< *s1P <<endl;
    cout<<"s2:"<< *s2P <<endl;

    int rs1 = solut1->countSubstrings(*s1P);
    cout << "result:" << boolalpha << rs1 << endl;      //boolalpha 是为了把bool的值的0和1 转换成true和false
    return 0;
}


