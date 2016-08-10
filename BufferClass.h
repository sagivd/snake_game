/* Buffer class h file */

#ifndef __BUFFER_CLASS_H
#define __BUFFER_CLASS_H

#define WIDTH 30
#define HEIGHT 20

class Buffer {
public:
	static unsigned int width, height;
	char buf[WIDTH][HEIGHT+2];

	Buffer();
	Buffer& operator= (Buffer);
	char* operator[] (const unsigned int);
};

#endif __BUFFER_CLASS_H