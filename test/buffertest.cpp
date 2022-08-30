#include <iostream>
#include <string>
#include "../src/Buffer.h"
using namespace xac;

int main() {
	Buffer* buffer = new Buffer();
	std::string test = "test";
	buffer->MemcopyToBuffer(const_cast<char*>(test.c_str()), test.length());
	char* cbuffer = (char*)malloc(10);
	buffer->MemcopyFromBuffer(cbuffer, 3);
	std::cout << cbuffer << std::endl;
	return 0;
}
