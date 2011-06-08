
#include "Torus.h"
#include "../BoundingBox.h"
#include "rtengine/HitRecord.h"
#include "utils/Point.h"
#include "rtengine/Ray.h"
#include "utils/Vector.h"
#include <math.h>
#include <malloc.h>

Torus::Torus(Material* material, const Point& center, const Vector& normal, const double radius, const double tubeRadius)
:Primitive(material), center(center), n(normal), radius(radius), tubeRadius(tubeRadius)
{
}

Torus::Torus(Material* material, const double radius, const double tubeRadius)
:Primitive(material), radius(radius), tubeRadius(tubeRadius)
{
	// origin = (0,0,0)
	// normal = (0,1,0)
}

Torus::~Torus()
{
}

void Torus::getBounds(BoundingBox& bbox) const
{
}

void Torus::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	Vector rayDir = ray.direction();
	Point origin = ray.origin();
	double x1 = origin.x(); double y1 = origin.y(); double z1 = origin.z();
	double d1 = rayDir.x(); double d2 = rayDir.y(); double d3 = rayDir.z();	
	
	double coeffs[5]; // coefficient array for the quartic equation
	double roots[4]; // solution array for the quartic equation
	
	// define the coefficients of the quartic equation
	
	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - radius * radius - tubeRadius * tubeRadius;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double fourRadiusSqrd	= 4.0 * radius * radius;
	
	coeffs[0] = e * e - fourRadiusSqrd * (tubeRadius * tubeRadius - y1 * y1); // constant term
	coeffs[1] = 4.0 * f * e + 2.0 * fourRadiusSqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + fourRadiusSqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  // coefficient of t^4
	
	// find roots of the quartic equation
	
	int num_real_roots = solveQuartic(coeffs, roots);
	
	bool intersected = false;
	double t = 1.0e10;
	
	if (num_real_roots == 0)  // ray misses the torus
		return;
	
	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
	for (int j = 0; j < num_real_roots; j++)  
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}
		
	if(!intersected)
		return;
		
	hit.hit( t, this, matl);
}

void Torus::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	Point hitPos(hitpos);
	if(isInstanced) {
		hitPos = invTransMatrix * ray.origin() + (invTransMatrix * ray.direction()) * hit.minT();
	}
	double param_squared = radius * radius + tubeRadius * tubeRadius;

	double x = hitPos.x();
	double y = hitPos.y();
	double z = hitPos.z();
	double sum_squared = x * x + y * y + z * z;
	
	double nx = 4.0 * x * (sum_squared - param_squared);
	double ny = 4.0 * y * (sum_squared - param_squared + 2.0 * radius * radius);
	double nz = 4.0 * z * (sum_squared - param_squared);
	Vector n(nx, ny, nz);
	n.normalize();
	
	normal = n;
	/*
	double param_squared = radius * radius + tubeRadius * tubeRadius;

	double x = hitpos.x();
	double y = hitpos.y();
	double z = hitpos.z();
	double sum_squared = x * x + y * y + z * z;
	
	double nx = 4.0 * x * (sum_squared - param_squared);
	double ny = 4.0 * y * (sum_squared - param_squared + 2.0 * radius * radius);
	double nz = 4.0 * z * (sum_squared - param_squared);
	Vector n(nx, ny, nz);
	n.normalize();
	
	normal = n;
	*/
	if(isInstanced)  {
		normal = NormalMulMatrix(invTransMatrix, normal);
		normal.normalize();
	}
}
