#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <climits>
#include <unordered_set>

#include <algorithm>

using namespace std;

/**
 *
 * You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
 * All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
 * For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 * You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.
 *
 * Example1:
 * Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
 * Output: ["JFK","MUC","LHR","SFO","SJC"]
 *
 * Example2:
 * tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 * Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
 * Explanation:
 * Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.
 *
 *
 *
 * 从题目来说 每个机票只能用一次,
 * 也就是说 从某个点 到 某个点的线 是受到限制的
 *
 * 也就是说这题关注的是线  而不是点
 * 而used数组关注的是点
 * 既然 我们 关注的是线
 * 我们的 逻辑树就是对 当前这个 起始地departure
 *      对他的那个 终点站 destination map 的每一站 进行尝试搜索和回溯
 *
 */
class Solution {
public:
    Solution(){

    }
    ~Solution(){

    }

    template<typename T>
    void myOutput_VectorBVectorBintBB(vector<vector<T>>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            for(int j=0;j<=nums[i].size()-1;j++){

                cout<<nums[i][j]<<"\t";
                if(j==nums[i].size()-1){
                    cout<<endl;
                }

            }
        }
    }

    template<typename T>
    void myOutput_VectorBtB(vector<T>& nums, int st_indx, int ed_indx){
        for(int i=st_indx;i<=ed_indx;i++){
            cout<<nums[i]<<"\t";
            if(i==ed_indx){
                cout<<endl;
            }
        }
    }



    /**
     * 所有机票都要用一次
     * 注意以下 map本身是有序的 因为他本身是红黑树弄得
     * @param tickets
     * @return
     *
     *
     *
     *
     */
     //
     // 给进来的
     // {"JFK":
     //         {"SFO":1},
     //         {"ATL":1}
     // ,"SFO":
     //         {"ATL":1}
     // ,"ATL":
     //         {"JFK":1},
     //         {"SFO":1}
     // }
     //
     // 我们会发现 这里不会 使用 tickets 也就是我们常说的candidate数组
     // 而是使用弄好的一个map 来弄
    int backtracking(int tickets_num, string now_depart, unordered_map<string, map<string, int>>& flight_routes, vector<string>& rs){
        //limit
        // 有多少个地点, 也只能去多少个地点, 不可以重复去
        // 机票数就是 线 数, 机场数量就是 点数
        // 点 数 = 线数 +1
        if(rs.size()==tickets_num+1){
            //找到了
            return 1;
        }

        int found_top1route=0;

        // 不能把map这样提取出来, 因为你提取出来以后 你修改map 不会影响到 flight_routes[now_depart]
        // 因为这个map只是一个副本
        // map<string,int> routes= flight_routes[now_depart];   //错误示范, 不用引用(&) 里面是无法修改值的
        map<string,int> &routes= flight_routes[now_depart];
        // for(pair<string,int> route: routes){                 //错误示范, 不用引用(&) 里面是无法修改值的
        for(pair<const string,int> &route: routes){
            //这条路线 用过了 剩余使用次数== 0
            if(route.second==0){
                continue;
            }

            rs.push_back(route.first);
            route.second=0;

            found_top1route=backtracking(tickets_num,route.first,flight_routes,rs);
            // 找到的话 直接结束 不用看后面了, 因为map本身就是带好排序的
            // 找到的第一条就是最优路线
            if(found_top1route==1){
                return 1;
            }

            //pop
            rs.pop_back();
            route.second=1;

        }


        return 0;
    }


    //时间复杂度: O(n * n!)
    //  对于n张机票的问题，例如第一次 我可以用n张机票,所以有n种可能性
    //                  第二次 我可以用n-1张机票,所以有n-1种可能性
    //                  第三次 我可以用n-2张机票,所以有n-2种可能性
    //  以此类推复杂度有O(n!)
    //
    //  在每次递归调用中，我们需要遍历出发机场那个map的可能的目的地（最坏情况下为O(n)）
    //  每次添加到结果向量的操作复杂度为O(1)，但如果考虑字符串复制的开销，则为O(字符串长度)
    //综合来看，时间复杂度为O(n * n!)，其中：
    //
    //空间复杂度: O(n)
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        vector<string> rs1={};
        unordered_map<string, map<string,int>> flight_routes;

        for(int i=0;i<=tickets.size()-1;i++){
            string dept_tmp=tickets[i][0];
            string dest_tmp=tickets[i][1];

            //因为每条线的机票只能为1张
            flight_routes[dept_tmp][dest_tmp]=1;
        }

        string now_depart = "JFK";
        rs1.push_back(now_depart);
        backtracking(tickets.size(),now_depart,flight_routes,rs1);


        return rs1;
    }
};


int main() {

    Solution* solut1 = new Solution();

    //vector<int>* p_intvec = new vector<int>({-1,0,3,5,9,12});
    vector<int> intvec1 ={1,1,2};
    vector<vector<string>> vec_vec_str1 = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    //int mytarget = 8;

//    int indx_rs1 = -1;
//
//    int k = 3;
//    int n =7;
    //string str1 ="101023";
    vector<string> rs1 = solut1->findItinerary(vec_vec_str1);
    cout<<"result:"<<endl;

    solut1->myOutput_VectorBtB(rs1,0,rs1.size()-1);
    return 0;
}


