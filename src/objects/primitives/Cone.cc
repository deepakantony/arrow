
#include "Cone.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>
#ifdef __APPLE__
#include <cstdlib>
#else
#include <malloc.h>
#endif

Cone::Cone(Material* material, const Point& center, const Vector& normal, const double radius)
:Primitive(material), center(center), n(normal), radius(radius)
{
}

Cone::~Cone()
{
}

void Cone::getBounds(BoundingBox& bbox) const
{
}

void Cone::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	
}

void Cone::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
}
