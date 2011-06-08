
#include "TriangleFilter.h"
#include "utils/Math.h"

TriangleFilter::TriangleFilter() 
:Filter(2)
{
//	super(2.0);
}

double TriangleFilter::evaluate(double x, double y) const {
	
	return Max(0.0, 1.0 - Abs(x)) * Max(0.0, 1.0 - Abs(y));
}
