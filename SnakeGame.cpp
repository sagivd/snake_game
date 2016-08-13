/* Snake classes cpp file */

#include <iostream>
#include "SnakeGame.h"
#include "BufferClass.h"


Snake::Snake() {
	headX = (unsigned int)rand() % (Buffer::width - 2) + 1;
	headY = (unsigned int)rand() % (Buffer::height - 2) + 1;
	next = NULL;
	curDir = STOP;
}

Snake::~Snake() {
	Segment *pnt1, *pnt2;
	for (pnt1 = this->next; pnt1; pnt1 = pnt2) {
		pnt2 = pnt1->next;
		delete pnt1;
	}
}

bool Snake::isTailLoc(unsigned int x, unsigned int y) {
	bool rc = false;
	for (Segment *pnt = next; pnt; pnt = pnt->next) {
		if (pnt->locX == x && pnt->locY == y) {
			rc = true;
			break;
		}
	}
	return rc;
}

void Snake::hasEaten() {
	Segment *temp = new Segment;
	if (!temp)
		exit(1);

	temp->next = next;
	temp->locX = headX;
	temp->locY = headY;
	next = temp;
}
