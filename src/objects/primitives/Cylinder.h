#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Primitive.h"
#include "Point.h"
#include "Vector.h"

class Ray;

class Cylinder : public Primitive {
 public:
  Cylinder(Material* material, const Point& center, const double height, const double radius);
  virtual ~Cylinder();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	Point center;
	double top, bottom, radius, invRadius, rSqrd;
};

#endif /*CYLINDER_H_*/
