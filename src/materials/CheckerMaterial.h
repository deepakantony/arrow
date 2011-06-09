
#ifndef _CHECKERMATERIAL_H_
#define _CHECKERMATERIAL_H_

#include "Material.h"
#include "Vector.h"

class CheckerMaterial: public Material 
{
public:
	CheckerMaterial(const Point& origin, const Vector& vector1, const Vector& vector2, const double scale, Material *matl1, Material*matl2);
	
	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;
	
	virtual bool castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const;

protected:

private:
	Point origin;
	Vector vector1, vector2;
	double scale;
	Material *matl1, *matl2;
};

#endif // _CHECKERMATERIAL_H_
