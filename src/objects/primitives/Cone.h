#ifndef CONE_H_
#define CONE_H_

#include "Primitive.h"
#include "utils/Point.h"
#include "utils/Vector.h"

class Ray;

class Cone : public Primitive {
 public:
  Cone(Material* material, const Point& center, const Vector& normal, const double radius);
  virtual ~Cone();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	Point center;
	Vector n;
	double radius;
};

#endif /*CONE_H_*/
