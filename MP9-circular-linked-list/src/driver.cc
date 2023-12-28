#include <iostream>

#include "circular-linked-list.hpp"


int main() {
    CircularLinkedList<int> list1;
    list1.InsertInOrder(3);
    list1.InsertInOrder(-111);
    list1.InsertInOrder(-1111);
    // Test 3: Copy assignment operator in Order::kASC
    CircularLinkedList<int> list3;
    list3.InsertInOrder(-5);
    list3.InsertInOrder(-1);
    std::cout << "List3 (Original): ";
    std::cout << list3 << std::endl;
    std::cout << "List1 (Original): ";
    std::cout << list1 << std::endl;

    list3 = list1;
    std::cout << "List1 (Original): ";
    std::cout << list1 << std::endl;
    std::cout << "List3 (Assigned): ";
    std::cout << list3 << std::endl;

    // CircularLinkedList<int> test;
    // test.Reverse();
    // const int kTest1 = 1;
    // const int kTest2 = 2;
    // const int kTest3 = 3;
    // const int kTest4 = 4;
    // const int kTest5 = 5;
    // test.InsertInOrder(kTest1);
    // test.InsertInOrder(kTest2);
    // test.InsertInOrder(kTest3);
    // test.InsertInOrder(kTest4);
    // test.InsertInOrder(kTest5);
    // CircularLinkedList<int> cl;
    // std::cout << cl << std::endl;
    // cl.InsertInOrder(kTest3);
    // test = cl;
    // std::cout << test << "TEST" << std::endl;
}
