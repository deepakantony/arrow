

#include "SpherePolar.h"
#include "../BoundingBox.h"
#include "rtengine/HitRecord.h"
#include "utils/Point.h"
#include "rtengine/Ray.h"
#include "utils/Vector.h"
#include "utils/Math.h"
#include "mapping/SphericalMapping.h"
#include <math.h>

SpherePolar::SpherePolar(Material* material, const Point& center, double radius, const Vector& pole, const Vector& meridian)
  : Sphere(material, center, radius), pole(pole), meridian(meridian)
{
	this->pole.normalize();
	this->meridian.normalize();
}

SpherePolar::~SpherePolar()
{
}

void SpherePolar::computeUVW(Vector& uvw, const RenderContext& context,
                           const Ray& ray, const HitRecord& hit) const
{
	Point hitpos = ray.origin()+ray.direction()*hit.minT();
	
	Vector Y = Cross(pole, meridian);
	Y.normalize();
	Vector vecHitpos = hitpos-center;
	
	double x = Dot(vecHitpos,meridian);
	double y = Dot(vecHitpos, Y);
	double z = Dot(vecHitpos, pole);
	
	SphericalMapping map;
	map.map(Point(x,y,z), uvw);
}
