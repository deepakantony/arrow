
#include "Cone.h"
#include "../BoundingBox.h"
#include "rtengine/HitRecord.h"
#include "utils/Point.h"
#include "rtengine/Ray.h"
#include "utils/Vector.h"
#include <math.h>
#include <malloc.h>

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
