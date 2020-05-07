#ifndef POINT_H_
#define POINT_H_

// first x is 0
// first y is 0
struct point {
  int x;
  int y;
};

int equals(struct point* p1, struct point* p2);

#endif
