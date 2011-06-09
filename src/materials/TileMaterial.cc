
#include "TileMaterial.h"
#include "Math.h"
#include "HitRecord.h"
#include "Ray.h"
#include "Primitive.h"

TileMaterial::TileMaterial(const Vector& vector1, const Vector& vector2, const double scale, const double groutWidth, Material *matlTile, Material*matlGrout)
:vector1(vector1), vector2(vector2), scale(scale), groutWidth(groutWidth), matlTile(matlTile), matlGrout(matlGrout)
{
	this->vector1 = vector1/Dot(vector1,vector1);
	this->vector2 = vector2/Dot(vector2,vector2);
}
	
void TileMaterial::shade(Color& result, const RenderContext& context, const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw,context,ray,hit);
	
	double i1 = Dot(uvw,vector1)/scale;
	double i2 = Dot(uvw,vector2)/scale;
	
	double s = i1 - (int)(i1);
	double t = i2 - (int)(i2);
	if(s < 0.0 ) s = 1.0 + s;
	if(t < 0.0 ) t = 1.0 + t;
	
	if(s < groutWidth || t < groutWidth)
		matlGrout->shade(result, context, ray, hit, atten, depth);
	else
		matlTile->shade(result, context, ray, hit, atten, depth);
}

bool TileMaterial::castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw,context,ray,hit);
	
	double i1 = Dot(uvw,vector1)/scale;
	double i2 = Dot(uvw,vector2)/scale;
	
	double s = i1 - (int)(i1);
	double t = i2 - (int)(i2);
	if(s < 0.0 ) s = 1.0 + s;
	if(t < 0.0 ) t = 1.0 + t;
	
	if(s < groutWidth || t < groutWidth)
		return matlGrout->castShadows(context, hit, ray);
	else
		return matlTile->castShadows(context, hit, ray);
}
