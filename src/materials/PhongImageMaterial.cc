

#include "PhongImageMaterial.h"
#include "HitRecord.h"
#include "Light.h"
#include "Point.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include "mathutil.h"
#include <iostream>


PhongImageMaterial::PhongImageMaterial(const string file, float Kd, float Ka, const Color& sHighlight, float exponent)
  :PhongMaterial(Color(1.0,1.0,1.0), Kd, Ka, sHighlight, exponent)
{
	image = new Image(file);
}

PhongImageMaterial::~PhongImageMaterial()
{
}

void PhongImageMaterial::shade(Color& result, const RenderContext& context,
                               const Ray& ray, const HitRecord& hit, const Color& atten, int depth) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw, context, ray, hit);
	PhongMaterial::color = image->interpolate(uvw.x(), uvw.y());
	PhongMaterial::shade(result, context, ray, hit, atten, depth);
}
