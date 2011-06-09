
#include "disk.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>
#include <malloc.h>

Disk::Disk(Material* material, const Point& center, const Vector& normal, const double radius)
:Primitive(material), center(center), n(normal), radius(radius)
{
	n.normalize();
}

Disk::~Disk()
{
}

void Disk::getBounds(BoundingBox& bbox) const
{
}

void Disk::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	//float denom = Dot(ray.direction() , n);
	double t = Dot((center - ray.origin()), n )/Dot(ray.direction(), n);
	
	Point p = ray.origin() + t * ray.direction();
	
	if( t > 0.0) {
		//float t = Dot((center - ray.origin()), n )/denom;
		//Point p = ray.origin() + t * ray.direction();
		if( p.distanceSquared(center) < (radius*radius))
			hit.hit(t, this, matl);
	}
	
}

void Disk::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	normal = this->n;
}
