#ifndef FIELD_H_
#define FIELD_H_

#include "snake.h"

struct field {
	// invalid value
	int maxRow;
	// invalid value
	int maxCol;
	struct snake s;
	struct food food;
};

int crash(struct field* f);

void putFood(struct field* f);

void initField(struct field* field, int width, int height, int offset, int slice);

int isValidMovement(struct field* field, int x, int y);

int mov(struct field* field, int direction);

int snakeLeft(struct field* field);

int snakeRight(struct field* field);

int snakeUp(struct field* field);

int snakeDown(struct field* field);

void getRandomPoint(struct field* field, struct point* p);

#endif
