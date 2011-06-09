#ifndef COUPLEDMATERIAL_H_
#define COUPLEDMATERIAL_H_

#include "Material.h"
#include "Color.h"

class CoupledMaterial : public Material {
 public:
  CoupledMaterial(const Color& color, float Kd, float Ka, const Color& sHighlight, float exponent);
  virtual ~CoupledMaterial();

  virtual void shade(Color& result, const RenderContext& context, const Ray& ray,
                     const HitRecord& hit, const Color& atten, int depth) const;

 private:
  CoupledMaterial(const CoupledMaterial&);
  CoupledMaterial& operator=(const CoupledMaterial&);

  Color color;
  float Kd;
  float Ka;
  Color sHighlight;
  float exponent;
};

#endif /*COUPLEDMATERIAL_H_*/
