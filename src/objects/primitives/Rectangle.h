#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Primitive.h"
#include "Point.h"
#include "Vector.h"

class Ray;

class Rectangle : public Primitive {
 public:
  Rectangle(Material* material, const Point& p, const Vector& a, const Vector& b);
  Rectangle(Material* material, const Point& p, const Point& pa, const Point& pb);
  virtual ~Rectangle();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	Point p;
	Vector n;
	Vector a, b; // the side vectors from point p
	double aLenSqrd, bLenSqrd;
};

#endif /*RECTANGLE_H_*/
