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

TEST(Constructor, InitList) {
    DoublyLinkedList<unsigned> list1;
    DoublyLinkedList<unsigned> list2 = {1, 2, 3};

    list1.push_tail(1);
    list1.push_tail(2);
    list1.push_tail(3);

    ASSERT_EQ(list1, list2);
}

TEST(Constructor, Array) {
    double array[5] = {-0.5, 0, 0.5, 1, 1.5};
    DoublyLinkedList<double> list1{array, array + 5};
    DoublyLinkedList<double> list2 = {-0.5, 0, 0.5, 1, 1.5};

    ASSERT_EQ(list1, list2);
}

TEST(Constructor, Iterator) {
    char array[5] = "Egor";
    DoublyLinkedList<char> list1{array, array + 4};
    std::vector<char> vec = {'E', 'g', 'o', 'r'};
    DoublyLinkedList<char> list2{vec.begin(), vec.end()};

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

TEST(At, Throw) {
    DoublyLinkedList<int> list;

    ASSERT_THROW(static_cast<void>(list.at(1)), std::out_of_range);
}

TEST(At, NoSize) {
    DoublyLinkedList<unsigned> list = {1, 2, 3};

    ASSERT_EQ(list.at(0)->value, 1);
    ASSERT_EQ(list.at(1)->value, 2);
    ASSERT_EQ(list.at(2)->value, 3);
}

TEST(At, Size) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DoublyLinkedList<int> list{array, array + 10, 4};

    ASSERT_EQ(list.at(0)->value, 1);
    ASSERT_EQ(list.at(1)->value, 2);
    ASSERT_EQ(list.at(2)->value, 3);
    ASSERT_EQ(list.at(3)->value, 4);
    ASSERT_EQ(list.at(4)->value, 5);
    ASSERT_EQ(list.at(5)->value, 6);
    ASSERT_EQ(list.at(6)->value, 7);
    ASSERT_EQ(list.at(7)->value, 8);
    ASSERT_EQ(list.at(8)->value, 9);
    ASSERT_EQ(list.at(9)->value, 10);
}
