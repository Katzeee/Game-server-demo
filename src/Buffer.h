#pragma	once
#include <iostream>

namespace xac {
class Buffer {
protected:
	char* buffer;
	size_t start_ = 0;
	size_t end_ = 0;
	size_t size_ = 0;
    size_t capacity_ = 0;
public:
	Buffer();
	Buffer(size_t size);
	virtual void ReAlloc(size_t size);
	size_t GetSize();
	size_t GetCapacity();
	virtual void MemcopyFromBuffer(char* des, size_t size);
	virtual void MemcopyToBuffer(char* src, size_t size);
    virtual void FillData() {}
    virtual void RemoveData() {}
	virtual ~Buffer();
};

class RingBuffer : public Buffer {

};

class NormalBuffer : public Buffer {
public:
    NormalBuffer() : Buffer() {}
    NormalBuffer(size_t size) : Buffer(size) {}
    ~NormalBuffer() { Buffer::~Buffer(); }
    void MemcopyFromBuffer(char* des, size_t size) { Buffer::MemcopyFromBuffer(des, size); }
    void MemcopyToBuffer(char* src, size_t size) { Buffer::MemcopyToBuffer(src, size); }
};


}
