
#ifndef Ray_h
#define Ray_h

#include "utils/Point.h"
#include "utils/Vector.h"

class Ray {
 public:
  Ray() {
  }
  Ray(const Point& origin, const Vector& direction)
    : org(origin), dir(direction) {
  }
    
  ~Ray() {
  }
  Ray(const Ray& copy)
    : org(copy.org), dir(copy.dir) {
  }
  Ray& operator=(const Ray& copy) {
    org = copy.org;
    dir = copy.dir;
    return *this;
  }

  const Point& origin() const {
    return org;
  }
  const Vector& direction() const {
    return dir;
  }
	void setOrigin(const Point& pt) const{
		org = pt;
	}
	void setDir(const Vector& vec) const{
		dir = vec;
	}
 private:
   mutable Point org;
   mutable Vector dir;
};

#endif
