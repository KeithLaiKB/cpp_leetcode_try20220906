#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;



template <typename T>
void printType(T t) {
    std::cout << "Generic Type: " << t << std::endl;
}

// 针对int类型的特化
template <>
void printType<int>(int t) {
    std::cout << "Int Type: " << t << std::endl;
}


/**
 * 从main里你就能看到了 我们上方 只有int这个类型专门特化过,
 * 所以使用printType 方法 并且 输入为 int 时
 *      他会 走这条 printType<int>(int t)
 * 然而 10.5 并不是 int类型, 而且 10.5 为 double 他并没有被特化
 *      所以他会 走这条 void printType(T t)
 * @return
 */
int main() {
    printType(10);        // 输出: Int Type: 10
    printType(10.5);      // 输出: Generic Type: 10.5
    return 0;
}