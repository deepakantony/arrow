/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * daray
 * 
 */

#ifndef _MULTIJITTEREDSAMPLER_H_
#define _MULTIJITTEREDSAMPLER_H_

#include "Sampler.h"

class MultiJitteredSampler: public Sampler 
{
public:
	MultiJitteredSampler(int spp);
	
	void generateSamples();

protected:

private:

};

#endif // _MULTIJITTEREDSAMPLER_H_
