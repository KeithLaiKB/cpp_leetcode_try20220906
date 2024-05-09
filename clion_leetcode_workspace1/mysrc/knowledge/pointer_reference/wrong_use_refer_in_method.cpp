#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// 这样int* ptr 只是能够改内容, 他改成新的地址, 对于main中是没用的
void resizeArray_wrong_p(int* ptr, int newSize) {
    //delete[] ptr;  // 删除本地副本指向的内存
    ptr = new int[newSize];  // 为新的大小分配内存，但只在本地指针中生效
    for (int i = 0; i < newSize; ++i) {
        ptr[i] = i + 1;
    }
}

// 这样啥都能改, 只是说你乱搞, 有可能会出问题而已
void resizeArray(int* &ptr, int newSize) {
    //delete[] ptr;  // 删除原来的内存
    ptr = new int[newSize];  // 分配新的内存
    for (int i = 0; i < newSize; ++i) {
        ptr[i] = i + 1;  // 初始化新数组
    }
}

// 只能读取数组内容，不能重新分配, 他改成新的地址, 对于main中是没用的
void resizeArray_wrong_cont1_new(const int* ptr, int size) {
    ptr = new int[size];  // 分配新的内存

/*    int ptr2[] = {1,2,3,4};
    ptr = ptr2;*/

    for (int i = 0; i < size; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}

// 只能读取数组内容，也不能修改
/*void resizeArray_wrong_cont1_upd_content(const int* ptr, int size) {
    ptr[1] = 10000;     // ide这里直接表明给你 readonly;
    for (int i = 0; i < size; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
}*/


int main() {
/*    int* array = new int[3];
    array[0] = 1; array[1] = 2; array[2] = 3;*/

    int array[]={1,2,3};
    int *arrayP = array;



    std::cout << "Before resizing: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    int newsize=5;

    //resizeArray_wrong_p(arrayP, newsize);    // 虽然调用了 resizeArray，但原指针 array 并未改变
    resizeArray(arrayP, newsize);

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


