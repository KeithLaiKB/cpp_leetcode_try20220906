#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// int* &ptr        , int newSize               : 什么都能搞 就是比较危险罢了
// int* ptr         , int newSize               : 只 改写 输入源参数的值,     不改变 输入源 的地址
// const int* ptr   , int size                  : 只 读取 输入源参数,        不改变 输入源 的值和地址

// const vector<optional<int>> &arr;            ; const 代表不能修改arr, 但是传递参数进来的时候 是引用 而不是拷贝

//×××××××××××××××××××××××××× 探查参数: int* ptr, int newSize ××××××××××××××××××××××××××××××××××××××××××
// 这样int* ptr 只是能够改内容,
// 但他改成新的地址, 对于main中是没用的
//
// 总结:
// 这种做法 非常适合 那种只 改写 输入源参数的值, 不改变输入源的地址


// 探查一: function内改地址是否会影响main里
// 发现 不会
//      你在这个函数里想要设置成 0 0 0 0 0
//      可是main 函数 after resize 里的输出 并不是 函数里所设置的样子
void resizeArray_wrong_p1(int* ptr, int newSize) {
    //delete[] ptr;  // 删除本地副本指向的内存
    ptr = new int[newSize];  // 为新的大小分配内存，但只在本地指针中生效
    for (int i = 0; i < newSize; ++i) {
        ptr[i] = 0;
    }

    std::cout << "inside the function(after change): ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}

// 探查二: function内改内容 是否成功
// 可以
void resizeArray_wrong_p1_upd_content(int* ptr, int newSize) {
    //delete[] ptr;  // 删除本地副本指向的内存

    //只修改内容
    for (int i = 0; i < newSize; ++i) {
        ptr[i] = 0;
    }

    std::cout << "inside the function(after change): ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}


//×××××××××××××××××××××××××× 探查参数: int* &ptr, int newSize ××××××××××××××××××××××××××××××××××××××××××
// 这样啥都能改, 只是说你乱搞, 有可能会出问题而已
void resizeArray(int* &ptr, int newSize) {
    //delete[] ptr;  // 删除原来的内存
    ptr = new int[newSize];  // 分配新的内存
    for (int i = 0; i < newSize; ++i) {
        ptr[i] = i + 1;  // 初始化新数组
    }
}


//×××××××××××××××××××××××××× 探查参数: const int* ptr, int size ××××××××××××××××××××××××××××××××××××××××××


// 在函数里 他虽然能把ptr的指向改成新的地址, 对于main中是没用的
// 只能 读取 ptr指向的地址的这个数组内容
//
// 总结:
// 这种做法 非常适合 那种只读取 输入源参数, 不改变输入源的值和地址

// 探查一: function内改地址是否会影响main里
// 发现 不会
//
// 你在最终输出会发现
//      你在这个函数里想要设置成 0 0 0 0 0
//      可是main 函数 after resize 里的输出 并不是 函数里所设置的样子
void resizeArray_wrong_cont1_new(const int* ptr, int newSize) {

    // *(ptr+0)=1000; 我本来想改变 a[0]的内容 你会发现这个该内容是不行的 因为他是readonly

    //于是我探查 重新分配内容
    ptr = new int[newSize];  // 分配新的内存

/*    int ptr2[] = {1,2,3,4};
    ptr = ptr2;*/

    std::cout << "inside the function(after change): ";
    for (int i = 0; i < newSize; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;


}
// 探查二: function内改内容 是否成功
// 发现只能读取数组内容，也不能修改
/*void resizeArray_wrong_cont1_upd_content(const int* ptr, int newSize) {
    ptr[1] = 10000;     // ide这里直接表明给你 readonly;
    for (int i = 0; i < newSize; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}*/


int main() {
/*    int* array = new int[3];
    array[0] = 1; array[1] = 2; array[2] = 3;*/

    int array[]={1,2,3};
    int *arrayP = array;
    int len = sizeof(array)/sizeof(array[0]);



    std::cout << "Before resizing: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    int newsize=5;

    //resizeArray_wrong_p1(arrayP, newsize);    // 虽然调用了 resizeArray，但原指针 array 并未改变
    resizeArray_wrong_p1_upd_content(arrayP, len);    // 虽然调用了 resizeArray，但原指针 array 并未改变

    //resizeArray(arrayP, newsize);

    //resizeArray_wrong_cont1_new(arrayP,newsize); // 虽然调用了 resizeArray，但原指针 array 并未改变
    //resizeArray_wrong_cont1_upd_content(arrayP,newsize);


    // 如果你用了 resizeArray_wrong 或者是 resizeArray_wrong_cont1_new, 这里 array 仍然指向原来的地址，已被 delete[]
    // 虽然你发现还是有输出(如果main中 是用int* array = new int[3];),
    //      但只是说暂时系统原因 没打算把它抛掉而已, 以后资源紧张就会抛掉了
    // 如果main中 是用 int array[]={1,2,3};
    //      答案就很明显告诉你是有问题的了
    std::cout << "After resizing: ";
    for (int i = 0; i < newsize; ++i) {
        std::cout << arrayP[i] << " ";
    }
    std::cout << std::endl;

    delete[] arrayP; // 释放原始指针所指向的内存（已经被释放）
    return 0;
}


