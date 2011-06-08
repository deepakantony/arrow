
#include "PinholeCamera.h"
#include "rtengine/Ray.h"
#include "utils/Math.h"
#include <math.h>
#include <iostream>

PinholeCamera::PinholeCamera(const Point& eye, const Point& lookat, const Vector& up,
                             double hfov)
  : eye(eye), lookat(lookat), up(up), hfov(hfov)
{
}

PinholeCamera::~PinholeCamera()
{
}

void PinholeCamera::preprocess(double aspect_ratio)
{
  lookdir = lookat-eye;
  lookdir.normalize();
  u = Cross(lookdir, up);
  v = Cross(u, lookdir);
  double ulen = tan(hfov/2.*M_PI/180.);
  u.normalize();
  u *= ulen;
  double vlen = ulen/aspect_ratio;
  v.normalize(); 
  v *= vlen;
	//std::cout << u << " " << v << " " << ulen << " " << vlen << "\n";
}

void PinholeCamera::makeRay(Ray& ray, const RenderContext& context, double x, double y) const
{
  Vector direction = lookdir+u*x+v*y;
  direction.normalize();
  ray = Ray(eye, direction);
}
