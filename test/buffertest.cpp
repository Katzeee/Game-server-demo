#include <iostream>
#include <string>
#include <cstring>
#include "../src/Buffer.h"
using namespace xac;

int main() {
	Buffer* buffer = new RingBuffer(10);
	std::string test = "test";
	char* cbuffer = (char*)malloc(10);
    memset(cbuffer, 0, 10);
    for (auto i = 0; i < 20; i++) {
        buffer->MemcopyToBuffer(const_cast<char*>(test.c_str()), test.length());
        buffer->FillData(4);
        memset(cbuffer, 0, 10);
        buffer->MemcopyFromBuffer(cbuffer, 4);
        buffer->RemoveData(4);
        std::cout << cbuffer << std::endl;
    }
	return 0;
}
