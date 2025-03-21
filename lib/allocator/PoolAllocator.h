#include <cstddef>

class PoolAllocator {
    private:
        size_t blockSize;
        char* poolMemory;
        char* freeBlockPtr;
    
    public:
        explicit PoolAllocator(size_t numBlocks, size_t blockSize);
        ~PoolAllocator();
        
        void* allocate();
        void deallocate(void* ptr);
    
    private:
        static const size_t alignment = alignof(std::max_align_t);
};