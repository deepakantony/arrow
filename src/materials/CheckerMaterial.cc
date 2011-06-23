
#include "CheckerMaterial.h"
#include "mathutil.h"
#include "HitRecord.h"
#include "Ray.h"
#include "Primitive.h"
#include <iostream>

using namespace std;

CheckerMaterial::CheckerMaterial(const Point& origin, const Vector& vector1, const Vector& vector2, const double scale, Material *matl1, Material*matl2)
:origin(origin), vector1(vector1), vector2(vector2), scale(scale), matl1(matl1), matl2(matl2)
{
	this->vector1 = vector1/Dot(vector1,vector1);
	this->vector2 = vector2/Dot(vector2,vector2);
}
	
void CheckerMaterial::shade(Color& result, const RenderContext& context, const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw,context,ray,hit);
	
	int i1 = (int)Floor(Dot(uvw,vector1)/scale);
	int i2 = (int)Floor(Dot(uvw,vector2)/scale);
	if((i1+i2) % 2 == 0)
		matl1->shade(result, context, ray, hit, atten, depth);
	else 
		matl2->shade(result, context, ray, hit, atten, depth);
}

bool CheckerMaterial::castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw,context,ray,hit);
	
	int i1 = (int)Floor(Dot(uvw,vector1)/scale);
	int i2 = (int)Floor(Dot(uvw,vector2)/scale);
	if((i1+i2) % 2 == 0) {
		return matl1->castShadows(context, hit, ray);
	}
	else {
		return matl2->castShadows(context, hit, ray);
	}
}
