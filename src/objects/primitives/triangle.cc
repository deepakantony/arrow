
#include "triangle.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>
#include <malloc.h>

Triangle::Triangle(Material* material, const Point& corner1, const Point& corner2, const Point& corner3)
:Primitive(material), a(corner1), b(corner2), c(corner3)
{
	this->corner1[0] = corner1.x();
	this->corner1[1] = corner1.y();
	this->corner1[2] = corner1.z();
	this->corner2[0] = corner2.x();
	this->corner2[1] = corner2.y();
	this->corner2[2] = corner2.z();
	this->corner3[0] = corner3.x();
	this->corner3[1] = corner3.y();
	this->corner3[2] = corner3.z();
	
	n = Cross(b-a, c-a);
	n.normalize();
}

Triangle::~Triangle()
{
}

void Triangle::getBounds(BoundingBox& bbox) const
{
}

void Triangle::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	double a, b, c, d, e, f, g, h, i, j, k, l;
	
	a = corner1[0] - corner2[0]; 
		b = corner1[0] - corner3[0];
			c = ray.direction().x();
				d = corner1[0] - ray.origin().x();
				
	e = corner1[1] - corner2[1]; 
		f = corner1[1] - corner3[1];
			g = ray.direction().y();
				h = corner1[1] - ray.origin().y();
				
	i = corner1[2] - corner2[2]; 
		j = corner1[2] - corner3[2];
			k = ray.direction().z();
				l = corner1[2] - ray.origin().z();
				
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double invDenom = 1.0/(a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;
	
	// if beta is not within the range 0 to 1 no hit!
	if( beta < 0.0 ) return;
	
	double r = e * l - h * i;
	double e2 = a*n + d*q + c*r;
	double gamma = e2 * invDenom;
	
	// if gamma is not within the range 0 to 1 then no hit!
	if( gamma < 0.0 ) return;
	
	// if alpha not within 0 to 1 then no hit!
	if( (beta + gamma) > 1.0) return;
	
	double e3 = a * p - b*r + d*s;
	double t = e3 * invDenom;
	
	// if t is beyond origin then no hit too..
	if( t < kEpsilon) return;
	
	hit.hit(t, this, matl);
}

void Triangle::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	normal = n;
}
