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

                char c_tmp2=t.at(i);
                if(unorder_map_s.find(c_tmp2) != unorder_map_s.end()){
                    unorder_map_s[c_tmp2]= unorder_map_s[c_tmp2] - 1;
                }
                else{
                    unorder_map_s[c_tmp2]=-1;
                }
            }

            bool findNoZero= false;     //发现存在!=0
            /*
            for(unordered_map<char,int>::iterator it=unorder_map_s.begin();it!=unorder_map_s.end();it++){
                cout<<it->first<<it->second<<endl;
                if(it->second!=0){
                    findNoZero = true;
                }
            }*/

            for(pair<int,int> kv:unorder_map_s){
                cout<<kv.first<<kv.second<<endl;
                if(kv.second!=0){
                    findNoZero = true;
                }
            }

            if(findNoZero==false){
                rs = true;
            }
            else if(findNoZero==true){
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


