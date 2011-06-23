
#include "GaussianFilter.h"
#include "mathutil.h"

GaussianFilter::GaussianFilter(double std)
: Filter(5),std(std)
{
	coeff = 1.0/(2.0*acos(-1.0)*std*std);
}

double GaussianFilter::evaluate(double x, double y) const {
	return coeff*exp(-(x*x+y*y)/(2.0*std*std));
}
