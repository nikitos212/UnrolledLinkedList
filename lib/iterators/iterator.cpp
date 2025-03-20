#include "unrolled_list.h"
#include <cstddef>
#include <iostream>

template<typename T, size_t NodeMaxSize, typename Allocator>
class unrolled_list<T, NodeMaxSize, Allocator>::iterator {
    public:
        using NodePointer = Node*;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        
        iterator() = default;
        explicit iterator(NodePointer node, pointer index) : node_(node) {
            ptr_ = index;
        }
        iterator(const iterator& other) : node_(other.node_), ptr_(other.ptr_) {
        }
    
        reference operator*() const {
            return *ptr_;
        }

        pointer operator->() const {
            return ptr_;
        }
    
        iterator& operator++() {
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return *this;
        }

        iterator operator++(int) {
            auto tmp(*this);
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return tmp;
        }

        iterator& operator+=(size_t inc) {
            for (size_t i = 0; i < inc; ++i) {
                if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                    node_ = node_->next;
                    ptr_ = &(node_->elements[0]);
                } else {
                    ++ptr_;
                }
            }

            return *this;
        }

        iterator& operator--() {
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return *this;
        }

        iterator operator--(int) {
            auto tmp = *this;
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return tmp;
        }

        iterator& operator-=(size_t dec) {
            for (size_t i = 0; i < dec; ++i) {
                if (ptr_ == &node_->elements[0] && node_->prev) {
                    node_ = node_->prev;
                    ptr_ = &(node_->elements[node_->numElements - 1]);
                } else {
                    --ptr_;
                }
            }

            return *this;
        }

        bool operator==(const iterator& other) const{
            return ptr_  == other.ptr_;
        }

        bool operator!=(const iterator& other) const{
            return ptr_  != other.ptr_;
        }
        
        iterator operator=(const iterator& other) {
            ptr_ = other.ptr_;
            node_ = other.node_;

            return *this;
        }

        NodePointer& getNodePointer() {
            return node_;
        }

        pointer& get_pointer() {
            return ptr_;
        }

        private:
            NodePointer node_;
            pointer ptr_;
};