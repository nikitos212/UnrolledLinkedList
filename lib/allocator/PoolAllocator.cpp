#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(size_t numBlocks, size_t blockSize) : blockSize(blockSize) {
    this->blockSize = ((blockSize + alignment - 1) / alignment) * alignment;
    size_t totalSize = numBlocks * this->blockSize;
    poolMemory = new char[totalSize];
    freeBlockPtr = poolMemory;
}

PoolAllocator::~PoolAllocator() {
    delete[] poolMemory;
}

void* PoolAllocator::allocate() {
    if (freeBlockPtr == nullptr) {
        return nullptr;
    }
    
    void* result = freeBlockPtr;
    freeBlockPtr += blockSize;
    
    return result;
}


void PoolAllocator::deallocate(void* ptr) {
    freeBlockPtr = reinterpret_cast<char*>(ptr);
}

