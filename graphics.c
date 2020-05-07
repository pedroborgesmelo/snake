#include "graphics.h"
#include <GL/gl.h>
#include <stdlib.h>

#include <stdio.h>

void backgroundColor() {
	glClearColor(0, 0, 0, 1);
	glColor3f(0, 0, 0);
}

void borderColor() {
	glColor3f(0, 0, 1);
}

void snaqueColor() {
	glColor3f(0, 1, 0);
}

void foodColor() {
 	glColor3f(1, 0, 0);
}

void printBackground() {
	backgroundColor();
	glClear(GL_COLOR_BUFFER_BIT);
}

void printRectangle(int x, int y, int width, int height) {
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();
}

void printBorder(int width, int height) {
	// setting
	borderColor();
	// printing border
	printRectangle(DISPLACEMENT, DISPLACEMENT, BORDER_SIDE, height - 2*DISPLACEMENT);
	printRectangle(DISPLACEMENT, height - DISPLACEMENT - BORDER_SIDE + SNAKE_SPACE, width - 2*DISPLACEMENT, BORDER_SIDE);
	printRectangle(DISPLACEMENT, DISPLACEMENT, width - 2*DISPLACEMENT, BORDER_SIDE);
	printRectangle(
		width - DISPLACEMENT - BORDER_SIDE + 2*SNAKE_SPACE, 
		DISPLACEMENT, 
		BORDER_SIDE, 
		height - 2*DISPLACEMENT + SNAKE_SPACE);
}

void printSnake(int offset, struct snake* snake) {
	snaqueColor();
	struct segment* s;
	int x = snake->ref.x;
	int y = snake->ref.y;
	struct segmentNode* node = snake->list.first;
	while(node != NULL) {
		s = &(node->s);
		printSegment(s->direction, x, y, s->size);
		// calculate new point 1
		if(s->direction == NORTH) y -= s->size;
		else if(s->direction == SOUTH) y += s->size;
		else if(s->direction == WEST) x += s->size;
		else x -= s->size;
		// next segment
		node = node->right;
	}
}

void printSegment(int direction, int x, int y, int size) {
	int xsignal, ysignal, xcord, ycord, OFFSET;
	OFFSET = DISPLACEMENT + BORDER_SIDE + BORDER_SPACE;
	// processing signal
	if(direction == SOUTH) {
		xsignal = 0; ysignal = +1;
	} else if(direction == NORTH) {
		xsignal = 0; ysignal = -1;
	} else if(direction == WEST) {
		xsignal = 1; ysignal = 0;
	} else { // direction == EAST
		xsignal = -1; ysignal = 0;
	}
	// calculate pixel position
	while(size > 0) {
		// calculate position
		xcord = OFFSET + (x*(SQUARE_SIDE + SNAKE_SPACE));
		ycord = OFFSET + (y*(SQUARE_SIDE + SNAKE_SPACE));
		// draw square
		printRectangle(xcord, ycord, SQUARE_SIDE, SQUARE_SIDE);
		// calculate new (x,y)
		x += xsignal;
		y += ysignal;
		--size;
	}
}

void printSquare(int offset, struct point* p) {
	int x = offset + (p->x * (SQUARE_SIDE + SNAKE_SPACE));
	int y = offset + (p->y * (SQUARE_SIDE + SNAKE_SPACE));
	printRectangle(x, y, SQUARE_SIDE, SQUARE_SIDE);
}

void printFood(int offset, struct food* f) {
	foodColor();
	printSquare(offset, &(f->p));
}
