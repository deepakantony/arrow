#ifndef BOX_H_
#define BOX_H_

#include "Primitive.h"
#include "utils/Point.h"

class Ray;

class Box : public Primitive {
 public:
  Box(Material* material, const Point& corner1, const Point& corner2);
  virtual ~Box();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
	void updateFacehit(int face);
protected:
	double corner1[3];
	double corner2[3];
	int faceHit; // used to find the normal
};

#endif /*BOX_H_*/
