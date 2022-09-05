#include <iostream>
#include <cstring>
#include "Buffer.h"
namespace xac {
Buffer::Buffer() {
	size_ = 0;
	capacity_ = 10 * 1024;
	buffer = (char*)malloc(capacity_);	
    memset(buffer, 0, capacity_);
}

Buffer::Buffer(size_t size) : size_(0), capacity_(size) {
	buffer = (char*)malloc(size);
    memset(buffer, 0, capacity_);
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
bool Buffer::MemcopyToBuffer(char* src, size_t size) {
    size_t empty_size = capacity_ - size_;
    if (empty_size <= size) {
        return false;
    }
	memcpy(buffer + end_, src, size);
    return true;
}

// TODO: overflow check
bool Buffer::MemcopyFromBuffer(char* des, size_t size) {
	memcpy(des, buffer + start_, size);
    return true;
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

void Buffer::FillData(size_t size) {
    size_ += size;
    end_ += size;
}

void Buffer::RemoveData(size_t size) {
    start_ += size;
}

bool RingBuffer::MemcopyFromBuffer(char* des, size_t size) {
    if (size_ < size) {
        std::cout << "Don't have enough data" << std::endl;
        return false;
    }
    if (end_ > start_) {
        memcpy(des, buffer + start_, size);
    } else {
        memcpy(des, buffer + start_, capacity_ - start_); // get rear
        memcpy(des + capacity_ - start_, buffer, size - capacity_ + start_); // get front
    }
    return true;
}

bool RingBuffer::MemcopyToBuffer(char* src, size_t size) {
    auto empty_size = capacity_ - size_;
    if (empty_size <= size) {
        std::cout << "No enough position!" << std::endl;
        return false;
    }
    if (end_ >= start_) {
        if (capacity_ - end_ >= size) {
            memcpy(buffer + end_, src, size);
        } else {
            auto rear_empty = capacity_ - end_;
            memcpy(buffer + end_, src, rear_empty); // fill rear
            memcpy(buffer, src + rear_empty, size - rear_empty); // fill front
        }
    } else {
        memcpy(buffer + end_, src, size);
    }
    return true;
}

void RingBuffer::RemoveData(size_t size) {
    start_ = (start_ + size) % capacity_;
    size_ -= size;
}

void RingBuffer::FillData(size_t size) {
    end_ = (end_ + size) % capacity_;
    size_ += size;
}
}
