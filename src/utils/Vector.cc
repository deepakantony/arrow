
#include "Vector.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
  out << '[' << v.x() << ", " << v.y() << ", " << v.z() << ']';
  return out;
}

