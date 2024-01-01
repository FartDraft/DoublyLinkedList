#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#define SIZE 8

template <typename T, typename S = unsigned>
class DoublyLinkedList {
  public:
    struct Node {
        Node* prev;
        T value;
        Node* next;
    };

    constexpr DoublyLinkedList(S size = SIZE) : _size{size} {}

    Node*
    push_tail(const T& value) {
        // TODO: Size'ify
        ++_len;
        if (this->head() == nullptr) {
            return _refs.front() = _refs.back() = new Node{nullptr, value, nullptr};
        }
        return _refs.back() = _refs.back()->next = new Node{_refs.back(), value, nullptr};
    }

    friend std::ostream&
    operator<<(std::ostream& os, const DoublyLinkedList<T>& list) noexcept {
        os << "head -> ";
        if (list.head() == nullptr) {
            os << "nullptr";
        } else {
            os << list.head()->value;
            for (Node* curr = list.head()->next; curr != nullptr; curr = curr->next) {
                os << " <-> " << curr->value;
            }
        }
        os << " <- tail" << std::endl;
        return os;
    }

    [[nodiscard]] constexpr bool
    empty(void) const noexcept {
        return _len == 0;
    }

    [[nodiscard]] constexpr auto
    length(void) const noexcept {
        return _len;
    }

    [[nodiscard]] constexpr auto
    head(void) const noexcept {
        return _refs.front();
    }

    [[nodiscard]] constexpr auto
    tail(void) const noexcept {
        return _refs.back();
    }

    [[nodiscard]] constexpr auto
    size(void) const noexcept {
        return _size;
    }

  private:
    uint64_t _len = 0;
    // _refs.front() = head, _refs.back() = tail
    std::vector<Node*> _refs = {nullptr, nullptr};
    S _size;
};
