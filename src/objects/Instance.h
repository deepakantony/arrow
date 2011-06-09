

#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "Object.h"
#include "Matrix.h"
#include "Point.h"
#include "Vector.h"

class Instance: public Object 
{
public:
	Instance();
	Instance(Object *obj);
	~Instance();
		
	virtual void getBounds(BoundingBox& bbox) const;
	virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
	
	void setObject(Object *obj);
	
	// affine transformation functions
	void translate(const Vector& trans);
	void translate(const double dx, const double dy, const double dz);
	void scale(const Vector& s);
	void scale(const double a, const double b, const double c);
	void rotateX(const double r);
	void rotateY(const double r);
	void rotateZ(const double r);
	void shear(const Matrix& m);

protected:
	Object* obj;
	Matrix transMatrix;
	Matrix invTransMatrix;

private:

};

#endif // _INSTANCE_H_
