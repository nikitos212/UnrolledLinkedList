#pragma once
#include <cstddef>
#include <initializer_list>
#include <memory>
#include "lib/allocator/PoolAllocatorNode.cpp"

template<typename T, size_t NodeMaxSize = 10, typename Allocator = std::allocator<T>>
class unrolled_list {
  protected:
    struct Node {
      Node* next = nullptr; 
      Node* prev = nullptr;
      int numElements = 0;
      T elements[NodeMaxSize];
    };

    Node* start_ = nullptr;
    Node* end_ = nullptr;
    Node* cur_ = nullptr;
    size_t size_ = 0;

    Node* create_node ();
    void shift_left (Node* memoryNode, Node* curNode, size_t index);
    void shift_right (Node* memoryNode, Node* curNode, const T& value, size_t index = 0);

  public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using NodeAllocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<Node>;
    NodeAllocator node_alloc;

    class iterator;
    class const_iterator;
    class reverse_iterator;
    class const_reverse_iterator;

    explicit unrolled_list();
    explicit unrolled_list( const Allocator& alloc );
    explicit unrolled_list( size_type count, const Allocator& = Allocator() );
    unrolled_list( size_type count, const_reference value, const Allocator& alloc = Allocator() );
    template< class InputIt >
    unrolled_list( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
    unrolled_list( const unrolled_list& other );
    unrolled_list( const unrolled_list& other, const Allocator& alloc );
    unrolled_list( std::initializer_list<value_type> init, const Allocator& alloc = Allocator() );

    ~unrolled_list();

    reference operator=( const_reference other );

    void assign( size_type count, const_reference value );
    template< class InputIt >
    void assign( InputIt first, InputIt last );
    void assign( std::initializer_list<T> ilist );

    allocator_type get_allocator() const noexcept;

    reference at( size_type pos );
    const_reference at( size_type pos ) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const noexcept;
    
    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    
    void clear () noexcept;
    void clear_node (Node* cur) noexcept;

    iterator insert( iterator pos, const T& value );
    iterator insert( const_iterator pos, const T& value );
    iterator insert( const_iterator pos, size_type count, const T& value );
    template<class InputIt>
    iterator insert( const_iterator pos, InputIt first, InputIt last );

    iterator erase( const_iterator pos ) noexcept;
    iterator erase( const_iterator first, const_iterator last ) noexcept;

    void push_back( const_reference& value );
    void pop_back() noexcept;
    void push_front( const_reference& value );
    void pop_front() noexcept;

    void resize( size_type count );
    void resize( size_type count, const_reference& value );

    void swap( unrolled_list& other ) noexcept;

    bool operator==( const unrolled_list& rhs ) const;
};

namespace std {
  template <>
  struct iterator_traits<unrolled_list<int>::iterator> {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;
  };
}