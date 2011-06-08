
#include "Color.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Color& c)
{
  out << '[' << c.r() << ", " << c.g() << ", " << c.b() << ']';
  return out;
}

