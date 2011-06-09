
#include "Plane.h"
#include "HitRecord.h"
#include "Math.h"
#include "Ray.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Plane::Plane(Material* material, const Vector& normal, const Point& point)
  : Primitive(material), n(normal)
{
  n.normalize();
  d = Dot(n, point);
}

Plane::~Plane()
{
}

void Plane::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
  double denom = Dot(n, ray.direction());
  if(Abs(denom) > 1.e-6){
    double t = (d-Dot(n, ray.origin()))/denom;
    hit.hit(t, this, matl);
  }
}

void Plane::normal(Vector& normal, const RenderContext&,
                   const Point&, const Ray&, const HitRecord&) const
{
  normal = n;
}

void Plane::getBounds(BoundingBox& bbox) const
{
  cerr <<  "Plane::getBounds() called!" << endl;
  exit( 1 );
}

