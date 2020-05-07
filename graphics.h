#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "snake.h"
#include "food.h"

#define BORDER_SIDE 5
#define SQUARE_SIDE 5
#define DISPLACEMENT 10
#define BORDER_SPACE 2
#define SNAKE_SPACE 1

void backgroundColor();

void borderColor();

void snaqueColor();

void foodColor();

void printBackground();

void printBorder(int width, int height);

void printRectangle(int x, int y, int width, int height);

void printSnake(int offset, struct snake* snake);

// print snake segment
void printSegment(int direction, int x, int y, int size);

void printSquare(int offset, struct point* p);

void printFood(int offset, struct food* f);

void reshapeSnake();

#endif
