#include <iostream>
#include <memory>
#include "../lib/unrolled_list.cpp"
#include "../lib/unrolled_list.h"

class SomeObj2 {
    public:
        static inline int CopiesCount = 0;
        static inline int DestructorCalled = 0;
    
        SomeObj2() = default;
    
        SomeObj2(SomeObj2&&) {}
    
        SomeObj2(const SomeObj2&) {
            ++CopiesCount;
            if (CopiesCount == 20) {
                CopiesCount = 0;
                throw std::runtime_error("");
            }
        }
    
        ~SomeObj2() {
            ++DestructorCalled;
        }
    };

int main(int argc, char** argv) {
    /* unrolled_list<SomeObj2, 5> unrolled{SomeObj2{} ,SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{},SomeObj2{}, SomeObj2{}};
    for (int i = 0; i < 10; ++i) {
        unrolled.pop_front();
        std::cout << unrolled.size() << std::endl;
    } */
    /* unrolled_list<int, 5> unrolled = unrolled_list<int, 5>();
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) unrolled.push_back(i);
        else unrolled.push_front(i);
    }

    unrolled.erase(unrolled.cbegin());
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() += 10);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() += 200);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() += 1);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin());
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() += 1);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin());
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() += 2);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin() -=500);
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    unrolled.erase(unrolled.cbegin());
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl; */

    unrolled_list<int, 5> unrolled = unrolled_list<int, 5>();
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) unrolled.push_back(i);
        else unrolled.push_front(i);
    }
    for (auto& i : unrolled) {std::cout << i << " ";}std::cout << std::endl;
    

    std::cout << *(unrolled.cbegin().get_pointer() += 100) << '\n';
    //std::allocator_traits<std::allocator<int>>::rebind_traits<>
    
    return 0;
}