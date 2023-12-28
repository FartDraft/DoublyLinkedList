#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"

TEST(Constructor, Empty) {
    DoublyLinkedList<int> list;

    ASSERT_EQ(SIZE, list.size);
}

TEST(Constructor, Size) {
    DoublyLinkedList<int> list{10};

    ASSERT_EQ(10, list.size);
}

TEST(Stream, Empty) {
    DoublyLinkedList<char> list;

    std::cout << list;
}

TEST(Stream, One) {
    DoublyLinkedList<char> list;

    list.push_tail('a');
    std::cout << list;

    ASSERT_EQ(1, list.length);
    ASSERT_EQ(list.head, list.refs[0]);
    ASSERT_EQ(list.tail, list.refs[1]);
    ASSERT_EQ(list.head, list.tail);
}

TEST(Stream, Many) {
    DoublyLinkedList<char> list;

    list.push_tail('a');
    list.push_tail('b');
    list.push_tail('c');
    std::cout << list;

    ASSERT_EQ(3, list.length);
    ASSERT_EQ('a', list.head->value);
    ASSERT_EQ('b', list.head->next->value);
    ASSERT_EQ('c', list.tail->value);
    ASSERT_EQ(list.head, list.refs[0]);
    ASSERT_EQ(list.tail, list.refs[1]);
}
