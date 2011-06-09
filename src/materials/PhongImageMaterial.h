
#ifndef _PHONGIMAGEMATERIAL_H_
#define _PHONGIMAGEMATERIAL_H_

#include "PhongMaterial.h"
#include "Image.h"
#include <string>

using namespace std;

class PhongImageMaterial: public PhongMaterial 
{
public:
	PhongImageMaterial(const string color, float Kd, float Ka, const Color& sHighlight, float exponent);
	virtual ~PhongImageMaterial();

	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
					 const HitRecord& hit, const Color& atten, int depth) const;
private:

	Image* image;
};

#endif // _PHONGIMAGEMATERIAL_H_
