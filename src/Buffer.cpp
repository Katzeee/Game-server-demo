#include <iostream>
#include <cstring>
#include "Buffer.h"
namespace xac {
Buffer::Buffer() {
	size_ = 10 * 1024;
	capacity_ = 10 * 1024;
	buffer = (char*)malloc(size_);	
    memset(buffer, 0, size_);
}

Buffer::Buffer(size_t size) : size_(size), capacity_(size) {
	buffer = (char*)malloc(size);
    memset(buffer, 0, size_);
}

void Buffer::ReAlloc(size_t size = 0) {
    if (size == 0 || size < capacity_) {
        size = 2 * capacity_;
    }
    char* new_buffer = (char*)malloc(size);
    memcpy(new_buffer, buffer, capacity_);
    capacity_ = size;
    free(buffer);
    buffer = new_buffer;
}

// TODO: overflow check
void Buffer::MemcopyToBuffer(char* src, size_t size) {
	memcpy(buffer + end_, src, size);
}

// TODO: overflow check
void Buffer::MemcopyFromBuffer(char* des, size_t size) {
	memcpy(des, buffer + start_, size);
}

Buffer::~Buffer() {
    free(buffer);
}

size_t Buffer::GetSize() {
    return size_;
}

size_t Buffer::GetCapacity() {
    return capacity_;
}

}
