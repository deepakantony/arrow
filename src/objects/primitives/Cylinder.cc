
#include "Cylinder.h"
#include "../BoundingBox.h"
#include "rtengine/HitRecord.h"
#include "utils/Point.h"
#include "rtengine/Ray.h"
#include "utils/Vector.h"
#include <math.h>
#include <malloc.h>

Cylinder::Cylinder(Material* material, const Point& center, const double height, const double radius)
:Primitive(material), center(center), top(height+center.y()), bottom(center.y()), radius(radius)
{
	invRadius = 1.0/radius;
	rSqrd = radius*radius;
}

Cylinder::~Cylinder()
{
}

void Cylinder::getBounds(BoundingBox& bbox) const
{
}

void Cylinder::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
	Vector rayDir = ray.direction();
	Point origin = ray.origin();
	if(isInstanced) {
		//rayDir = invTransMatrix * rayDir;
		//origin = invTransMatrix * origin;
		//ray.setOrigin(origin);
		//ray.setDir(rayDir);
	}
	double dx = rayDir.x(), dy = rayDir.y(), dz = rayDir.z();
	double ox = origin.x(), oy = origin.y(), oz = origin.z(); 
	double a =  dx*dx + dz*dz;
	double b = 2*( ox*dx + oz*dz);
	double c = ox*ox + oz*oz - rSqrd;
	
	double disc = b * b - 4 * a * c;
	
	if(disc >= 0) {
		double denom = 1/(2*a);
		double sqrtDisc = sqrt(disc);
		double root1 = (-b-sqrtDisc)*denom;
		double py = oy + root1 * dy;
		bool success = false;
		if(py <= top && py >= bottom )
			success = hit.hit(root1, this, matl);
		
		if(!success) {
			double root2 = (-b+sqrtDisc)*denom;
			double py = oy + root2 * dy;
			if(py <= top && py >= bottom)
				hit.hit(root2, this, matl);
		}
	}
}

void Cylinder::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
	Point hitPos(hitpos);
	if(isInstanced) 
		hitPos = invTransMatrix * ray.origin() + (invTransMatrix * ray.direction()) * hit.minT();
	normal = Vector( hitPos.x()*invRadius,0.0, hitPos.z()*invRadius); 
	if(isInstanced)  {
		
		normal = NormalMulMatrix(invTransMatrix, normal);
	}
	normal.normalize();
}
