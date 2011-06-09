
#ifndef BoundingBox_h
#define BoundingBox_h

#include "Point.h"

class BoundingBox {
 public:
  BoundingBox();
  ~BoundingBox();

  void reset();
  void extend(const Point&);

  Point getMin() const {
    return min;
  }
  Point getMax() const {
    return max;
  }
 private:
  Point min, max;
};

#endif
