
#include "InvisibleMaterial.h"
#include "utils/Vector.h"
#include "utils/Point.h"
#include "rtengine/Ray.h"
#include "rtengine/HitRecord.h"
#include "rtengine/Scene.h"
#include "rtengine/RenderContext.h"

InvisibleMaterial::InvisibleMaterial()
{
}

void InvisibleMaterial::shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const
{
	Vector rayDir = ray.direction();
	Point hitpos = ray.origin() + hit.minT() * rayDir;
	const Scene* scene = context.getScene();
	Ray newRay(hitpos, rayDir);
	scene->traceRay(result, context, newRay, atten, depth);
}

bool InvisibleMaterial::castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const
{
	return false;
}
