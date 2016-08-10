/* Screen class cpp file */

#include <iostream>
#include "SnakeGame.h"
#include "BufferClass.h"
#include "ScreenClass.h"

void Screen::setCursorPosition(int x, int y)
{
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Screen::updateScreen(Buffer &curBuffer, Buffer &prevBuffer) {
	for (UINT i = 0; i < Buffer::width; i++) {
		for (UINT j = 0; j < Buffer::height; j++) {
			if (curBuffer[i][j] == prevBuffer[i][j])
				continue;

			setCursorPosition(i, j);
			std::cout << curBuffer[i][j];
		}
	}
	std::cout.flush();
}

void Screen::updateScore(unsigned int score) {
	setCursorPosition(1, Buffer::height + 1);
	std::cout << "Player 1 - " << score;
}

void Screen::updateScore(unsigned int score1, unsigned int score2) {
	setCursorPosition(1, Buffer::height + 1);
	std::cout << "Player 1 - " << score1;
	setCursorPosition(1, Buffer::height + 2);
	std::cout << "Player 2 - " << score2;
}

Screen::Screen() {
	// Get the Win32 handle representing standard output.
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// set the cursor visibility off
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursorInfo);
}


