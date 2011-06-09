
#include "Material.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Ray.h"

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

