/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * daray
 * 
 */

#ifndef _GAUSSIANFILTER_H_
#define _GAUSSIANFILTER_H_

#include "Filter.h"

class GaussianFilter: public Filter 
{
public:
	GaussianFilter(double std);
	
	double evaluate(double x, double y) const;
	double gaussian(double d, double exp) const;

protected:

private:
	double std, coeff;
};

#endif // _GAUSSIANFILTER_H_
