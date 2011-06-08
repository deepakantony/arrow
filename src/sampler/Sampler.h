
#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <vector>
#include <math.h>
#include <utils/Point.h>

using namespace std;

class Sampler
{
public:
	Sampler(int spp);
	Sampler(int xEnd, int yEnd, int spp);
	Sampler(int xStart, int xEnd, int yStart, int yEnd, int spp);
	
	~Sampler();
	
	virtual void generateSamples() = 0;
	
	void shuffleIndices();
	void shuffleSamples();
	Point getNextSample();
	int getSamplesPerPixel() const;

protected:
	int xPixelStart, xPixelEnd, yPixelStart, yPixelEnd;
	int samplesPerPixel;
	int numOfSets;
	int sqrtSpp;
	Point *samples;
	std::vector<int> shuffledIndices;
	unsigned long count;
	int jump;

private:

};

#endif // _SAMPLER_H_
