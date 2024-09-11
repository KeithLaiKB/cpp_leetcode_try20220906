#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;


template <typename T1 = double, typename T2 = string>         //指的是默认是T1是int类型 T2是string 类型
class MyShape {
private:
    T1 permiter;     //周长
    T2 color;
    double area;    //面积
public:
    //构造函数 第一种写法, 这种貌似效率更高?
    //MyShape(T1 v1, T2 v2, double v3) : permiter(v1), color(v2), area(v3){
    // cout<<"constructor finished"<<endl;
    // }

    //构造函数 第二种写法
    MyShape(T1 permiter, T2 color, double area){
        this->permiter=permiter;
        this->color = color;
        this->area= area;
        cout<<"constructor finished"<<endl;
    }

    T1 getPermiter() {
        return permiter;
    }

    T1 getColor() {
        return color;
    }

    T1 getArea() {
        return area;
    }
};

int main() {
    MyShape<double,string> shape1(123.67,"green",35);   // 使用double
    MyShape<int,string> shape2(123,"black",35);         // 使用int
    MyShape<> shape3(123,"black",35);                   // 使用默认的int类型 和 string 类型
    MyShape<float, string> shape4(123.67,"black",35);      // 使用float

    std::cout << shape1.getPermiter() << std::endl;    // 输出: 123.67
    std::cout << "Type of a: " << typeid(shape1.getPermiter()).name() << std::endl;

    std::cout << shape2.getPermiter() << std::endl; // 输出: 123
    std::cout << "Type of a: " << typeid(shape2.getPermiter()).name() << std::endl;

    std::cout << shape4.getPermiter() << std::endl; // 输出: 123.67
    std::cout << "Type of a: " << typeid(shape4.getPermiter()).name() << std::endl;
    return 0;
}