
#ifndef Primitive_h
#define Primitive_h

#include "Object.h"
#include "Vector.h"
class Material;
class Point;

class Primitive : public Object {
 public:
  Primitive(Material* matl);
  virtual ~Primitive();

  virtual void preprocess();
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const = 0;
  void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;

  virtual void computeUVW(Vector& uvw, const RenderContext& context,
                          const Ray& ray, const HitRecord& hit) const;
	
 protected:
  Material* matl;
	double kEpsilon;
	mutable Vector n;


 private:
  Primitive(const Primitive&);
  Primitive& operator=(const Primitive&);
};


#endif

