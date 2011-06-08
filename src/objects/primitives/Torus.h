#ifndef TORUS_H_
#define TORUS_H_

#include "Primitive.h"
#include "utils/Point.h"
#include "utils/Vector.h"

class Ray;

class Torus : public Primitive {
 public:
  Torus(Material* material, const Point& center, const Vector& normal, const double radius, const double innerRadius);
  Torus(Material* material, const double radius, const double tubeRadius);
  virtual ~Torus();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	Point center;
	Vector n;
	double radius, tubeRadius;
};

#endif /*TORUS_H_*/
