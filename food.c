#include "food.h"
#include <time.h>
#include <stdlib.h>

void initFood(struct food* f, int x, int y) {
	/* initialize random seed: */
	srand(time(NULL));
	f->energy = (rand() % MAX_ENERGY) + 1;
	f->p.x = x;
	f->p.y = y;
}
