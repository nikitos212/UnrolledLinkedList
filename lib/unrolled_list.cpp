#include "unrolled_list.h"
#include "iterators/iterator.cpp"
#include "iterators/const_iterator.cpp"
#include "iterators/reverse_iterator.cpp"
#include "iterators/const_reverse_iterator.cpp"
#include <cstddef>
#include <limits>
#include <iostream>

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::Node* unrolled_list<T, NodeMaxSize, Allocator>::create_node() {
    Node* newNode = node_alloc.allocate(1);
    newNode->numElements = 0;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    return newNode;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list() {
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( const Allocator& alloc ) {
    NodeAllocator node_alloc(alloc);
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( size_type count, const Allocator& alloc ) {
    NodeAllocator node_alloc(alloc);
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
    if (count > 0) {
        try {
            for (size_t i = 0; i < count; ++i) {
                push_back(0);
            }
        } catch (...) {
            clear();
            throw;
        }
    }
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( size_type count, const_reference value, const Allocator& alloc ) {
    NodeAllocator node_alloc(alloc);
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
    if (count > 0) {
        try {
            for (size_t i = 0; i < count; ++i) {
                push_back(value);
            }
        } catch (...) {
            clear();
            throw;
        }
    }
}

template<typename T, size_t NodeMaxSize, typename Allocator>
template<class InputIt>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( InputIt first, InputIt last, const Allocator& alloc ) {
    NodeAllocator node_alloc(alloc);
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
    try {
        for (auto& i = first; first != last; ++first) {
            push_back(*i);
        }
    } catch (...) {
        clear();
        throw;
    }
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( std::initializer_list<value_type> init, const Allocator& alloc) {
    NodeAllocator node_alloc(alloc);
    Node* newNode = create_node();
    start_ = newNode;
    end_ = newNode;
    cur_ = newNode;
    try {
        for (auto& i : init) {
            push_back(i);
        }
    } catch (...) {
        clear();
        throw;
    }
}


template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::clear() noexcept{
    Node* cur = start_;
    while (true) {
        Node* next = cur->next;
        for (size_t i  = 0; i < cur_->numElements; ++i) {
            cur_->elements[i].~T();
        }
        node_alloc.deallocate(cur, 1);
        if (cur == end_) {
            break;
        }
        cur = next;
    }
    start_ = nullptr;
    end_ = nullptr;
    cur_ = nullptr;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::clear_node(Node* cur) noexcept{
    Node* next = cur->next;
    for (size_t i  = 0; i < cur_->numElements; ++i) {
        cur_->elements[i].~T();
    }
    node_alloc.deallocate(cur, 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( const unrolled_list& other) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::unrolled_list( const unrolled_list& other, const Allocator& alloc ) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::~unrolled_list() {
    Node* cur = start_;
    while (true) {
        Node* next = cur->next;
        for (size_t i  = 0; i < cur_->numElements; ++i) {
            cur_->elements[i].~T();
        }
        node_alloc.deallocate(cur, 1);
        if (cur == end_) {
            break;
        }
        cur = next;
    }
    start_ = nullptr;
    end_ = nullptr;
    cur_ = nullptr;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reference unrolled_list<T, NodeMaxSize, Allocator>::operator=( const_reference other ) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::assign( size_type count, const_reference value ) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
template< class InputIt >
void unrolled_list<T, NodeMaxSize, Allocator>::assign( InputIt first, InputIt last ) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::assign( std::initializer_list<T> ilist ) {
    
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::allocator_type unrolled_list<T, NodeMaxSize, Allocator>::get_allocator() const noexcept{
    return allocator_type();
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reference unrolled_list<T, NodeMaxSize, Allocator>::at( size_type pos ) {
    size_t count = 0;
    iterator end = this->end();
    for (iterator i = this->begin(); i != end; ++i) {
        ++count;
        if (count == pos) {return *i;}
    }

    return 0;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reference unrolled_list<T, NodeMaxSize, Allocator>::at( size_type pos ) const {
    size_t count = 0;
    const_iterator end = this->end();
    for (const_iterator i = this->begin(); i != end; ++i) {
        ++count;
        if (count == pos) {return *i;}
    }

    return 0;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reference unrolled_list<T, NodeMaxSize, Allocator>::front() {
    return *iterator(start_, &start_->elements[0]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reference unrolled_list<T, NodeMaxSize, Allocator>::front() const{
    return *const_iterator(start_, &start_->elements[0]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reference unrolled_list<T, NodeMaxSize, Allocator>::back() {
    return *iterator(end_, &end_->elements[end_->numElements - 1]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reference unrolled_list<T, NodeMaxSize, Allocator>::back() const{
    return *const_iterator(end_, &end_->elements[end_->numElements - 1]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::begin() {
    return iterator(start_, &start_->elements[0]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_iterator unrolled_list<T, NodeMaxSize, Allocator>::begin() const{
    return const_iterator(start_, &start_->elements[0]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_iterator unrolled_list<T, NodeMaxSize, Allocator>::cbegin() const noexcept{
    return const_iterator(start_, &start_->elements[0]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::end() {
    return iterator(end_, &end_->elements[end_->numElements - 1] + 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_iterator unrolled_list<T, NodeMaxSize, Allocator>::end() const{
    return const_iterator(end_, &end_->elements[end_->numElements - 1] + 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_iterator unrolled_list<T, NodeMaxSize, Allocator>::cend() const noexcept{
    return const_iterator(end_, &end_->elements[end_->numElements - 1] + 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::rbegin() {
    return reverse_iterator(end_, &end_->elements[end_->numElements - 1]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::rbegin() const{
    return const_reverse_iterator(end_, &end_->elements[end_->numElements - 1]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::crbegin() const noexcept{
    return const_reverse_iterator(end_, &end_->elements[end_->numElements - 1]);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::rend() {
    return reverse_iterator(start_, &start_->elements[0] - 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::rend() const{
    return const_reverse_iterator(start_, &start_->elements[0] - 1);
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::const_reverse_iterator unrolled_list<T, NodeMaxSize, Allocator>::crend() const noexcept{
    return const_reverse_iterator(start_, &start_->elements[0] - 1);
}



template<typename T, size_t NodeMaxSize, typename Allocator>
bool unrolled_list<T, NodeMaxSize, Allocator>::empty() const{
    if (size_ == 0) return true;
    return false;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::size_type unrolled_list<T, NodeMaxSize, Allocator>::size() const{
    return size_;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::size_type unrolled_list<T, NodeMaxSize, Allocator>::max_size() const{
    return std::numeric_limits<value_type>::max();
}

template<typename T, size_t NodeMaxSize, typename Allocator> 
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::insert( const_iterator pos, const T& value ){

}

template<typename T, size_t NodeMaxSize, typename Allocator> 
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::insert( const_iterator pos, size_type count, const T& value ){

}

template<typename T, size_t NodeMaxSize, typename Allocator>
template<class InputIt>
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::insert( const_iterator pos, InputIt first, InputIt last ) {

}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::erase( const_iterator pos ) noexcept{
    return pos;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
unrolled_list<T, NodeMaxSize, Allocator>::iterator unrolled_list<T, NodeMaxSize, Allocator>::erase( const_iterator first, const_iterator last ) noexcept{
    return first;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::push_back( const_reference& value ) {
    ++size_;
    int& index = cur_->numElements;
    if (index != NodeMaxSize) {
        new (&cur_->elements[index]) value_type(value);
        ++index; 
    } else {
        Node* CurNode;
        if (cur_->next == nullptr) {
            CurNode = create_node();
            end_ = CurNode;
        } else {
            CurNode = cur_->next;
        }
        size_t half_index = (NodeMaxSize % 2 == 0) ? NodeMaxSize / 2 : NodeMaxSize / 2 + 1;
        for(size_t i  = half_index; i < index; ++i) {
            new (&CurNode->elements[i - half_index]) value_type(cur_->elements[i]);
        }
        index = half_index;
        CurNode->numElements = NodeMaxSize - half_index;
        cur_->next = CurNode;
        CurNode->prev = cur_;
        cur_ = CurNode;
        new (&cur_->elements[cur_->numElements]) value_type(value);
        ++cur_->numElements;
    }
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::pop_back() noexcept{
    if (cur_->numElements == 0 && cur_->prev) {
        end_ = cur_->prev;
        clear_node(cur_);
        cur_ = end_;
        cur_->next = nullptr;
    } else if (cur_->numElements == 0 && !cur_->prev) {
        return;
    }
    --size_;
    --cur_->numElements;
    if (cur_->numElements == 0 && cur_->prev) {
        end_ = cur_->prev;
        clear_node(cur_);
        cur_ = end_;
        cur_->next = nullptr;
    }

    return;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::push_front( const_reference& value ) {
    ++size_;
    if (start_->numElements  <= NodeMaxSize - NodeMaxSize / 2) {
        value_type cur = start_->elements[0];
        value_type next = start_->elements[1];
        for (size_t i = 1; i <= start_->numElements; ++i) {
            new (&start_->elements[i]) value_type(cur);
            cur = next;
            next = start_->elements[i + 1];
        }
        new (&start_->elements[0]) value_type(value);
        ++start_->numElements;
    } else {
        Node* CurNode = create_node();
        new (&CurNode->elements[0]) value_type(value);
        ++CurNode->numElements;
        CurNode->next = start_;
        start_->prev = CurNode;
        start_ = CurNode;
        size_t index = 0;
        while (start_->next->numElements  > NodeMaxSize - NodeMaxSize / 2) {
            new (&start_->elements[start_->numElements]) value_type(start_->next->elements[index]);
            ++start_->numElements;
            ++index;
            for (size_t i = 1; i < start_->next->numElements; ++i) {
                new (&start_->next->elements[i - 1]) value_type(start_->next->elements[i]);
            }
            --start_->next->numElements;
        }
    }
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::pop_front() noexcept{
    --size_;
    if (start_->numElements == 0) {
        if (start_->next) {
            Node* cur = start_->next;
            clear_node(start_);
            start_ = cur;
            start_->prev = nullptr;
        } else {
            return;
        }
    }

    for (size_t i = 1; i < start_->numElements; ++i) {
        new (&start_->elements[i - 1]) value_type(start_->elements[i]);
    }
    --start_->numElements;

    if (!start_->next) return;
    bool isSmallNode = false;
    while (start_->numElements < NodeMaxSize - NodeMaxSize / 2 && start_->next->numElements != 0) {
        isSmallNode = true;
        new (&start_->elements[start_->numElements]) value_type(start_->next->elements[0]);
        for (size_t i = 1; i < start_->next->numElements; ++i) {
            new (&start_->next->elements[i - 1]) value_type(start_->next->elements[i]);
        }
        ++start_->numElements;
        --start_->next->numElements;
    }
    if (start_->next->numElements < NodeMaxSize - NodeMaxSize / 2 && isSmallNode) {
        while (start_->next->numElements != 0) {
            new (&start_->elements[start_->numElements]) value_type(start_->next->elements[0]);
            for (size_t i = 1; i < start_->next->numElements; ++i) {
                new (&start_->next->elements[i - 1]) value_type(start_->next->elements[i]);
            }
            ++start_->numElements;
            --start_->next->numElements;
        }
    }

    if (start_->numElements == 0 && start_->next) {
        Node* cur = start_->next;
        clear_node(start_);
        start_ = cur;
        start_->prev = nullptr;
    }

    if (start_->next->numElements == 0) {
        Node* cur = start_->next->next;
        if (end_ == start_->next) {
            end_ = start_;
            cur_ = start_;
        }
        clear_node(start_->next);
        start_->next = cur;
        if (cur) {
            cur->prev = start_;
        }
    }

    return;
}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::resize( size_type count ){

}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::resize( size_type count, const_reference& value ){

}

template<typename T, size_t NodeMaxSize, typename Allocator>
void unrolled_list<T, NodeMaxSize, Allocator>::swap( unrolled_list& other ) noexcept{

}

template<typename T, size_t NodeMaxSize, typename Allocator>
bool unrolled_list<T, NodeMaxSize, Allocator>::operator==( const unrolled_list& rhs ) const{
    if (this->size_ != rhs.size_) return false;
    const_iterator iter_rhs = rhs.begin();
    const_iterator iter_end = this->end();
    for (const_iterator iter = this->begin(); iter != iter_end; ++iter) {
        if (*iter != *iter_rhs) {std::cout << *iter << " " << *iter_rhs << std::endl; return false;}
        ++iter_rhs;
    }

    return true;
}



