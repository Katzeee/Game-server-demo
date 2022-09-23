#pragma	once
#include <iostream>
#include "IDisposable.h"

namespace xac {

// static void* malloc(size_t size) {
//     std::cout << "malloc " << size << std::endl;
//     return ::malloc(size);
// }

// static void free(void* ptr) {
//     std::cout << "free " << std::endl;
//     ::free(ptr);
// }
class BufferBase {
protected:
	char* buffer_ = nullptr;
	size_t start_ = 0; // buffer start position
	size_t end_ = 0; // buffer end position
	size_t size_ = 0; // buffer size
    // when end_ == start_, buffer is empty
    size_t capacity_ = 0; // buffer capacity
public:
	BufferBase();
	BufferBase(size_t size);
	virtual ~BufferBase();
	size_t GetSize();
	size_t GetCapacity();
	virtual void ReAlloc(size_t size);
    virtual size_t GetEmptySize();
	virtual bool MemcopyFromBuffer(char* des, size_t size);
	virtual bool MemcopyToBuffer(char* src, size_t size);
    virtual bool FillData(size_t size);
    virtual bool RemoveData(size_t size);
    virtual char* GetBufferEndAddr();
    virtual char* GetBufferStartAddr();
};

class RingBuffer : public BufferBase {
public:
    RingBuffer() : BufferBase() {}
    RingBuffer(size_t size) : BufferBase(size) {}
    virtual ~RingBuffer() = default;
    bool MemcopyFromBuffer(char* des, size_t size) override;
    bool MemcopyToBuffer(char* src, size_t size) override;
    bool RemoveData(size_t size) override;
    bool FillData(size_t size) override;
    size_t GetEmptySize() override;
};

class NormalBuffer : public BufferBase {
public:
    NormalBuffer() : BufferBase() {}
    NormalBuffer(size_t size) : BufferBase(size) {}
    virtual ~NormalBuffer() = default;
};


}
