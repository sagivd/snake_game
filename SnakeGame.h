/* Snake game h file */

#ifndef __SNAKE_GAME_H
#define __SNAKE_GAME_H

enum direction { STOP = 0, UP, LEFT, DOWN, RIGHT };

class Segment {
public:
	Segment *next;
	int locX, locY;
};

class Snake {
public:
	unsigned int headX, headY;
	unsigned int score;
	direction curDir, nextDir;

	Segment *next;

	Snake();
	~Snake();

	inline bool Snake::isHeadLoc(unsigned int x, unsigned int y) {
		return (headX == x && headY == y);
	}
	bool isTailLoc(unsigned int, unsigned int);
	void hasEaten();
};

class Fruit {
public:
	unsigned int locX, locY;

	Fruit() { this->newLocation(); };
	void newLocation(); // defined in SnakeGameMain, since it uses the
						// (global) snake objects.

	inline bool isHere(unsigned int x, unsigned int y) {
		return (locX == x && locY == y);
	}
};

#endif __SNAKE_GAME_H
