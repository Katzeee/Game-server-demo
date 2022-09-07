#include <iostream>
#include <cstring>
#include "Buffer.h"
namespace xac {
Buffer::Buffer() {
	size_ = 0;
	capacity_ = 1 * 128;
	//buffer = (char*)::malloc(capacity_);	
    buffer = new char[capacity_];
    // memset(buffer, 0, capacity_);
}

Buffer::Buffer(size_t size) : size_(0), capacity_(size) {
	buffer = (char*)malloc(size);
    memset(buffer, 0, capacity_);
}

void Buffer::ReAlloc(size_t size = 0) {
    if (GetEmptySize() > size) {
        return;
    }
    if (size == 0) {
        size = capacity_;
    }
    char* new_buffer = (char*)malloc(capacity_ + size);
    memcpy(new_buffer, buffer, capacity_);
    capacity_ += size;
    free(buffer);
    buffer = new_buffer;
}

bool Buffer::MemcopyToBuffer(char* src, size_t size) {
    size_t empty_size = capacity_ - end_;
    if (empty_size <= size) {
        std::cout << "No enough position" << std::endl;
        return false;
    }
	memcpy(buffer + end_, src, size);
    return true;
}

bool Buffer::MemcopyFromBuffer(char* des, size_t size) {
    // size_ is fake to indicate the used part of a buffer having removed data. It is correct to calculate the emptysieze but cannot reflect the real size
    if (size_ < size) {
        std::cout << "Don't have enough data" << std::endl;
        return false;
    }
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

size_t Buffer::GetEmptySize() {
    return capacity_ - end_;
}

bool Buffer::FillData(size_t size) {
    if (size + end_ >= capacity_) {
        return false;
    }
    size_ += size;
    end_ += size;
    return true;
}

bool Buffer::RemoveData(size_t size) {
    if (size_ < size) {
        return false;
    }
    size_ -= size;
    start_ += size;
    return true;
}

size_t RingBuffer::GetEmptySize() {
    if (end_ >= start_) {
        return capacity_ - end_ + start_;
    } else {
        return start_ - end_;
    }
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

bool RingBuffer::RemoveData(size_t size) {
    if (size_ < size) {
        return false;
    }
    start_ = (start_ + size) % capacity_;
    size_ -= size;
    return true;
}

bool RingBuffer::FillData(size_t size) {
    if (size + size_ >= capacity_) {
        return false;
    }
    end_ = (end_ + size) % capacity_;
    size_ += size;
    return true;
}
}
