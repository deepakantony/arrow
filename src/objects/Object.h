
#ifndef Object_h
#define Object_h

class BoundingBox;
class Color;
class HitRecord;
class Ray;
class RenderContext;

#include "utils/Matrix.h"

class Object {
 public:
  Object();
  virtual ~Object();

  virtual void preprocess();
  virtual void getBounds(BoundingBox& bbox) const = 0;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const = 0;
	
	void setInstance(const bool isInstanced);
	void setInvTransMatrix(const Matrix invTransMatrix);
	void setTransMatrix(const Matrix transMatrix);

	
protected:
	bool isInstanced;
	Matrix invTransMatrix;
	Matrix transMatrix;

 private:
  Object(const Object&);
  Object& operator=(const Object&);
};

#endif

