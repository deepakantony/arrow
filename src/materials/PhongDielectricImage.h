

#ifndef _DIELECTRICIMAGE_H_
#define _DIELECTRICIMAGE_H_

#include "DielectricMaterial.h"
#include "PhongMaterial.h"
#include "utils/Image.h"

#include <string>

using namespace std;

class PhongDielectricImage: public PhongMaterial 
{
public:
	PhongDielectricImage(const string file, const Color& colormask, const double maskrange, PhongMaterial* phong, DielectricMaterial* dielectric);
	
	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;
	
	bool mask() const;
protected:
	Color colormask;
	Image *image;
	DielectricMaterial *dielectric;
	double maskrange;
};

#endif // _DIELECTRICIMAGE_H_
