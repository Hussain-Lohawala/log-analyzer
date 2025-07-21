#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H	

#include <vector>
#include <cstddef>
#include <stdexcept>

class MemoryPool {
public:
	MemoryPool(std::size_t blockSize=1024, std::size_t blockCount= 128)
		: blockSize(blockSize), blockCount(blockCount) {
		for (std::size_t i = 0; i < blockCount; ++i) {
			pool.push_back(new char[blockSize]);
		}
	}

	~MemoryPool() {
		for (auto block : pool) {
			delete[] block;
		}
		pool.clear();
	}

	void* allocate() {
		if (pool.empty()) {
			throw std::bad_alloc();
		}
		void* ptr = pool.back();
		pool.pop_back();
		return ptr;
	}

	void deallocate(void* ptr) {
		pool.push_back(static_cast<char*>(ptr));
	}

private: 
	std::vector<char*> pool;
	std::size_t blockSize;
	std::size_t blockCount;
};

#endif //MEMORYPOOL_H