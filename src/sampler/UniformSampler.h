
#ifndef _UNIFORMSAMPLER_H_
#define _UNIFORMSAMPLER_H_

#include "Sampler.h"

class UniformSampler: public Sampler 
{
public:
	UniformSampler(int spp);

protected:
	void generateSamples();

private:

};

#endif // _UNIFORMSAMPLER_H_
