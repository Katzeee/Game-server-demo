#pragma	once
#include <iostream>

namespace xac {
class Buffer {
protected:
	char* buffer;
	size_t start_;
	size_t end_;
	size_t size_;
public:
	Buffer();
	Buffer(size_t size);
	void ReAlloc();
	size_t GetBufferSize();
	void MemcopyFromBuffer(void* des, size_t size);
	void MemcopyToBuffer(void* src, size_t size);
	~Buffer();
};
}
