

#include "PhongImageMaterial.h"
#include "rtengine/HitRecord.h"
#include "lights/Light.h"
#include "utils/Point.h"
#include "objects/primitives/Primitive.h"
#include "rtengine/Ray.h"
#include "rtengine/RenderContext.h"
#include "rtengine/Scene.h"
#include "utils/Vector.h"
#include "utils/Math.h"
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
