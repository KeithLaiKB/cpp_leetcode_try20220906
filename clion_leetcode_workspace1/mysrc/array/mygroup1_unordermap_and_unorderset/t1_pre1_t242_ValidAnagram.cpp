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
    bool isAnagram(string s, string t) {
        unordered_map<char,int> unorder_map_s;
        unordered_map<char,int> unorder_map_t;
        int i=-1;

        bool rs = false;
        if(s.size()!=t.size()){
            rs = false;
        }
        else if(s.size()==t.size()){
            for(i=0;i<=s.size()-1;i++){
                char c_tmp1=s.at(i);
                if(unorder_map_s.find(c_tmp1) != unorder_map_s.end()){
                    unorder_map_s[c_tmp1]= unorder_map_s[c_tmp1] + 1;
                }
                else{
                    unorder_map_s[c_tmp1]=1;
                }
            }
            for(i=0;i<=t.size()-1;i++){
                char c_tmp2=t.at(i);
                if(unorder_map_t.find(c_tmp2) != unorder_map_t.end()){
                    unorder_map_t[c_tmp2]= unorder_map_t[c_tmp2] + 1;
                }
                else{
                    unorder_map_t[c_tmp2]=1;
                }
            }
            if(unorder_map_s==unorder_map_t){
                rs = true;
            }
            else{
                rs = false;
            }
        }
        return rs;
    }
};


int main() {

    Solution* solut1 = new Solution();

    string str1("abc");
    string str2("abc");

    string* s1P= new string();
    cin >> *s1P;

    string* s2P= new string();
    cin >> *s2P;

    cout<<"s1:"<< *s1P <<endl;
    cout<<"s2:"<< *s2P <<endl;

    bool rs1 = solut1->isAnagram(*s1P,*s2P);
    cout << "result:" << boolalpha << rs1 << endl;      //boolalpha 是为了把bool的值的0和1 转换成true和false
    return 0;
}


