#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

void initSnake(struct snake* snake, int x, int y) {
	// put reference point
	snake->ref.x = x;
	snake->ref.y = y;
	// build the queue
	snake->list.first = malloc(sizeof(struct segmentNode));
	struct segmentNode* first = snake->list.first;
	// put information in segment
	first->s.direction = SOUTH;
	first->s.size = 33;
	// assert pointers to other elements
	first->left = NULL;
	first->right = NULL;
	// build queue
	snake->list.last = first;
}

void incrementLastSegment(struct snake* snake) {
	++(snake->list.last->s.size);
}

void subLastSegment(struct snake* snake) {
	--(snake->list.last->s.size);
	// if size of last segment is 0 remove last segment
	if(snake->list.last->s.size == 0) {
		struct segmentNode* newLast = snake->list.last->left;
		newLast->right = NULL;
		free(snake->list.last);
		snake->list.last = newLast;
	}
}

void addFirstSegment(struct snake* snake, int direction) {
	// if the direction is the same
	if(snake->list.first->s.direction == direction) {
		++(snake->list.first->s.size);
	} else {
		// then i have insert new segment at front with size 1
		insertNewSegmentAtFront(snake, direction);
	}
}

void fixReferencePoint(int refx, int refy, int* newx, int* newy, int direction) {
	*newy = refy;
	*newx = refx;
	if(direction == NORTH) *newy = refy + 1;
	else if(direction == SOUTH) *newy = refy - 1;
	else if(direction == EAST) *newx = refx + 1;
	else *newx = refx - 1;
}

void insertNewSegmentAtFront(struct snake* snake, int direction) {
	struct segmentNode* node = malloc(sizeof(struct segmentNode));
	node->s.direction = direction;
	node->s.size = 1;
	node->left = NULL;
	node->right = snake->list.first;
	snake->list.first->left = node;
	snake->list.first = node;
}

void deleteSnake(struct snake* snake) {

}
