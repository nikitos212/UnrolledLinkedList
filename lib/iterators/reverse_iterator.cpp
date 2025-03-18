#include "unrolled_list.h"

template<typename T, size_t NodeMaxSize, typename Allocator>
class unrolled_list<T, NodeMaxSize, Allocator>::reverse_iterator {
    public:
        using NodePointer = Node*;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        
        reverse_iterator() = default;
        explicit reverse_iterator(NodePointer node, pointer index) : node_(node) {
            ptr_ = index;
        }
        reverse_iterator(const reverse_iterator& other) : node_(other.node_), ptr_(other.ptr_) {
        }
    
        reference operator*() const {
            return *ptr_;
        }

        pointer operator->() const {
            return ptr_;
        }
    
        reverse_iterator& operator--() {
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return *this;
        }

        reverse_iterator operator--(int) {
            auto tmp(*this);
            if (node_->numElements >= 1 && ptr_ == &node_->elements[node_->numElements - 1] && node_->next) {
                node_ = node_->next;
                ptr_ = &(node_->elements[0]);
            } else {
                ++ptr_;
            }

            return tmp;
        }

        reverse_iterator& operator++() {
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return *this;
        }

        reverse_iterator operator++(int) {
            auto tmp = *this;
            if (ptr_ == &node_->elements[0] && node_->prev) {
                node_ = node_->prev;
                ptr_ = &(node_->elements[node_->numElements - 1]);
            } else {
                --ptr_;
            }

            return tmp;
        }

        bool operator==(const reverse_iterator& other) const{
            return ptr_  == other.ptr_;
        }

        bool operator!=(const reverse_iterator& other) const{
            return ptr_  != other.ptr_;
        }

        reverse_iterator operator=(const reverse_iterator& other) {
            ptr_ = other.ptr_;
            node_ = other.node_;

            return *this;
        }
    
        pointer base() const { return node_; }

        private:
            NodePointer node_;
            pointer ptr_;
};