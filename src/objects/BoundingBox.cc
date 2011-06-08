
#include "BoundingBox.h"
#include <float.h>

BoundingBox::BoundingBox()
{
  min = Point(DBL_MAX, DBL_MAX, DBL_MAX);
  max = Point(-DBL_MAX, -DBL_MAX, -DBL_MAX);
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::extend(const Point& p)
{
  min = Min(p, min);
  max = Max(p, max);
}
