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

TEST(Constructor, Assert) { ASSERT_DEATH(DoublyLinkedList<int> list{0}, "size > 0"); }

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
    DoublyLinkedList<char> list{2};

    list.push_tail('a');
    list.push_tail('b');
    list.push_tail('c');
    list.push_tail('d');
    std::cout << list;

    ASSERT_EQ(list.length(), 4);
    ASSERT_EQ(list.head()->value, 'a');
    ASSERT_EQ(list.head()->next->value, 'b');
    ASSERT_EQ(list.tail()->prev->value, 'c');
    ASSERT_EQ(list.tail()->value, 'd');
}
