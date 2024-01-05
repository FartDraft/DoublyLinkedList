#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

TEST(Constructor, Array) {
    char array[] = "Hello, World!";
    DoublyLinkedList<char> list{array};

    std::cout << list << std::endl;
}

TEST(Constructor, Iterator) {
    unsigned array[] = {1, 2, 3};
    DoublyLinkedList<unsigned> list1{array};
    std::vector<unsigned> vec = {1, 2, 3};
    DoublyLinkedList<unsigned> list2{vec};

    ASSERT_EQ(list1.head()->value, list2.head()->value);
    ASSERT_EQ(list1.head()->next->value, list2.tail()->prev->value);
    ASSERT_EQ(list1.tail()->value, list2.tail()->value);
}

TEST(Iterator, For) {
    std::string s = "Hello, World!";
    DoublyLinkedList<char> list{s};

    for (const auto& value : list) {
        std::cout << value;
    }
    std::cout << std::endl;
}

TEST(Iterator, Forward) {
    std::string s = "BGTU";
    DoublyLinkedList<char> list{s};

    for (auto&& it = list.begin(); it != list.end(); ++it) {
        *it = '!';
    }
    std::cout << list << std::endl;
}

TEST(Iterator, Reversed) {
    std::string s = "I'll be back";
    DoublyLinkedList<char> list{s};

    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
}
