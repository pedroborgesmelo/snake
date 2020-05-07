#ifndef SNAKE_H_
#define SNAKE_H_

#include "point.h"
#include "food.h"

// is the directions of segments
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

// the function do the integer division food->energy by MOD
// and the result is the amount the snake will grow
#define MOD 20

// is a part of snake
struct segment {
  int direction;
  int size;
};

struct segmentNode {
  struct segment s;
  struct segmentNode* left;
  struct segmentNode* right;
};

struct snakeQueue {
  struct segmentNode* first;
  struct segmentNode* last;
};

struct snake {
  // reference point
  struct point ref;
  // the set of parts
  // it must be a queue because the changes is in first and last part
  // and with a queue the operations of get first and last is O(1)
  struct snakeQueue list;
};

void incrementLastSegment(struct snake* snake);

void initSnake(struct snake* snake, int x, int y);

void subLastSegment(struct snake* snake);

void addFirstSegment(struct snake* snake, int direction);

// this function calculate the new point after movement
void fixReferencePoint(int refx, int refy, int* newx, int* newy, int direction);

void insertNewSegmentAtFront(struct snake* snake, int direction);

void deleteSnake(struct snake* snake);

#endif
