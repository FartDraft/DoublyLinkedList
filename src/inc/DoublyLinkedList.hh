#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

/**
 * @brief doubly linked list implementation with vector of references to every size-th element
 *
 * @tparam T value type
 * @tparam S size type = unsigned int
 *
 * Constructors:
 *     - DoublyLinkedList(S size) noexcept;
 *     - DoublyLinkedList(S size, std::initializer_list<T> init);
 *     - DoublyLinkedList(S size, T* start, T* stop);
 *     - template <class InputIt>
 *       DoublyLinkedList(S size, const InputIt& begin, const InputIt& end);
 */
template <typename T, typename S = unsigned>
class DoublyLinkedList {
  public:
    struct Node {
        Node* prev;
        T value;
        Node* next;
    };

    DoublyLinkedList(S size) noexcept : _size(size) { assert(size > 0); }

    DoublyLinkedList(S size, const std::initializer_list<T>& init) : _size(size) {
        assert(size > 0);
        for (const T& value : init) {
            push_tail(value);
        }
    }

    DoublyLinkedList(S size, T* start, T* stop) : _size(size) {
        assert(size > 0);
        for (; start != stop; ++start) {
            push_tail(*start);
        }
    }

    template <class InputIt>
    DoublyLinkedList(S size, const InputIt& begin, const InputIt& end) : _size(size) {
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

    Node*
    push_tail(T&& value) {
        ++_len;
        if (_refs.front() == nullptr) {
            return _refs.front() = _refs.back() = new Node{nullptr, std::move(value), nullptr};
        }
        if (_len > 2 and (_len - 2) % _size == 0) {
            Node* new_node = new Node{_refs.back(), std::move(value), nullptr};
            _refs.back()->next = new_node;
            _refs.push_back(new_node);
            return new_node;
        }
        return _refs.back() = _refs.back()->next = new Node{_refs.back(), std::move(value), nullptr};
    }

    Node*
    push_head(const T& value) {
        ++_len;
        if (_refs.front() == nullptr) {
            return _refs.front() = _refs.back() = new Node{nullptr, value, nullptr};
        }
        _refs.front()->prev = new Node{nullptr, value, _refs.front()};
        for (size_t i = 0; i < _refs.size() - 1; ++i) {
            _refs[i] = _refs[i]->prev;
        }
        if (_len > 2 and (_len - 2) % _size == 0) {
            _refs.back() = _refs.back()->prev;
            _refs.push_back(_refs.back()->next);
        }
        return _refs.front();
    }

    Node*
    push_head(T&& value) {
        ++_len;
        if (_refs.front() == nullptr) {
            return _refs.front() = _refs.back() = new Node{nullptr, std::move(value), nullptr};
        }
        _refs.front()->prev = new Node{nullptr, std::move(value), _refs.front()};
        for (size_t i = 0; i < _refs.size() - 1; ++i) {
            _refs[i] = _refs[i]->prev;
        }
        if (_len > 2 and (_len - 2) % _size == 0) {
            _refs.back() = _refs.back()->prev;
            _refs.push_back(_refs.back()->next);
        }
        return _refs.front();
    }

    Node*
    insert(uint64_t pos, const T& value) {
        if (pos == 0) {
            return push_head(value);
        }
        if (pos == _len) {
            return push_tail(value);
        }
        if (pos > _len) {
            throw std::out_of_range("pos > length");
        }

        Node* node = at(pos);
        node->prev = node->prev->next = new Node{node->prev, value, node};
        for (size_t i = (pos % _size ? 1 : 0) + pos / _size; i < _refs.size() - 1; ++i) {
            _refs[i] = _refs[i]->prev;
        }
        ++_len;
        if (_len > 2 and (_len - 2) % _size == 0) {
            _refs.back() = _refs.back()->prev;
            _refs.push_back(_refs.back()->next);
        }
        return node->prev;
    }

    Node*
    insert(uint64_t pos, T&& value) {
        if (pos == 0) {
            return push_head(std::move(value));
        }
        if (pos == _len) {
            return push_tail(std::move(value));
        }
        if (pos > _len) {
            throw std::out_of_range("pos > length");
        }

        Node* node = at(pos);
        node->prev = node->prev->next = new Node{node->prev, std::move(value), node};
        for (size_t i = (pos % _size ? 1 : 0) + pos / _size; i < _refs.size() - 1; ++i) {
            _refs[i] = _refs[i]->prev;
        }
        ++_len;
        if (_len > 2 and (_len - 2) % _size == 0) {
            _refs.back() = _refs.back()->prev;
            _refs.push_back(_refs.back()->next);
        }
        return node->prev;
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

    DoublyLinkedList<T>&
    operator=(const DoublyLinkedList<T>& other) {
        clear();
        for (const T& value : other) {
            push_tail(value);
        }
        return *this;
    }

    DoublyLinkedList<T>&
    operator=(std::initializer_list<T> init) {
        clear();
        for (const T& value : init) {
            push_tail(value);
        }
        return *this;
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
