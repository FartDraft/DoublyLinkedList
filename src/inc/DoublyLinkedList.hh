#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
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

    template <class Iterator>
    DoublyLinkedList(const Iterator& it, S size = SIZE) : _size{size} {
        assert(size > 0);
        for (const T& value : it) {
            push_tail(value);
        }
    }

    ~DoublyLinkedList() {
        std::function<void(Node*)> _delete;
        _delete = [&_delete](Node* head) -> void {
            if (head == nullptr) {
                return;
            }
            _delete(head->next);
            delete head;
        };
        _delete(_refs[0]);
    }

    Node*
    push_tail(const T& value) {
        ++_len;
        if (_refs.front() == nullptr) {
            return _refs.front() = _refs.back() = new Node{nullptr, value, nullptr};
        }
        if (_len > 2 and (_len - 2) % _size == 0) {
            Node* new_node = new Node{_refs.back(), value, nullptr};
            _refs.back()->next = new_node;
            _refs.push_back(new_node);
            return new_node;
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
        os << " <- tail";
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

    class Iterator {
      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node, bool is_reversed = false) : _node{node}, _is_reversed{is_reversed} {}

        [[nodiscard]] constexpr reference
        operator*() const noexcept {
            return _node->value;
        }

        constexpr Iterator&
        operator++() noexcept {
            _node = _is_reversed ? _node->prev : _node->next;
            return *this;
        }

        constexpr Iterator
        operator++(int) noexcept {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr Iterator&
        operator--() noexcept {
            _node = _is_reversed ? _node->next : _node->prev;
            return *this;
        }

        constexpr Iterator
        operator--(int) noexcept {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        [[nodiscard]] constexpr bool
        operator==(const Iterator& other) const noexcept {
            return _node == other._node;
        }

        [[nodiscard]] constexpr bool
        operator!=(const Iterator& other) const noexcept {
            return !(*this == other);
        }

      private:
        Node* _node;
        bool _is_reversed;
    };

    Iterator
    begin() const {
        return Iterator(_refs.front());
    }

    Iterator
    rbegin() const {
        return Iterator(_refs.back(), true);
    }

    Iterator
    end() const {
        return Iterator(nullptr);
    }

    Iterator
    rend() const {
        return Iterator(nullptr, true);
    }

  private:
    uint64_t _len = 0;
    // _refs.front() = head, _refs.back() = tail
    std::vector<Node*> _refs = {nullptr, nullptr};
    // > 0
    S _size;
};
