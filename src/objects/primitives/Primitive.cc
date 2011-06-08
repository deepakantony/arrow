
#include "Primitive.h"
#include "rtengine/HitRecord.h"
#include "materials/Material.h"
#include "rtengine/Ray.h"
#include "utils/Vector.h"

Primitive::Primitive(Material* matl)
  : matl(matl)
{
	kEpsilon = 1.e-6;
}

Primitive::~Primitive()
{
	kEpsilon = 1.e-6;
}

void Primitive::preprocess()
{
  matl->preprocess();
}

void Primitive::computeUVW(Vector& uvw, const RenderContext& context,
                           const Ray& ray, const HitRecord& hit) const
{
  Point hitpos = ray.origin()+ray.direction()*hit.minT();
  uvw = Vector(hitpos);
}

void Primitive::normal(Vector& normal, const RenderContext& context, const Point& hitpos, const Ray& ray, const HitRecord& hit) const
{
	normal = this->n;
}

