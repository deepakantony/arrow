/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * daray
 * 
 */

#ifndef _WINDOWEDSINCFILTER_H_
#define _WINDOWEDSINCFILTER_H_

#include "Filter.h"

class WindowedSincFilter: public Filter 
{
public:
	WindowedSincFilter();
	
	double evaluate(double x, double y) const;

protected:

private:

};

#endif // _WINDOWEDSINCFILTER_H_
