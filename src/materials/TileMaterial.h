
#ifndef _TILEMATERIAL_H_
#define _TILEMATERIAL_H_

#include "Material.h"
#include "utils/Vector.h"
#include "utils/Color.h"

class TileMaterial: public Material 
{
public:
	TileMaterial(const Vector& vector1, const Vector& vector2, const double scale, const double groutWidth, Material *matl1, Material*matl2);
	
	virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
              const HitRecord& hit, const Color& atten, int depth) const;
	
	virtual bool castShadows(const RenderContext& context, const HitRecord& hit, const Ray& ray) const;

protected:

private:
	Vector vector1, vector2;
	double groutWidth;
	double scale;
	Material *matlTile, *matlGrout;
};

#endif // _TILEMATERIAL_H_
