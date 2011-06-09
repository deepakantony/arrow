#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Primitive.h"
#include "Point.h"

class Ray;

class Triangle : public Primitive {
 public:
  Triangle(Material* material, const Point& corner1, const Point& corner2, const Point& corner3);
  virtual ~Triangle();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
protected:
	double corner1[3];
	double corner2[3];
	double corner3[3];
	Point a, b, c;
	Vector n;
};

#endif /*TRIANGLE_H_*/
