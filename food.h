#ifndef FOOD_H_
#define FOOD_H_

#include "point.h"

#define MAX_ENERGY 50

struct food {
	int energy;
	struct point p;
};

void initFood(struct food* f, int x, int y);

#endif
