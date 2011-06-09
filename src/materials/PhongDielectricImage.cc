

#include "PhongDielectricImage.h"
#include "Image.h"
#include "Color.h"
#include "Vector.h"
#include "HitRecord.h"
#include "Primitive.h"

PhongDielectricImage::PhongDielectricImage(const string file, const Color& colormask, const double maskrange, PhongMaterial* phong, DielectricMaterial* dielectric)
:PhongMaterial(*phong),dielectric(dielectric), colormask(colormask), maskrange(maskrange)
{
	image = new Image(file);
}

void PhongDielectricImage::shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const
{
	Vector uvw;
	hit.getPrimitive()->computeUVW(uvw, context, ray, hit);
	PhongMaterial::color = image->interpolate(uvw.x(), uvw.y());
	if(mask())
		dielectric->shade(result, context, ray, hit, atten, depth);
	else
		PhongMaterial::shade(result, context, ray, hit, atten, depth);
}

bool PhongDielectricImage::mask() const {
	if(color.r() < (colormask.r()+maskrange) && 
	   color.g() < (colormask.g()+maskrange) && 
	   color.b() < (colormask.b()+maskrange) && 
	   color.r() > (colormask.r()-maskrange) && 
	   color.g() > (colormask.g()-maskrange) && 
	   color.b() > (colormask.b()-maskrange)
	   )
		return true;
	else return false;
}
