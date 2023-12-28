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
