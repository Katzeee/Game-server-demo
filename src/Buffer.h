#pragma	once
#include <iostream>

namespace xac {

static void* malloc(size_t size) {
    std::cout << "malloc " << size << std::endl;
    return ::malloc(size);
}

static void free(void* ptr) {
    std::cout << "free " << std::endl;
    ::free(ptr);
}
class Buffer {
protected:
	char* buffer = nullptr;
	size_t start_ = 0; // buffer start position
	size_t end_ = 0; // buffer end position
	size_t size_ = 0; // buffer size
    // when end_ == start_, buffer is empty
    size_t capacity_ = 0; // buffer capacity
public:
	Buffer();
	Buffer(size_t size);
	virtual void ReAlloc(size_t size);
	size_t GetSize();
	size_t GetCapacity();
    virtual size_t GetEmptySize();
	virtual bool MemcopyFromBuffer(char* des, size_t size);
	virtual bool MemcopyToBuffer(char* src, size_t size);
    virtual bool FillData(size_t size);
    virtual bool RemoveData(size_t size);
	virtual ~Buffer();
};

class RingBuffer : public Buffer {
public:
    RingBuffer() : Buffer() {}
    RingBuffer(size_t size) : Buffer(size) {}
    bool MemcopyFromBuffer(char* des, size_t size) override;
    bool MemcopyToBuffer(char* src, size_t size) override;
    bool RemoveData(size_t size) override;
    bool FillData(size_t size) override;
    size_t GetEmptySize() override;
};

class NormalBuffer : public Buffer {
public:
    NormalBuffer() : Buffer() { std::cout << "Normal buffer" << std::endl; }
    NormalBuffer(size_t size) : Buffer(size) {}
    // ~NormalBuffer() { Buffer::~Buffer(); }
    // void MemcopyFromBuffer(char* des, size_t size) { Buffer::MemcopyFromBuffer(des, size); }
    // void MemcopyToBuffer(char* src, size_t size) { Buffer::MemcopyToBuffer(src, size); }
};


}
