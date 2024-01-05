#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

TEST(Constructor, Empty) {
    DoublyLinkedList<int> list;

    list.push_tail(1);
    list.push_tail(20);
    list.push_tail(300);

    std::cout << list << std::endl;
}

TEST(Constructor, FromArray) {
    unsigned array[3] = {1, 2, 3};
    DoublyLinkedList list1{array, array + 3};
    DoublyLinkedList<unsigned> list2;

    list2.push_tail(1);
    list2.push_tail(2);
    list2.push_tail(3);

    ASSERT_EQ(list1, list2);
}

TEST(Constructor, Iterator) {
    unsigned array[3] = {1, 2, 3};
    DoublyLinkedList list1{array, array + 3};
    std::vector<unsigned> vec = {1, 2, 3};
    DoublyLinkedList<unsigned> list2{vec.begin(), vec.end()};

    ASSERT_EQ(list1, list2);
}

TEST(Iterator, Loop) {
    std::string s = "Hello, World!";
    DoublyLinkedList<char> list{s.begin(), s.end()};

    for (const auto& value : list) {
        std::cout << value;
    }
    std::cout << std::endl;
}

TEST(Iterator, Forward) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    DoublyLinkedList<int> list{vec.begin(), vec.end()};

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        sum += *it;
    }

    ASSERT_EQ(sum, 15);
}

TEST(Iterator, Reversed) {
    std::string s = "I'll be back";
    DoublyLinkedList<char> list{s.crbegin(), s.crend()};

    size_t i = 0;
    for (auto it = list.crbegin(); it != list.crend(); ++it) {
        ASSERT_EQ(*it, s[i++]);
    }
}
