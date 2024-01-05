#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
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

    DoublyLinkedList(S size = SIZE) : _size{size} { assert(size > 0); }

    DoublyLinkedList(T* start, T* stop, S size = SIZE) : _size{size} {
        assert(size > 0);
        for (; start != stop; ++start) {
            push_tail(*start);
        }
    }

    template <class Iterator>
    DoublyLinkedList(const Iterator& begin, const Iterator& end, S size = SIZE) : _size{size} {
        assert(size > 0);
        for (auto it = begin; it != end; ++it) {
            push_tail(*it);
        }
    }

    ~DoublyLinkedList() { this->clear(); }

    void
    clear(void) noexcept {
        std::function<void(Node*)> _delete;
        _delete = [&_delete](Node* head) -> void {
            if (head == nullptr) {
                return;
            }
            _delete(head->next);
            delete head;
        };
        _delete(_refs[0]);

        _len = 0;
        _refs = {nullptr, nullptr};
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

    [[nodiscard]] Node*
    at(uint64_t pos) const {
        if (pos >= _len) {
            throw std::out_of_range("pos >= length");
        }

        Node* node = _refs[pos / _size];
        for (S i = 0; i < pos % _size; ++i) {
            node = node->next;
        }
        return node;
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
    operator==(const DoublyLinkedList<T>& other) const noexcept {
        if (this->_len != other._len) {
            return false;
        }
        for (auto it1 = this->cbegin(), it2 = other.cbegin(); it1 != other.cend(); ++it1, ++it2) {
            if (*it1 != *it2) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] constexpr bool
    operator!=(const DoublyLinkedList<T>& other) const noexcept {
        return !(*this == other);
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
        Node* _node;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node) : _node{node} {}

        [[nodiscard]] constexpr reference
        operator*() const noexcept {
            return _node->value;
        }

        constexpr Iterator&
        operator++() noexcept {
            _node = _node->next;
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
            _node = _node->prev;
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
    };

    Iterator
    begin() const {
        return Iterator(_refs.front());
    }

    Iterator
    end() const {
        return Iterator(nullptr);
    }

    class ConstIterator {
        Node* _node;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = const T&;

        explicit ConstIterator(Node* node) : _node{node} {}

        [[nodiscard]] constexpr reference
        operator*() const noexcept {
            return _node->value;
        }

        constexpr ConstIterator&
        operator++() noexcept {
            _node = _node->next;
            return *this;
        }

        constexpr ConstIterator
        operator++(int) noexcept {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr ConstIterator&
        operator--() noexcept {
            _node = _node->prev;
            return *this;
        }

        constexpr ConstIterator
        operator--(int) noexcept {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        [[nodiscard]] constexpr bool
        operator==(const ConstIterator& other) const noexcept {
            return _node == other._node;
        }

        [[nodiscard]] constexpr bool
        operator!=(const ConstIterator& other) const noexcept {
            return !(*this == other);
        }
    };

    ConstIterator
    cbegin() const {
        return ConstIterator(_refs.front());
    }

    ConstIterator
    cend() const {
        return ConstIterator(nullptr);
    }

    class ReverseIterator {
        Node* _node;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit ReverseIterator(Node* node) : _node{node} {}

        [[nodiscard]] constexpr reference
        operator*() const noexcept {
            return _node->value;
        }

        constexpr ReverseIterator&
        operator++() noexcept {
            _node = _node->prev;
            return *this;
        }

        constexpr ReverseIterator
        operator++(int) noexcept {
            ReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr ReverseIterator&
        operator--() noexcept {
            _node = _node->next;
            return *this;
        }

        constexpr ReverseIterator
        operator--(int) noexcept {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        [[nodiscard]] constexpr bool
        operator==(const ReverseIterator& other) const noexcept {
            return _node == other._node;
        }

        [[nodiscard]] constexpr bool
        operator!=(const ReverseIterator& other) const noexcept {
            return !(*this == other);
        }
    };

    ReverseIterator
    rbegin() const {
        return ReverseIterator(_refs.back());
    }

    ReverseIterator
    rend() const {
        return ReverseIterator(nullptr);
    }

    class ConstReverseIterator {
        Node* _node;

      public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = const T&;

        explicit ConstReverseIterator(Node* node) : _node{node} {}

        [[nodiscard]] constexpr reference
        operator*() const noexcept {
            return _node->value;
        }

        constexpr ConstReverseIterator&
        operator++() noexcept {
            _node = _node->prev;
            return *this;
        }

        constexpr ConstReverseIterator
        operator++(int) noexcept {
            ConstReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr ConstReverseIterator&
        operator--() noexcept {
            _node = _node->next;
            return *this;
        }

        constexpr ConstReverseIterator
        operator--(int) noexcept {
            ConstReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        [[nodiscard]] constexpr bool
        operator==(const ConstReverseIterator& other) const noexcept {
            return _node == other._node;
        }

        [[nodiscard]] constexpr bool
        operator!=(const ConstReverseIterator& other) const noexcept {
            return !(*this == other);
        }
    };

    ConstReverseIterator
    crbegin() const {
        return ConstReverseIterator(_refs.back());
    }

    ConstReverseIterator
    crend() const {
        return ConstReverseIterator(nullptr);
    }

  private:
    uint64_t _len = 0;
    // _refs.front() = head, _refs.back() = tail
    std::vector<Node*> _refs = {nullptr, nullptr};
    // > 0
    S _size;
};
