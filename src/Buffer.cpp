#include <iostream>
#include <cstring>
#include "Buffer.h"
namespace xac {
Buffer::Buffer() {
	buffer = (char*)malloc(10 * 1024);	
	size_ = 10 * 1024;
}

Buffer::Buffer(size_t size) : size_(size) {
	buffer = (char*)malloc(size);
}

void Buffer::ReAlloc() {
		
}

void Buffer::MemcopyToBuffer(void* src, size_t size) {
	memcpy(buffer + end_, src, size);
	end_ += size;
}

void Buffer::MemcopyFromBuffer(void* des, size_t size) {
	memcpy(des, buffer + start_, size);
	start_ += size;
}

}
