// Buffer class cpp file
#include "BufferClass.h"

unsigned int Buffer::width = WIDTH;
unsigned int Buffer::height = HEIGHT;

Buffer::Buffer() {
	for (unsigned int i = 0; i < Buffer::width; i++)
		for (unsigned int j = 0; j < Buffer::height; j++)
			(*this)[i][j] = 0;
}
Buffer& Buffer::operator= (Buffer that) {
	for (unsigned int i = 0; i < Buffer::width; i++)
		for (unsigned int j = 0; j < Buffer::height; j++)
			(*this)[i][j] = that[i][j];
	return *this;
}
char* Buffer::operator[] (const unsigned int i) {
		return buf[i];
	}