
#include "JitteredSampler.h"
#include <iostream>
#include <cstdlib>

JitteredSampler::JitteredSampler(int spp)
:Sampler(spp)
{
	generateSamples();
}

void JitteredSampler::generateSamples() {
	int indexSamples = 0;
	double clamp = -0.5;
	for(int i = 0; i < numOfSets; i++) {
		for(int j = 0; j < sqrtSpp; j++) {
			for(int k = 0; k < sqrtSpp; k++) {
				// clamping to [-0.5, 0.5]. z value stores this value!
				Point sample(((double)k+(double)rand()/(double)RAND_MAX)/(double)sqrtSpp+clamp, 
							 ((double)j+(double)rand()/(double)RAND_MAX)/(double)sqrtSpp+clamp, -clamp);
				samples[indexSamples++] = sample;
			}
		}
	}	
}
