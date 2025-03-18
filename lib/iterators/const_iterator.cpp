#include "unrolled_list.h"

template<typename T, size_t NodeMaxSize, typename Allocator>
class unrolled_list<T, NodeMaxSize, Allocator>::const_iterator {
    public:
        using NodePointer = Node*;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        
        const_iterator() = default;
        constexpr explicit const_iterator(NodePointer node, pointer index) : node_(node) {
            ptr_ = index;
        }
        constexpr const_iterator(const const_iterator& other) : node_(other.node_), ptr_(other.ptr_) {
        }

        constexpr reference operator*() const {
            return *ptr_;
        }

        constexpr pointer operator->() const {
            return ptr_;
        }

        constexpr const_iterator& operator++() {
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return *this;
        }

        constexpr const_iterator operator++(int) {
            const_iterator tmp(*this);
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return tmp;
        }

        constexpr const_iterator& operator--() {
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return *this;
        }

        constexpr const_iterator operator--(int) {
            const_iterator tmp = *this;
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return tmp;
        }

        bool operator==(const const_iterator& other) const{
            return ptr_  == other.ptr_;
        }

        bool operator!=(const const_iterator& other) const{
            return ptr_  != other.ptr_;
        }

        constexpr const_iterator operator=(const const_iterator& other) {
            ptr_ = other.ptr_;
            node_ = other.node_;

            return *this;
        }

        constexpr pointer base() const { return node_; }

    private:
        NodePointer node_;
        pointer ptr_;
};