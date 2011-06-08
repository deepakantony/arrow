
#include "SphericalMapping.h"
#include "utils/Math.h"
#include <iostream>

using namespace std;

SphericalMapping::SphericalMapping() {
}

void SphericalMapping::map(const Point& hitPos, Vector& uvw) const {
	double x = hitPos.x(), y = hitPos.y(), z = hitPos.z();
	double R = sqrt( x*x+y*y+z*z);

	double phi = acos(z/R);
	double theta = atan2(y,x);
	double u = theta/(2*M_PI);
	if(u<0) u += 1;
	double v = 1 - phi/M_PI;
	double w = R;

	uvw = Vector(u, v, w);								
}


