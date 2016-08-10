/*************************************************************************

  /$$$$$$                      /$$                   /$$$        /$$$  
 /$$__  $$                    | $$                  /$$_/       |_  $$ 
| $$  \__/ /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$  /$$/   /$$$$$$$\  $$
|  $$$$$$ | $$__  $$ |____  $$| $$  /$$/ /$$__  $$| $$   /$$_____/ | $$
 \____  $$| $$  \ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$| $$  |  $$$$$$  | $$
 /$$  \ $$| $$  | $$ /$$__  $$| $$_  $$ | $$_____/|  $$  \____  $$ /$$/
|  $$$$$$/| $$  | $$|  $$$$$$$| $$ \  $$|  $$$$$$$ \  $$$/$$$$$$$/$$$/ 
 \______/ |__/  |__/ \_______/|__/  \__/ \_______/  \___/_______/___/ 

 *************************************************************************
 * Snake(s) - Game by Sagiv Dvash
 * Version 0.1
 * Based on NVitanovic's tutorial (https://www.youtube.com/user/NVitanovic)
 * and using this answer at stack overflow http://stackoverflow.com/questions/34842526/update-console-without-flickering-c
 *
 * Known issues:
 * - *.h files should not include other .h files, but I don't know how to 
 *   avoid this currently
 * - I define the Fruit "newLoaction" method in the main cpp file instead
 *   of the SnakeGame.cpp file because I use the snakes variables. this 
 *   is ugly, but i can't think of a different way...
 *
 * Comments, suggestions, etc. are welcome at sagivdev@gmail.com
 *************************************************************************/

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#include "SnakeGame.h"
#include "BufferClass.h"
#include "ScreenClass.h"
using namespace std;

/************************************
*	Static variables				*
************************************/

Snake sk1, sk2;
Fruit fr;
Screen *hScreen;
bool gameOver = false;
int numOfPlayers = 1;
Buffer curBuffer, prevBuffer;
unsigned int speed = 200;

/************************************
*	Fruit method					*
************************************/

void Fruit::newLocation() {
	// Check that the new random location does not coinside with the snake(s)
	if (numOfPlayers == 1) {
		do {
			locX = rand() % (WIDTH - 2) + 1;
			locY = rand() % (HEIGHT - 2) + 1;
		} while (sk1.isHeadLoc(locX, locY) || sk1.isTailLoc(locX, locY));
	} else {
		// 2 players:
		do {
			locX = rand() % (WIDTH - 2) + 1;
			locY = rand() % (HEIGHT - 2) + 1;
		} while (sk1.isHeadLoc(locX, locY) || sk1.isTailLoc(locX, locY) ||
			sk2.isHeadLoc(locX, locY) || sk2.isTailLoc(locX, locY));
	}
}

/************************************
*	Auxilery functions				*
************************************/

void draw2Buffer_1p() {
	// Fill in new buffer
	prevBuffer = curBuffer;
	for (UINT i = 0; i < Buffer::width; i++) {
		curBuffer[i][0] = '#';
	}

	for (UINT i = 0; i < Buffer::width; i++) {
		for (UINT j = 1; j < Buffer::height - 1; j++) {
			if (i == 0 || i == Buffer::width - 1)
				curBuffer[i][j] = '#';
			else if (sk1.isHeadLoc(i, j))
				curBuffer[i][j] = 'O';
			else if (fr.isHere(i, j))
				curBuffer[i][j] = '*';
			else if (sk1.isTailLoc(i, j))
				curBuffer[i][j] = 'o';
			else
				curBuffer[i][j] = ' ';
		}
	}

	for (UINT i = 0; i < Buffer::width; i++) {
		curBuffer[i][Buffer::height - 1] = '#';
	}

	// Write to screen
	hScreen->updateScreen(curBuffer, prevBuffer);

	// Update score
	hScreen->updateScore(sk1.score);
}

void draw2Buffer_2p() {
	// Fill in new buffer
	prevBuffer = curBuffer;
	for (UINT i = 0; i < Buffer::width; i++) {
		curBuffer[i][0] = '#';
	}

	for (UINT i = 0; i < Buffer::width; i++) {
		for (UINT j = 1; j < Buffer::height - 1; j++) {
			if (i == 0 || i == Buffer::width - 1)
				curBuffer[i][j] = '#';
			else if (sk1.isHeadLoc(i, j))
				curBuffer[i][j] = 'O';
			else if (sk2.isHeadLoc(i, j))
				curBuffer[i][j] = 'X';
			else if (fr.isHere(i, j))
				curBuffer[i][j] = '*';
			else if (sk1.isTailLoc(i, j))
				curBuffer[i][j] = 'o';
			else if (sk2.isTailLoc(i, j))
				curBuffer[i][j] = 'x';
			else
				curBuffer[i][j] = ' ';
		}
	}

	for (UINT i = 0; i < Buffer::width; i++) {
		curBuffer[i][Buffer::height - 1] = '#';
	}

	// Write to screen
	hScreen->updateScreen(curBuffer, prevBuffer);

	// Update score
	hScreen->updateScore(sk1.score, sk2.score);
}

void input_1p() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (!(sk1.dir == DOWN && sk1.next))
				sk1.dir = UP;
			break;
		case 'a':
			if (!(sk1.dir == RIGHT && sk1.next))
				sk1.dir = LEFT;
			break;
		case 's':
			if (!(sk1.dir == UP && sk1.next))
				sk1.dir = DOWN;
			break;
		case 'd':
			if (!(sk1.dir == LEFT && sk1.next))
				sk1.dir = RIGHT;
			break;
		case 'q':
		case 'Q':
			gameOver = true;
			break;
		}
	}
}

void input_2p() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (!(sk1.dir == DOWN && sk1.next))
				sk1.dir = UP;
			break;
		case 'a':
			if (!(sk1.dir == RIGHT && sk1.next))
				sk1.dir = LEFT;
			break;
		case 's':
			if (!(sk1.dir == UP && sk1.next))
				sk1.dir = DOWN;
			break;
		case 'd':
			if (!(sk1.dir == LEFT && sk1.next))
				sk1.dir = RIGHT;
			break;
		case 'i':
			if (!(sk2.dir == DOWN && sk2.next))
				sk2.dir = UP;
			break;
		case 'j':
			if (!(sk2.dir == RIGHT && sk2.next))
				sk2.dir = LEFT;
			break;
		case 'k':
			if (!(sk2.dir == UP && sk2.next))
				sk2.dir = DOWN;
			break;
		case 'l':
			if (!(sk2.dir == LEFT && sk2.next))
				sk2.dir = RIGHT;
			break;
		case 'q':
		case 'Q':
			gameOver = true;
			break;
		}
	}
}

void logic_1p() {
	int tmp1X = sk1.headX, tmp1Y = sk1.headY;
	int tmp2X, tmp2Y;

	// Update head location
	switch (sk1.dir)
	{
	case UP:
		sk1.headY--;
		break;
	case LEFT:
		sk1.headX--;
		break;
	case DOWN:
		sk1.headY++;
		break;
	case RIGHT:
		sk1.headX++;
		break;
	}

	// Update tail location
	for (Segment *pnt = sk1.next; pnt; pnt = pnt->next) {
		tmp2X = pnt->locX;
		tmp2Y = pnt->locY;
		pnt->locX = tmp1X;
		pnt->locY = tmp1Y;
		tmp1X = tmp2X;
		tmp1Y = tmp2Y;
	}

	// Check boundry collision
	if (sk1.headX >= WIDTH - 1 || sk1.headX <= 0 ||
		sk1.headY >= HEIGHT - 1 || sk1.headY <= 0)
		gameOver = true;
	// Check self collision
	if (sk1.isTailLoc(sk1.headX, sk1.headY))
		gameOver = true;

	if (fr.isHere(sk1.headX, sk1.headY)) {
		sk1.score += 10;
		fr.newLocation();
		sk1.hasEaten();
	}
}

void logic_2p() {
	int tmp1X = sk1.headX, tmp1Y = sk1.headY;
	int tmp2X, tmp2Y;

	// Snake 1 - Update head & tail location
	switch (sk1.dir)
	{
	case UP:
		sk1.headY--;
		break;
	case LEFT:
		sk1.headX--;
		break;
	case DOWN:
		sk1.headY++;
		break;
	case RIGHT:
		sk1.headX++;
		break;
	}
	for (Segment *pnt = sk1.next; pnt; pnt = pnt->next) {
		tmp2X = pnt->locX;
		tmp2Y = pnt->locY;
		pnt->locX = tmp1X;
		pnt->locY = tmp1Y;
		tmp1X = tmp2X;
		tmp1Y = tmp2Y;
	}

	// Snake 2 - Update head & tail location
	tmp1X = sk2.headX;
	tmp1Y = sk2.headY;

	switch (sk2.dir)
	{
	case UP:
		sk2.headY--;
		break;
	case LEFT:
		sk2.headX--;
		break;
	case DOWN:
		sk2.headY++;
		break;
	case RIGHT:
		sk2.headX++;
		break;
	}

	for (Segment *pnt = sk2.next; pnt; pnt = pnt->next) {
		tmp2X = pnt->locX;
		tmp2Y = pnt->locY;
		pnt->locX = tmp1X;
		pnt->locY = tmp1Y;
		tmp1X = tmp2X;
		tmp1Y = tmp2Y;
	}

	// Check boundry collision
	if (sk1.headX >= WIDTH - 1 || sk1.headX <= 0 ||
		sk1.headY >= HEIGHT - 1 || sk1.headY <= 0)
		gameOver = true;
	if (sk2.headX >= WIDTH - 1 || sk2.headX <= 0 ||
		sk2.headY >= HEIGHT - 1 || sk2.headY <= 0)
		gameOver = true;

	// Check self collision
	if (sk1.isTailLoc(sk1.headX, sk1.headY))
		gameOver = true;
	if (sk2.isTailLoc(sk2.headX, sk2.headY))
		gameOver = true;

	// Check inter-collistions
	if (sk1.isTailLoc(sk2.headX, sk2.headY))
		gameOver = true;
	if (sk2.isTailLoc(sk1.headX, sk2.headY))
		gameOver = true;

	// Check for fruit-eating
	if (fr.isHere(sk1.headX, sk1.headY)) {
		sk1.score += 10;
		fr.newLocation();
		sk1.hasEaten();
	}
	if (fr.isHere(sk2.headX, sk2.headY)) {
		sk2.score += 10;
		fr.newLocation();
		sk2.hasEaten();
	}
}

/************************************
*	Main function					*
************************************/

int main() {
	srand(time(NULL));
	hScreen = new Screen;

	cout << "how many players ? (1-2)\n";
	cin >> numOfPlayers;
	if (numOfPlayers != 1 && numOfPlayers != 2)
		exit(1);

	if (numOfPlayers == 1) {
		while (!gameOver) {
			input_1p();
			logic_1p();
			draw2Buffer_1p();
			Sleep(speed);
		}
	} else {
		while (!gameOver) {
			input_2p();
			input_2p();
			logic_2p();
			draw2Buffer_2p();
			Sleep(150);
		}
	}

	delete hScreen;

	return 0;
}