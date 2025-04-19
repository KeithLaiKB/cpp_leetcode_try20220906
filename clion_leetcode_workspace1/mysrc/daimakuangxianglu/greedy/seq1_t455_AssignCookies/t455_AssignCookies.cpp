#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Assume you are an awesome parent and want to give your children some cookies.
 * But, you should give each child at most one cookie.
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with;
 * and each cookie j has a size s[j]. If s[j] >= g[i],
 * we can assign the cookie j to the child i, and the child i will be content.
 *
 * Your goal is to maximize the number of your content children
 * and output the maximum number.
 *
 *
 * Example1:
 * Input: g = [1,2,3], s = [1,1]
 * Output: 1
 * Explanation:
 *      You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
 *      And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
 *      You need to output 1.
 *
 * Example2:
 * Input: g = [1,2], s = [1,2,3]
 * Output: 2
 * Explanation:
 *      You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
 *      You have 3 cookies and their sizes are big enough to gratify all of the children,
 *      You need to output 2.
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    bool static mycomp(const int &a, const int &b){
        return a<b;
    }

    // 时间复杂度：O(log n)
    // 空间复杂度：O(1)
    int findContentChildren(vector<int>& child, vector<int>& cookie) {
        if(child.size()==0 || cookie.size()==0){
            return 0;
        }

        sort(child.begin(),child.end(),mycomp);
        sort(cookie.begin(),cookie.end(),mycomp);

        int child_idx=0;
        int rs = 0;

        //先把人喂抱, 当前人喂饱了才能看下一个人
        // 所以 人的遍历 是不能在外面这个for循环的
        // cookie 会用 外面这个循环
        for(int cookie_idx=0;cookie_idx<=cookie.size()-1;cookie_idx++){
            if(child_idx<=child.size()-1 && child[child_idx]<=cookie[cookie_idx]){
                ++rs;
                ++child_idx;
            }
        }
        return rs;
    }
};


int main() {
    cout << "result" << endl;
    Solution* solut1 = new Solution();

    vector<int> vec_int1={1,2,3};
    vector<int> vec_int2={1,1};
    //int mytarget = 5;

    int rs1 = -1;
    rs1 = solut1->findContentChildren(vec_int1,vec_int2);
    cout<<"result:"<<endl;
    cout<<rs1<<endl;
    return 0;
}


