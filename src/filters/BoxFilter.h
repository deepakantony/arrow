
#ifndef _BOXFILTER_H_
#define _BOXFILTER_H_

#include "Filter.h"

class BoxFilter: public Filter 
{
public:
	BoxFilter();
	
	double evaluate(double x, double y) const;
protected:

private:

};

#endif 
