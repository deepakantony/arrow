
#ifndef _INVISIBLEMATERIAL_H_
#define _INVISIBLEMATERIAL_H_

#include "Material.h"

class InvisibleMaterial: public Material 
{
public:
	InvisibleMaterial();
	
	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;
	
	virtual bool castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const;

protected:
	

private:

};

#endif // _INVISIBLEMATERIAL_H_
