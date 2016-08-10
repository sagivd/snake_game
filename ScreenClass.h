/* Screen class h file */

#ifndef __SCREEN_CLASS_H
#define __SCREEN_CLASS_H

#include <Windows.h>

class Screen {
	HANDLE hOut;
public:
	Screen();

	void setCursorPosition(int, int);
	void updateScreen(Buffer &, Buffer &);
	void updateScore(unsigned int);
	void updateScore(unsigned int, unsigned int);
};

#endif __SCREEN_CLASS_H