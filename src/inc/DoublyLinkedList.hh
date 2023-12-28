#pragma once

#include <cstdint>
#include <iostream>
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
    std::vector<node*> refs = {head, tail};

    explicit constexpr DoublyLinkedList(S size = SIZE) : size{size} {}

    constexpr node*
    push_tail(const T& value) {
        ++length;
        if (head == nullptr) {
            return refs.front() = refs.back() = head = tail = new node{nullptr, value, nullptr};
        }
        return refs.back() = tail = tail->next = new node{tail, value, nullptr};
    }

    friend std::ostream&
    operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        os << "head -> ";
        if (list.head == nullptr) {
            os << "nullptr";
        } else {
            os << list.head->value;
            for (node* curr = list.head->next; curr != nullptr; curr = curr->next) {
                os << " <-> " << curr->value;
            }
        }
        os << " <- tail" << std::endl;
        return os;
    }
};
