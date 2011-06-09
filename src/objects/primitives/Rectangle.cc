
#include "Rectangle.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>
#include <malloc.h>

Rectangle::Rectangle(Material* material, const Point& p, const Vector& a, const Vector& b)
:Primitive(material), p(p), a(a), b(b)
{
	n = Cross( a, b );
	n.normalize();
	aLenSqrd = Dot(a, a);
	bLenSqrd = Dot(b, b);
}

Rectangle::Rectangle(Material* material, const Point& p, const Point& pa, const Point& pb)
:Primitive(material), p(p), a(pa-p), b(pb-p)
{
	n = Cross( a, b );
	n.normalize();
	aLenSqrd = Dot(a, a);
	bLenSqrd = Dot(b, b);
}

Rectangle::~Rectangle()
{
}

void Rectangle::getBounds(BoundingBox& bbox) const
{
}

void Rectangle::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	double t = Dot((this->p - ray.origin()), n )/Dot(ray.direction(), n);
	
	if( t < 0) return;
	
	Point p = ray.origin() + t * ray.direction();
	Vector d = p - this->p;
	
	double ddota = Dot(d, a);
	
	if( ddota < 0 || ddota > aLenSqrd ) return;
	
	double ddotb = Dot(d, b);
	if( ddotb < 0 || ddotb > bLenSqrd ) return;
	
	hit.hit(t, this, matl);
}

void Rectangle::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	normal = n;
}
