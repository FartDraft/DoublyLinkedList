#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

const unsigned SIZE = 8;

TEST(Property, Constructor_Empty) {
    DoublyLinkedList<unsigned> list(SIZE);

    list.push_tail(1);
    list.push_tail(20);
    list.push_tail(300);

    std::cout << list << std::endl;
}

TEST(Property, Constructor_InitializerList) {
    DoublyLinkedList<int> list1(SIZE, {-1, -2, -3});
    DoublyLinkedList<int> list2(SIZE);

    list2.push_tail(-1);
    list2.push_tail(-2);
    list2.push_tail(-3);

    ASSERT_EQ(list1.head()->value, list2.head()->value);
    ASSERT_EQ(list1.head()->next->value, list2.head()->next->value);
    ASSERT_EQ(list1.tail()->value, list2.tail()->value);
}

TEST(Property, Constructor_Array) {
    double array[3] = {0.1, 0.2, 0.3};
    DoublyLinkedList<double> list1(SIZE, array, array + 3);
    DoublyLinkedList<double> list2(SIZE, {0.1, 0.2, 0.3});

    ASSERT_EQ(list1, list2);
}

TEST(Property, Constructor_Iterator) {
    std::string s1 = "Author: Egor Afanasin";
    DoublyLinkedList<char> list1(SIZE, s1.begin(), s1.end());
    char s2[22] = "Author: Egor Afanasin";
    DoublyLinkedList<char> list2(SIZE, s2, s2 + 21);

    ASSERT_EQ(list1, list2);
}

TEST(Property, Iterator_Loop) {
    std::string s = "Hello, World!";
    DoublyLinkedList<char> list(SIZE, s.begin(), s.end());

    for (const auto& value : list) {
        std::cout << value;
    }
    std::cout << std::endl;
}

TEST(Property, Iterator_Forward) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    DoublyLinkedList<int> list(SIZE, vec.begin(), vec.end());

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        sum += *it;
    }

    ASSERT_EQ(sum, 15);
}

TEST(Property, Iterator_Reversed) {
    std::string s = "I'll be back";
    DoublyLinkedList<char> list(SIZE, s.crbegin(), s.crend());

    size_t i = 0;
    for (auto it = list.crbegin(); it != list.crend(); ++it) {
        ASSERT_EQ(*it, s[i++]);
    }
}

TEST(Property, Assignment_Vector) {
    DoublyLinkedList<int> list1(SIZE, {-10, -9, -8, -7, -6, -5});
    DoublyLinkedList<int> list2(SIZE, {-1, 0, -1});

    list1 = list2;

    ASSERT_EQ(list1, list2);
}

TEST(Property, Assignment_InitializerList) {
    DoublyLinkedList<int> list1(SIZE, {-10, -9, -8, -7, -6, -5});
    DoublyLinkedList<int> list2(SIZE, {-1, 0, -1});

    list1 = {-1, 0, -1};

    ASSERT_EQ(list1, list2);
}

TEST(Method, Clear_) {
    DoublyLinkedList<int> list1(SIZE, {1, 2, 3});
    DoublyLinkedList<int> list2(SIZE);

    list1.clear();

    ASSERT_EQ(list2.empty(), true);
    ASSERT_EQ(list2.length(), 0);
    ASSERT_EQ(list2.size(), SIZE);
    ASSERT_EQ(list1, list2);
}

TEST(Method, At_Throw) {
    DoublyLinkedList<int> list(SIZE);

    ASSERT_THROW(static_cast<void>(list.at(1)), std::out_of_range);
}

TEST(Method, At_NoSize) {
    DoublyLinkedList<unsigned> list(SIZE, {1, 2, 3});

    ASSERT_EQ(list.at(0)->value, 1);
    ASSERT_EQ(list.at(1)->value, 2);
    ASSERT_EQ(list.at(2)->value, 3);
}

TEST(Method, At_Size) {
    DoublyLinkedList<int> list(3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

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
