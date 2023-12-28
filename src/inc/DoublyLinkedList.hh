#pragma once

#include <cstdint>
#include <vector>

#define SIZE 64

template <typename T, typename S = unsigned>
class DoublyLinkedList {
  public:
    struct node {
        node* prev;
        T value;
        node* next;
    };

    uint64_t length = 0;
    S size = SIZE;
    node *head{}, *tail{};
    std::vector<node*> refs = {head, tail}; // {head, SIZE, 2*SIZE, ..., n*SIZE, head}

    DoublyLinkedList(S size = SIZE) : size{size} {}
};
