/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * daray
 * 
 */

#ifndef _MITCHELLFILTER_H_
#define _MITCHELLFILTER_H_

#include "Filter.h"

class MitchellFilter: public Filter 
{
public:
	MitchellFilter();
	
	double evaluate(double x, double y) const;

protected:

private:

};

#endif // _MITCHELLFILTER_H_
