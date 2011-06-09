#include "Sampler.h"
#include <cstdlib>

Sampler::Sampler(int spp)
:samplesPerPixel(spp)
{
	numOfSets = 1000; // predefined number of sets so that the samples don't repeat
	samples = new Point[spp*numOfSets];
	sqrtSpp = (int)round(sqrt(samplesPerPixel));
}

Sampler::Sampler(int xEnd, int yEnd, int spp)
{
	// not implemented
}

Sampler::Sampler(int xStart, int xEnd, int yStart, int yEnd, int spp) 
{
	// not implemented
}

Sampler::~Sampler() {
	delete samples;
}

void Sampler::shuffleIndices() {
}

void Sampler::shuffleSamples() {
}

Point Sampler::getNextSample() {
	if( count % samplesPerPixel == 0 )
		jump = (rand() % numOfSets ) * samplesPerPixel;
	return (samples[count++ % (samplesPerPixel*numOfSets)]);
}

int Sampler::getSamplesPerPixel() const{
	return samplesPerPixel;
}


