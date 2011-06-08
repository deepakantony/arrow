
#include "Material.h"
#include "rtengine/RenderContext.h"
#include "rtengine/HitRecord.h"
#include "rtengine/Ray.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::preprocess()
{
}

bool Material::castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const
{
	return true;
}

