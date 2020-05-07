#include "field.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void initField(struct field* field, int width, int height, int offset, int slice) {
	// def bounds
	field->maxRow = (height - offset) / slice;
	field->maxCol = (width - offset) / slice;
	// init snake
	initSnake(&(field->s), 0, field->maxRow/2);
	putFood(field);
}

int crash(struct field* f) {
	struct snake* snake = &(f->s);
	struct segment* s;
	int refx, x, xmax, xmin;
	int refy, y, ymax, ymin;
	refy = y = snake->ref.y;
	refx = x = snake->ref.x;
	struct segmentNode* node = snake->list.first;
	while(node != NULL) {
		s = &(node->s);
		// gera o bound
		if(s->direction == SOUTH) {
			xmin = xmax = x;
			ymin = y;
			ymax = y + s->size;
		} else if(s->direction == NORTH) {
			xmin = xmax = x;
			ymax = y;
			ymin = y - s->size;
		} else if(s->direction == WEST) {
			ymin = ymax = y;
			xmin = x;
			xmax = x + s->size;
		} else { // direction == EAST
			ymin = ymax = y;
			xmax = x;
			xmin = x - s->size;
		}
		// verifica se o ref está no intervalo do corpo do snake
		if(refx >= xmin && refx <= xmax && refy >= ymin && refy <= ymax
			&& node != snake->list.first) return 1;
		// calculate new point
		if(s->direction == NORTH) y -= s->size;
		else if(s->direction == SOUTH) y += s->size;
		else if(s->direction == WEST) x += s->size;
		else x -= s->size;
		// next segment
		node = node->right;
	}
	return 0;
}

void putFood(struct field* f) {
	struct point p;
	getRandomPoint(f, &p);
	initFood(&(f->food), p.x, p.y);
}

void getRandomPoint(struct field* field, struct point* p) {
	srand(time(NULL));
	p->x = rand() % field->maxCol;
	p->y = rand() % field->maxRow;
}

int isValidMovement(struct field* field, int x, int y) {
	return x >= 0 && x <= field->maxCol && y >= 0 && y <= field->maxRow;
}

int mov(struct field* field, int direction) {
	struct snake* s = &(field->s);
	int newx, newy;
	// verify bouds of movement
	fixReferencePoint(s->ref.x, s->ref.y, &newx, &newy, direction);
	if(isValidMovement(field, newx, newy) != 1) return 0;
	// mov
	s->ref.x = newx;
	s->ref.y = newy;
	subLastSegment(s);
	addFirstSegment(s, direction);
	// return normal status
	return 1;
}

int snakeLeft(struct field* field) {
	return mov(field, EAST);
}

int snakeRight(struct field* field) {
	return mov(field, WEST);
}

int snakeUp(struct field* field) {
	return mov(field, NORTH);
}

int snakeDown(struct field* field) {
	return mov(field, SOUTH);
}
