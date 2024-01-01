#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

TEST(Constructor, Empty) {
    DoublyLinkedList<int> list;

    ASSERT_EQ(list.size(), SIZE);
}

TEST(Constructor, Size) {
    DoublyLinkedList<int> list{10};

    ASSERT_EQ(list.size(), 10);
}

TEST(Stream, Empty) {
    DoublyLinkedList<char> list;

    std::cout << list;
}

TEST(Stream, One) {
    DoublyLinkedList<char> list;

    list.push_tail('a');
    std::cout << list;

    ASSERT_EQ(list.length(), 1);
    ASSERT_EQ(list.head(), list.tail());
}

TEST(Stream, Many) {
    DoublyLinkedList<char> list;

    list.push_tail('a');
    list.push_tail('b');
    list.push_tail('c');
    std::cout << list;

    ASSERT_EQ(list.length(), 3);
    ASSERT_EQ(list.head()->value, 'a');
    ASSERT_EQ(list.head()->next->value, 'b');
    ASSERT_EQ(list.tail()->value, 'c');
}
