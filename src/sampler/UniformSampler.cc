
#include "UniformSampler.h"
#include <iostream>

UniformSampler::UniformSampler(int spp)
 :Sampler(spp)
{
  generateSamples();
}

void UniformSampler::generateSamples() {
  int indexSamples = 0;
  double clamp = -0.5 + (1.0 - ((double)sqrtSpp - 1.0)/(double)sqrtSpp)/2;
  for(int i = 0; i < numOfSets; i++) {
    for(int j = 0; j < sqrtSpp; j++) {
      for(int k = 0; k < sqrtSpp; k++) {
	Point sample(((double)k)/((double)sqrtSpp) + clamp, 
		     ((double)j)/((double)sqrtSpp)+clamp, clamp);
	samples[indexSamples++] = sample;
      }
    }
  }	
}
