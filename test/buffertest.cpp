#include <iostream>
#include <string>
#include <cstring>
#include "../src/Buffer.h"
using namespace xac;

int main() {
	NormalBuffer* buffer = new NormalBuffer();
	std::string test = "test";
	buffer->MemcopyToBuffer(const_cast<char*>(test.c_str()), test.length() + 1);
	char* cbuffer = (char*)malloc(10);
    memset(cbuffer, 0, 10);
	buffer->MemcopyFromBuffer(cbuffer, 3);
	std::cout << cbuffer << std::endl;
    buffer->ReAlloc(20);
    memset(cbuffer, 0, 10);
	buffer->MemcopyFromBuffer(cbuffer, 3);
	std::cout << cbuffer << std::endl;
	return 0;
}
