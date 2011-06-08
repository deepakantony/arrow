
#ifndef _TRIANGLEFILTER_H_
#define _TRIANGLEFILTER_H_

#include "Filter.h"

class TriangleFilter : public Filter
{
public:
	TriangleFilter();
	
	double evaluate(double x, double y) const;

protected:

private:

};

#endif // _TRIANGLEFILTER_H_
