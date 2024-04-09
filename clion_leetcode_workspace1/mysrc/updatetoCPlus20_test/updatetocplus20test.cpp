//
// Created by kt on 09/04/24.
//

#include "updatetocplus20test.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

// 定义一个概念，要求类型T支持<运算符
template<typename T>
concept LessThanComparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// 使用概念约束的函数模板，找到并返回容器中的最小元素
template<LessThanComparable T>
T findMin(const std::vector<T>& values) {
    T min = values[0];
    for (const auto& value : values) {
        if (value < min) {
            min = value;
        }
    }
    return min;
}

int main() {
    std::vector<int> intValues = {5, 3, 8, 1, 4};
    std::cout << "The minimum int value is: " << findMin(intValues) << std::endl;

    std::vector<std::string> stringValues = {"Zebra", "Apple", "Mango", "Cherry", "Banana"};
    std::cout << "The minimum string value is: " << findMin(stringValues) << std::endl;

    // 下面的代码将在编译时失败，因为std::list不支持下标访问
    // std::list<int> listValues = {5, 3, 8, 1, 4};
    // std::cout << "The minimum in list is: " << findMin(listValues) << std::endl;

    return 0;
}