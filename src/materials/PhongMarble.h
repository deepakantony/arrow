
#ifndef _PHONGMARBLE_H_
#define _PHONGMARBLE_H_

#include "PhongMaterial.h"
#include "Color.h"

class PhongMarble: public PhongMaterial 
{
public:
	PhongMarble(const Color& color1, const Color& color2, const double scale, const int octaves,
				const double tscale, const double fscale, const double lacunarity, 
				const double gain, const double Kd, const double Ka, const Color& highlight,
				const double exponent);
	
	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

protected:
	double scale, tscale, fscale, lacunarity, gain;
	int octaves;
	Color color1, color2;
	
private:

};

#endif // _PHONGMARBLE_H_
