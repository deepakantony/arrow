#ifndef RING_H_
#define RING_H_

#include "Primitive.h"
#include "Point.h"
#include "Vector.h"

class Ray;

class Ring : public Primitive {
 public:
  Ring(Material* material, const Point& center, const Vector& normal, const double innerRadius, const double outerRadius);
  virtual ~Ring();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	Point center;
	Vector n;
	double innerRadius, outerRadius;
};

#endif /*RING_H_*/
