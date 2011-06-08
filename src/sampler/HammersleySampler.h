/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * daray
 * 
 */

#ifndef _HAMMERSLEYSAMPLER_H_
#define _HAMMERSLEYSAMPLER_H_

#include "Sampler.h"

class HammersleySampler: public Sampler 
{
public:
	HammersleySampler(int spp);
	
	void generateSamples();
protected:

private:

};

#endif // _HAMMERSLEYSAMPLER_H_
