
#ifndef _NROOKSSAMPLER_H_
#define _NROOKSSAMPLER_H_

#include "Sampler.h"

class NRooksSampler: public Sampler 
{
public:
	NRooksSampler(int spp);
	
	void generateSamples();

protected:

private:

};

#endif // _NROOKSSAMPLER_H_
