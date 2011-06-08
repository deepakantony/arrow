
#include "Point.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Point& p)
{
  out << '[' << p.x() << ", " << p.y() << ", " << p.z() << ']';
  return out;
}
