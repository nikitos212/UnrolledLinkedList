#include <cstddef>
#include <iostream>
#include <memory>
#include "../lib/unrolled_list.cpp"
#include "../lib/unrolled_list.h"

int main(int argc, char** argv) {
    unrolled_list<int, 5, std::allocator<int>> list1(std::allocator<int>{});
    unrolled_list<int, 5, std::allocator<int>> list2(std::allocator<int>{});
    size_t count = 0;
    for (int i = 0; i < 1000; ++i) {
        list1.push_back(i);
        list2.push_back(i);
    }

    for (int i = 0; i < 500; ++i) {
        if (i % 2 == 0) {
            list1.pop_back();
            list2.pop_back();
        } else {
            list1.pop_front();
            list2.pop_front();
        }
    }

    /* for (int i = 0; i < 500; ++i) {
        list1.pop_back();
        list2.pop_back();
    } */

    if (list1 == list2) { std::cout << "true\n";}
    std::cout << list1.front() << " " << list1.back();
    
    return 0;
}
