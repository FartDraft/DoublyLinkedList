#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

TEST(Property, Constructor_Empty) {
    DoublyLinkedList<int> list;

    list.push_tail(1);
    list.push_tail(20);
    list.push_tail(300);

    std::cout << list << std::endl;
}

TEST(Property, Constructor_Array) {
    DoublyLinkedList<unsigned> list1;
    unsigned array[3] = {1, 2, 3};
    DoublyLinkedList<unsigned> list2{array, array + 3};

    list1.push_tail(1);
    list1.push_tail(2);
    list1.push_tail(3);

    ASSERT_EQ(list1, list2);
}

TEST(Property, Constructor_Iterator) {
    char array[5] = "Egor";
    DoublyLinkedList<char> list1{array, array + 4};
    std::vector<char> vec = {'E', 'g', 'o', 'r'};
    DoublyLinkedList<char> list2{vec.begin(), vec.end()};

    ASSERT_EQ(list1, list2);
}

TEST(Property, Iterator_Loop) {
    std::string s = "Hello, World!";
    DoublyLinkedList<char> list{s.begin(), s.end()};

    for (const auto& value : list) {
        std::cout << value;
    }
    std::cout << std::endl;
}

TEST(Property, Iterator_Forward) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    DoublyLinkedList<int> list{vec.begin(), vec.end()};

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        sum += *it;
    }

    ASSERT_EQ(sum, 15);
}

TEST(Property, Iterator_Reversed) {
    std::string s = "I'll be back";
    DoublyLinkedList<char> list{s.crbegin(), s.crend()};

    size_t i = 0;
    for (auto it = list.crbegin(); it != list.crend(); ++it) {
        ASSERT_EQ(*it, s[i++]);
    }
}

TEST(Method, At_Throw) {
    DoublyLinkedList<int> list;

    ASSERT_THROW(static_cast<void>(list.at(1)), std::out_of_range);
}

TEST(Method, At_NoSize) {
    unsigned array[] = {1, 2, 3};
    DoublyLinkedList<unsigned> list{array, array + 3};

    ASSERT_EQ(list.at(0)->value, 1);
    ASSERT_EQ(list.at(1)->value, 2);
    ASSERT_EQ(list.at(2)->value, 3);
}

TEST(Method, At_Size) {
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

TEST(Method, Clear_) {
    DoublyLinkedList<char> list1;
    std::string s = "clear";
    DoublyLinkedList<char> list2{s.begin(), s.end(), 4};

    list2.clear();

    ASSERT_EQ(list1, list2);
    ASSERT_EQ(list2.empty(), true);
    ASSERT_EQ(list2.length(), 0);
    ASSERT_EQ(list2.size(), 4);
}
