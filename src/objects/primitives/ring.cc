
#include "ring.h"
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

Ring::Ring(Material* material, const Point& center, const Vector& normal, 
	const double innerRadius, const double outerRadius)
:Primitive(material), center(center), n(normal), innerRadius(innerRadius), outerRadius(outerRadius)
{
	n.normalize();
}

Ring::~Ring()
{
}

void Ring::getBounds(BoundingBox& bbox) const
{
}

void Ring::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	double t = Dot((center - ray.origin()), n )/Dot(ray.direction(), n);
	
	Point p = ray.origin() + t * ray.direction();
	
	if( t > 0.0) {
		if( p.distanceSquared(center) < (outerRadius*outerRadius)
			&& p.distanceSquared(center) >  (innerRadius*innerRadius))
			hit.hit(t, this, matl);
	}
}

void Ring::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	normal = this->n;
}
