#pragma once
#include <gtest/gtest.h>
#include "../DoublyLinkedList.hh"
#include "gtest/gtest.h"

TEST(Constructor, Array) {
    char array[14] = "Hello, World!";
    DoublyLinkedList<char> list{array, 13};

    std::cout << list << std::endl;
}

TEST(Constructor, Iterator) {
    unsigned array1[3] = {1, 2, 3};
    DoublyLinkedList<unsigned> list1{array1, 3};
    std::vector<unsigned> vec = {1, 2, 3};
    DoublyLinkedList<unsigned> list2{vec};

    ASSERT_EQ(list1.head()->value, list2.head()->value);
    ASSERT_EQ(list1.head()->next->value, list2.tail()->prev->value);
    ASSERT_EQ(list1.tail()->value, list2.tail()->value);
}
