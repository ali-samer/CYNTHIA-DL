#pragma once


#include <cstddef>
#include <vector>
#include <cassert>


CYDL_BEGIN_LIB_NAMESPACE


CYDL_BEGIN_LIB_POLICIES_NAMESPACE
class FixedBlockAllocation
{
private:
	struct Block
	{
		Block* next;
	};

	Block* m_freeBlocks;
	void * m_pool;
	size_t m_blockSize;
	size_t m_blockCount;
public:
	FixedBlockAllocation ( size_t blockSize , size_t blockCount )
		: m_blockSize( blockSize ) , m_blockCount( blockCount ) , m_pool( nullptr ) ,
		  m_freeBlocks( nullptr )
	{
		assert( blockSize >= sizeof( Block* ) ); // Ensure block can store the pointer
		m_pool       = operator new( blockSize * blockCount ); // Allocate memory pool
		m_freeBlocks = static_cast<Block*>(m_pool);

		// Initialize the free block list
		auto         current = m_freeBlocks;
		for ( size_t i       = 1 ; i < blockCount ; ++i )
		{
			current->next = reinterpret_cast<Block*>(reinterpret_cast<char*>(m_pool) + i * blockSize);
			current = current->next;
		}
		current->next = nullptr;
	}

	~FixedBlockAllocation() { operator delete(m_pool); }

	void* allocate()
	{
		if (!m_freeBlocks)
			return nullptr;

		Block* block = m_freeBlocks;
		m_freeBlocks = m_freeBlocks->next;
		return block;
	}

	void deallocate(void* ptr)
	{
		auto block = static_cast<Block*>(ptr);
		block->next = m_freeBlocks;
		m_freeBlocks = block;
	}
};
CYDL_END_LIB_POLICIES_NAMESPACE


CYDL_END_LIB_NAMESPACE

/*
 *
// Usage example
int main() {
    FixedBlockAllocation allocator(sizeof(int), 100); // 100 blocks of size sizeof(int)
    int* intPtr = static_cast<int*>(allocator.allocate());
    // Use intPtr...
    allocator.deallocate(intPtr);
    return 0;
}
 * */