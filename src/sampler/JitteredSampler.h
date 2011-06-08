
#ifndef _JITTEREDSAMPLER_H_
#define _JITTEREDSAMPLER_H_

#include "Sampler.h"

class JitteredSampler: public Sampler 
{
public:
	JitteredSampler(int spp);

protected:
	void generateSamples();

private:

};

#endif // _JITTEREDSAMPLER_H_
