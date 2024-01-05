#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"
#include "gtest/gtest.h"

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
