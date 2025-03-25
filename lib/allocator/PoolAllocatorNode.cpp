#include <cstddef>

template<typename Node>
class PoolAllocatorNode {
private:
    Node* firstFreeNode = nullptr;

public:
    using value_type = Node;
    using pointer = Node*;
    using const_pointer = const Node*;
    using reference = Node&;
    using const_reference = const Node&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template<typename U>
    struct rebind {
        using other = PoolAllocatorNode<U>;
    };

    explicit PoolAllocatorNode(size_t numNodes = 1000) {
        Node* memory = static_cast<Node*>(operator new[](numNodes * sizeof(Node)));
        
        for (size_t i = 0; i < numNodes - 1; ++i) {
            memory[i].next = &memory[i + 1];
        }
        memory[numNodes - 1].next = nullptr;
        firstFreeNode = memory;
    }

    ~PoolAllocatorNode() {
        operator delete[](reinterpret_cast<void*>(firstFreeNode));
    }

    Node* allocate(int count = 1) {
        if (firstFreeNode == nullptr) {
            return nullptr;
        }
        Node* result = firstFreeNode;
        firstFreeNode = firstFreeNode->next;
        return result;
    }

    void deallocate(Node* node, int count = 1) {
        if (node != nullptr) {
            node->next = firstFreeNode;
            firstFreeNode = node;
        }
    }
};