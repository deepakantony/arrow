#ifndef PHONGMATERIAL_H_
#define PHONGMATERIAL_H_

#include "Material.h"
#include "Color.h"

class PhongMaterial : public Material {
 public:
  PhongMaterial(const Color& color, float Kd, float Ka, const Color& sHighlight, float exponent);
  virtual ~PhongMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

protected:
  PhongMaterial(const PhongMaterial&);
  PhongMaterial& operator=(const PhongMaterial&);

  float Kd;
  float Ka;
  Color sHighlight;
  float exponent;
	mutable Color color;
};

#endif /*PHONGMATERIAL_H_*/
