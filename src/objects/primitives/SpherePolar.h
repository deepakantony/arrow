
#ifndef _SPHEREPOLAR_H_
#define _SPHEREPOLAR_H_

#include "Sphere.h"

class SpherePolar: public Sphere 
{
public:
public:
	SpherePolar(Material* material, const Point& center, double radius, const Vector& pole, const Vector& meridian);
	virtual ~SpherePolar();
	
	void computeUVW(Vector& uvw, const RenderContext& context,
                           const Ray& ray, const HitRecord& hit) const;

protected:
	Vector pole, meridian;
};

#endif // _SPHEREPOLAR_H_
